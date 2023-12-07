/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:55:15
 * @LastEditTime: 2023-12-07 22:47:39
 * @Description: 豌豆射手
 */
#include "include/plants/pea.h"
#include "hpp/tools.hpp"
#include "include/plants/plant.h"
#include "include/manager/game_manager.h"
#include "include/plants/plant_slot.h"
#include "include/zombie/zombie.h"
#include "QSharedPointer"
#include <QMovie>
#include <qgraphicsitem.h>
#include <qpixmap.h>
#include <qtimer.h>

Pea::Pea(PlantSlot *slot, PlantConfig::PlantData data) :
  Plant(slot, data) {
  // setParent(slot);
}

Pea::~Pea() {
  qinfo << "豌豆射手被析构了";
}

/* 攻击 */
void Pea::attack() {
  QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(":/plants/bullet_normal.png"));
  item->setPos(this->slot->pos() + QPoint(100, 10));
  scene->addItem(item);
  QTimer *timer = new QTimer(this);
  timer->start(30);
  connect(timer, &QTimer::timeout, [this, item, timer] {
    zombie_ptr zombie = nullptr;
    if (!manager->zombieList().at(ij.x()).isEmpty()) {
      zombie = manager->zombieList().at(ij.x()).first();
    }
    item->setPos(item->pos() + QPoint(10, 0));
    if (item->pos().x() > 900) {
      scene->removeItem(item);
      delete item;
      timer->stop();
    }
    if (zombie && item->collidesWithItem(zombie.data())) {
      zombie->injuried(plantData.hurt);
      scene->removeItem(item);
      delete item;
      timer->stop();
    }
  });
}

void Pea::injuried(int blod) {
  this->blod -= blod;
  if (this->blod <= 0) {
    destory();
  }
}

void Pea::destory() {
  attack_timer->stop();
  emit deathed();
  movie->stop();
  disconnect();
}