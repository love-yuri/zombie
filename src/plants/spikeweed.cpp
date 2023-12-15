/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:55:15
 * @LastEditTime: 2023-12-15 21:12:13
 * @Description: 豌豆射手
 */
#include "include/plants/spikeweed.h"
#include "hpp/tools.hpp"
#include "include/plants/plant.h"
#include "include/manager/game_manager.h"
#include "include/plants/plant_slot.h"
#include <QGraphicsScene>
#include "include/zombie/zombie.h"
#include "QSharedPointer"
#include <QMovie>
#include <exception>
#include <qapplication.h>
#include <qgraphicsitem.h>
#include "hpp/pea_attack.hpp"
#include <qpixmap.h>
#include <qtimer.h>

Spikeweed::Spikeweed(PlantSlot *slot, const PlantData &data) :
  Plant(slot, data) {
  connect(attack_timer, &QTimer::timeout, this, &Spikeweed::attack);
  attack_timer->start(plantData.interval);
}

/* 攻击 */
void Spikeweed::attack() {
  for (QWeakPointer<Zombie> zombieWeak : manager->zombieList().at(ij.x())) {
    if (auto zombie = zombieWeak.lock()) {
      if (zombie.data()->collidesWithItem(slot) && zombie->alive()) {
        zombie->injuried(plantData.hurt);
      }
    }
  }
}
void Spikeweed::destory() {
  isAlive = false;
  attack_timer->stop();
  for (QGraphicsItem *item : items) {
    item->scene()->removeItem(item);
    items.removeOne(item);
    delete item;
  }
  emit deathed();
  // disconnect();
}