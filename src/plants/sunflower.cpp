/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:55:15
 * @LastEditTime: 2023-12-10 21:16:20
 * @Description: 豌豆射手
 */
#include "include/plants/sunflower.h"
#include "hpp/tools.hpp"
#include "include/plants/plant.h"
#include "include/manager/game_manager.h"
#include "include/plants/plant_slot.h"
#include <QRandomGenerator>
#include "hpp/sun.hpp"
#include <QGraphicsScene>
#include "include/zombie/zombie.h"
#include "QSharedPointer"
#include <QMovie>
#include <QPropertyAnimation>
#include <exception>
#include <qapplication.h>
#include <qgraphicsitem.h>
#include "hpp/pea_attack.hpp"
#include <qpixmap.h>
#include <qpoint.h>
#include <qtimer.h>

SunFlower::SunFlower(PlantSlot *slot, const PlantData &data) :
  Plant(slot, data) {
}

/* 攻击 */
void SunFlower::attack() {
  Sun *sun = new Sun(manager);
  int x = QRandomGenerator::global()->bounded(200) - 100;
  int y = QRandomGenerator::global()->bounded(200) - 100;
  sun->setPos(slot->pos());
  scene->addItem(sun);
  sun->moveTo(slot->pos() + QPoint(x, y));
}

void SunFlower::destory() {
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