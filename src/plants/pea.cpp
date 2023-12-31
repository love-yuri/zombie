/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:55:15
 * @LastEditTime: 2023-12-16 19:59:06
 * @Description: 豌豆射手
 */
#include "include/plants/pea.h"
#include "hpp/tools.hpp"
#include "include/plants/plant.h"
#include "include/manager/game_manager.h"
#include "include/plants/plant_slot.h"
#include <QGraphicsScene>
#include "include/zombie/zombie.h"
#include "QSharedPointer"
#include <QMovie>
#include <exception>
#include <qgraphicsitem.h>
#include "hpp/pea_attack.hpp"
#include <qpixmap.h>
#include <qtimer.h>

Pea::Pea(PlantSlot *slot, const PlantData &data) :
  Plant(slot, data) {
  // setParent(slot);
}

/* 攻击 */
void Pea::attack() {
  if (manager->zombieList().at(ij.x()).empty()) {
    return;
  }
  PeaAttack *attack = new PeaAttack(":/plants/bullet_normal.png");
  attack->setPos(slot->pos() + QPointF(30, 10));
  scene->addItem(attack);
  attack->start(30, this, manager, plantData.hurt);
}

void Pea::destory() {
  attack_timer->stop();
  for (QGraphicsItem *item : items) {
    item->scene()->removeItem(item);
    items.removeOne(item);
    delete item;
  }
  movie->stop();
  emit deathed();
  disconnect();
}