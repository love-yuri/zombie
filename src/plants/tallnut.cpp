/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:55:15
 * @LastEditTime: 2023-12-12 14:47:56
 * @Description: 豌豆射手
 */
#include "include/plants/tallnut.h"
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

Tallnut::Tallnut(PlantSlot *slot, const PlantData &data) :
  Plant(slot, data) {
}

/* 攻击 */
void Tallnut::attack() {
}
void Tallnut::destory() {
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

void Tallnut::injuried(int blod) {
  this->blod -= blod;
  if (this->blod == 10) {
    movie->stop();
    movie->setFileName(":/plants/tallnut/TallnutCracked1.gif");
    movie->start();
  } else if (this->blod == 6) {
    movie->stop();
    movie->setFileName(":/plants/tallnut/TallnutCracked2.gif");
    movie->start();
  } else if (this->blod <= 0) {
    isAlive = false;
    destory();
  }
}