/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:55:15
 * @LastEditTime: 2023-12-16 22:50:20
 * @Description: 豌豆射手
 */
#include "include/plants/squash.h"
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

Squash::Squash(PlantSlot *slot, const PlantData &data) :
  Plant(slot, data) {

}

/* 攻击 */
void Squash::attack() {
}
void Squash::destory() {
  isAlive = false;
  attack_timer->stop();
  for (QGraphicsItem *item : items) {
    item->scene()->removeItem(item);
    items.removeOne(item);
    delete item;
  }
  emit deathed();
}