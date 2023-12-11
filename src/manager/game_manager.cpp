/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 20:46:20
 * @LastEditTime: 2023-12-11 17:21:05
 * @Description:
 */
#include "include/manager/game_manager.h"
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
#include <qcontainerfwd.h>
#include <QSharedPointer>
#include <qgraphicsscene.h>
#include <qlist.h>
#include <qpoint.h>
#include <qreadwritelock.h>
#include <qtimer.h>

GameManager::GameManager(QObject *parent, QGraphicsScene *scene, GlobalConfig *config) :
  QObject(parent), scene(scene), config(config) {
  sun_ = config->defaultConfig().default_sun;
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

QWeakPointer<Zombie> GameManager::firstZombie(int i) {
  QReadLocker locker(&zombie_lock);
  if (i >= zombie_list.size() || zombie_list[i].isEmpty()) {
    return QWeakPointer<Zombie>();
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
      if (plant->attackZombie) {
        plant->attackZombie->restart();
      }
      plant->disconnect(plant.data(), &Plant::near, nullptr, nullptr);
      plant.clear();
    }
  });
  return plant;
}
zombie_ptr GameManager::createZombie(ZombieType type, int pos_i) {
  zombie_ptr zombie = nullptr;
  ZombieData zombieData = config->zombiesData().value(config->zombiesTypeMap().key(type));
  switch (type) {
  case ZombieType::NAORMAL: zombie = QSharedPointer<Zombie>(new NormalZombie(this, pos_i, zombieData)); break;
  case ZombieType::CONE: zombie = QSharedPointer<Zombie>(new ConeZombie(this, pos_i, zombieData)); break;
  case ZombieType::BUCKET: zombie = QSharedPointer<Zombie>(new BucketZombie(this, pos_i, zombieData)); break;
  default:
    return nullptr;
  }
  QWriteLocker locker(&zombie_lock);
  zombie_list[pos_i].push_back(zombie);
  QWeakPointer<Zombie> weakZombie = zombie;
  connect(zombie.data(), &Zombie::deathed, [this, weakZombie]() {
    if (auto zombie = weakZombie.lock()) {
      zombie_list[zombie->pos_i].removeOne(zombie);
      zombie->scene()->removeItem(zombie.data());
    }
  });
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

  i = 0;
  for (QPoint point : zombiePos()) {
    zombie_ptr zombie = createZombie(CONE, i++);
    zombie->setPos(point);
    // game_manager->addZombie(zombie);
    scene->addItem(zombie.data());
  }
}