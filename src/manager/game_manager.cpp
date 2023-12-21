/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 20:46:20
 * @LastEditTime: 2023-12-21 20:58:51
 * @Description:
 */
#include "include/manager/game_manager.h"
#include "hpp/sun.hpp"
#include "hpp/sun_number.hpp"
#include "hpp/tools.hpp"
#include "include/manager/global_config.h"
#include "include/plants/plant_card.h"
#include "include/plants/dazui.h"
#include "include/plants/double_pea.h"
#include "include/plants/pea.h"
#include "include/plants/plant.h"
#include "include/plants/plant_card.h"
#include "include/plants/plant_slot.h"
#include "include/plants/potato.h"
#include "include/plants/spikeweed.h"
#include "include/plants/squash.h"
#include "include/plants/sunflower.h"
#include "include/plants/tallnut.h"
#include "include/plants/wallnut.h"
#include "include/plants/cherry.h"
#include "include/zombie/bucket_zombie.h"
#include "include/zombie/cone_zombie.h"
#include "include/zombie/nomal_zombie.h"
#include "include/zombie/zombie.h"
#include "include/zombie/zombie_doctor.h"
#include <qcontainerfwd.h>
#include <QSharedPointer>
#include <QRandomGenerator>
#include <qgraphicsscene.h>
#include <qlist.h>
#include <qpoint.h>
#include <qreadwritelock.h>
#include <qtimer.h>

GameManager::GameManager(QObject *parent, QGraphicsScene *scene, GlobalConfig *config) :
  QObject(parent), scene(scene), config(config) {
  sun_ = config->defaultConfig().default_sun;
  zom_num = 0;
  sun_number = new SunNumber(this);
  scene->addItem(sun_number);
  /* 初始化位置map */
  for (int i = 0; i < 5; i++) {
    QVector<QPoint> vec;
    for (int j = 0; j < 9; j++) {
      QPoint p(77 + j * 84, 90 + i * 94);
      vec.push_back(p);
    }
    zombie_pos.push_back(QPoint(vec.back()) + QPoint(90, -20));
    pos_map.push_back(vec);
  }
  plant_list = QVector<QList<plant_ptr>>(pos_map.size());
  zombie_list = QVector<QList<zombie_ptr>>(pos_map.size());
  slot_list = QVector<QVector<PlantSlot *>>(pos_map.size(), QVector<PlantSlot *>(pos_map.first().size()));
}

GameManager::~GameManager() {
}

QWeakPointer<Plant> GameManager::firstPlant(int i) {
  QReadLocker locker(&plant_lock);
  if (i >= plant_list.size() || plant_list[i].isEmpty()) {
    return QWeakPointer<Plant>();
  }
  return plant_list[i].last();
}

QWeakPointer<Zombie> GameManager::firstZombie(int i, const QPointF &pos) {
  QList<zombie_ptr> &list = zombie_list[i];
  std::sort(list.begin(), list.end(), [](zombie_ptr a, zombie_ptr b) {
    return a->pos().x() < b->pos().x();
  });
  QReadLocker locker(&zombie_lock);
  if (i >= zombie_list.size() || zombie_list[i].isEmpty()) {
    return QWeakPointer<Zombie>();
  }
  for (QWeakPointer<Zombie> zombie : zombie_list[i]) {
    if (auto zom = zombie.lock()) {
      if (zom->alive() && zom->pos().x() >= pos.x()) {
        return zom;
      }
    }
  }
  return zombie_list[i].first();
}

plant_ptr GameManager::createPlant(QString name, PlantSlot *slot) {
  PlantData data = config->plantsData().value(name);
  plant_ptr plant = nullptr;
  switch (config->plantsTypeMap().value(name)) {
  case PEA: plant = QSharedPointer<Plant>(new Pea(slot, data)); break;
  case POTATOMINE: plant = QSharedPointer<Potato>(new Potato(slot, data)); break;
  case TALLNUT: plant = QSharedPointer<Tallnut>(new Tallnut(slot, data)); break;
  case WALLNUT: plant = QSharedPointer<Wallnut>(new Wallnut(slot, data)); break;
  case DAZUI: plant = QSharedPointer<Dazui>(new Dazui(slot, data)); break;
  case SUNFLOWER: plant = QSharedPointer<SunFlower>(new SunFlower(slot, data)); break;
  case REPEATERPEA: plant = QSharedPointer<DoublePea>(new DoublePea(slot, data)); break;
  case CHERRY: plant = QSharedPointer<Cherry>(new Cherry(slot, data)); break;
  case SKIKEWEED: plant = QSharedPointer<Spikeweed>(new Spikeweed(slot, data)); break;
  case CSQUASH: plant = QSharedPointer<Squash>(new Squash(slot, data)); break;
  default:
    return nullptr;
  }
  delSun(data.sun);
  QWriteLocker locker(&plant_lock);
  if (config->plantsTypeMap().value(name) == SKIKEWEED) {
    plant_list_temp.push_back(plant);
    return plant;
  }
  plant_list[slot->ij.x()].push_back(plant);
  QList<plant_ptr> &list = plant_list[slot->ij.x()];
  std::sort(list.begin(), list.end(), [](plant_ptr a, plant_ptr b) {
    return a->ij.y() < b->ij.y();
  });
  QWeakPointer<Plant> weakPlant = plant;
  connect(plant.data(), &Plant::deathed, [this, weakPlant, slot]() {
    if (auto plant = weakPlant.lock()) {
      plant_list[slot->ij.x()].removeOne(plant);
      if (!plant->attackZombie.empty()) {
        for (auto zombie : plant->attackZombie) {
          zombie->restart();
        }
      }
      plant->disconnect(plant.data(), &Plant::near, nullptr, nullptr);
      plant.clear();
    }
  });
  return plant;
}
zombie_ptr GameManager::createZombie(ZombieType type, int pos_i) {
  zombie_ptr zombie = nullptr;
  QPoint p = zombiePos()[pos_i];
  ZombieData zombieData = config->zombiesData().value(config->zombiesTypeMap().key(type));
  switch (type) {
  case ZombieType::NAORMAL: zombie = QSharedPointer<Zombie>(new NormalZombie(this, pos_i, zombieData)); break;
  case ZombieType::CONE: zombie = QSharedPointer<Zombie>(new ConeZombie(this, pos_i, zombieData)); break;
  case ZombieType::BUCKET: zombie = QSharedPointer<Zombie>(new BucketZombie(this, pos_i, zombieData)); break;
  default:
    return nullptr;
  }
  QWriteLocker locker(&zombie_lock);
  zombie->setPos(p);
  zombie_list[pos_i].push_back(zombie);
  QList<zombie_ptr> &list = zombie_list[pos_i];
  std::sort(list.begin(), list.end(), [](zombie_ptr a, zombie_ptr b) {
    return a->pos().x() < b->pos().x();
  });
  zom_num++;
  QWeakPointer<Zombie> weakZombie = zombie;
  connect(zombie.data(), &Zombie::deathed, [this, weakZombie]() {
    if (auto zombie = weakZombie.lock()) {
      zombie_list[zombie->pos_i].removeOne(zombie);
      zombie->scene()->removeItem(zombie.data());
    }
  });
  connect(zombie.data(), &Zombie::gameOver, this, &GameManager::gameOver);
  return zombie;
}

void GameManager::addSun() {
  sun_ += 25;
  sun_number->update();
  // scene->update();
  for (PlantCard *card : plant_cards) {
    card->update();
  }
}

void GameManager::delSun(int val) {
  sun_ -= val;
  // scene->update();
  for (PlantCard *card : plant_cards) {
    card->update();
  }
  sun_number->update();
}

void GameManager::start(const QList<QString> &plants) {
  sun_number->setPos(12, 57);
  /* 放置植物卡片 */
  for (int i = 0; i < plants.size(); i++) {
    PlantCard *card = new PlantCard(config->plantsData().value(plants[i]), this);
    plant_cards.push_back(card);
    card->setPos(78 + i * (130 - 78), 8);
    scene->addItem(card);
  }

  /* 初始化地图卡片 */
  int i = -1;
  for (QVector<QPoint> points : posMap()) {
    int j = -1;
    i++;
    for (QPoint point : points) {
      j++;
      PlantSlot *slot = new PlantSlot(scene, this);
      slot->setPos(point);
      slot->ij = QPoint(i, j);
      scene->addItem(slot);
      slot_list[i][j] = slot;
    }
  }

  /* 僵尸产生 */
  QTimer *timer = new QTimer(this);
  timer->setSingleShot(true);
  timer->start(config->defaultConfig().first_zombie);
  auto randomZom = [this] {
    int pos_i = QRandomGenerator::global()->bounded(zombiePos().size());
    int zombie_type = QRandomGenerator::global()->bounded(config->zombiesTypeMap().size());
    ZombieType type = ZombieType(zombie_type);
    if (zom_num <= config->defaultConfig().normal_zombie_num) {
      type = ZombieType::NAORMAL;
    }
    zombie_ptr zombie = createZombie(type, pos_i);
    scene->addItem(zombie.data());
  };
  // createZombieDoctor();
  connect(timer, &QTimer::timeout, [this, randomZom]() {
    randomZom();
    QTimer *main_zom = new QTimer(this);
    main_zom->setSingleShot(true);
    main_zom->start(QRandomGenerator::global()->bounded(config->defaultConfig().min_interval, config->defaultConfig().max_interval));
    connect(main_zom, &QTimer::timeout, [this, main_zom, randomZom]() {
      randomZom();
      if (zom_num < config->defaultConfig().threshold) {
        main_zom->start(QRandomGenerator::global()->bounded(config->defaultConfig().min_interval, config->defaultConfig().max_interval));
      } else {
        createZombieDoctor();
        QTimer *timer = new QTimer(this);
        timer->start(2000);
        connect(timer, &QTimer::timeout, [this, timer, randomZom] {
          randomZom();
          if (zom_num >= config->defaultConfig().zombie_num) {
            timer->stop();
          }
        });
      }
    });
  });

  /* 随机产生太阳花 */
  QTimer *sun_timer = new QTimer(this);
  sun_timer->start(config->defaultConfig().global_sun_time);
  connect(sun_timer, &QTimer::timeout, [this]() {
    Sun *sun = new Sun(this);
    int x = QRandomGenerator::global()->bounded(600);
    int y = QRandomGenerator::global()->bounded(500);
    sun->setPos(QPointF(20, 20));
    scene->addItem(sun);
    sun->moveTo(QPoint(x, y));
  });
}

void GameManager::createZombieDoctor() {
  ZombieData zombieData = config->zombiesData().value("zombie_doctor_complete_form");
  zombie_ptr zombie = QSharedPointer<ZombieDoctor>(new ZombieDoctor(this, 4, zombieData));
  QWriteLocker locker(&zombie_lock);
  zombie_list[4].push_back(zombie);
  QWeakPointer<Zombie> weakZombie = zombie;
  connect(zombie.data(), &Zombie::deathed, [this, weakZombie]() {
    if (auto zombie = weakZombie.lock()) {
      zombie_list[zombie->pos_i].removeOne(zombie);
      // zombie->scene()->removeItem(zombie.data());
      emit victory();
    }
  });
  ZombieDoctor *doctor = dynamic_cast<ZombieDoctor *>(zombie.data());
  doctor->sharedPtr = zombie;
  zombie->setPos(zombie_pos.at(4));
  scene->addItem(zombie.data());
}