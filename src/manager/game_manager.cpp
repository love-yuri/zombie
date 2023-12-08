/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 20:46:20
 * @LastEditTime: 2023-12-08 22:32:19
 * @Description:
 */
#include "include/manager/game_manager.h"
#include "hpp/tools.hpp"
#include "include/manager/global_config.h"
#include "include/plants/pea.h"
#include "include/plants/plant.h"
#include "include/zombie/bucket_zombie.h"
#include "include/zombie/cone_zombie.h"
#include "include/zombie/nomal_zombie.h"
#include "include/zombie/zombie.h"
#include <qcontainerfwd.h>
#include <QSharedPointer>
#include <qgraphicsscene.h>
#include <qlist.h>
#include <qpoint.h>
#include <qtimer.h>

GameManager::GameManager(QObject *parent, QGraphicsScene *scene, GlobalConfig *config) :
  QObject(parent), scene(scene), config(config) {
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
}

GameManager::~GameManager() {
}

plant_ptr GameManager::createPlant(QString name, PlantSlot *slot) {
  PlantData data = config->plantsData().value(name);
  plant_ptr plant = nullptr;
  switch (config->plantsTypeMap().value(name)) {
  case PEA: plant = QSharedPointer<Plant>(new Pea(slot, data)); break;
  default:
    return nullptr;
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
      plant->attackZombie->restart();
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
  zombie_list[pos_i].push_back(zombie);
  QWeakPointer<Zombie> weakZombie = zombie;
  connect(zombie.data(), &Zombie::deathed, [this, weakZombie]() {
    if (auto zombie = weakZombie.lock()) {
      zombie_list[zombie->pos_i].removeOne(zombie);
      // zombie->destoryGif(weakZombie);
      zombie->scene()->removeItem(zombie.data());
    }
  });
  return zombie;
}