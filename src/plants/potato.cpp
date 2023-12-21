/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:55:15
 * @LastEditTime: 2023-12-21 21:03:36
 * @Description: 豌豆射手
 */
#include "include/plants/potato.h"
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

Potato::Potato(PlantSlot *slot, const PlantData &data) :
  Plant(slot, data) {
  // setParent(slot);
  QWeakPointer<Zombie> weakZombie = manager->firstZombie(ij.x(), this->slot->pos());
  if (auto zombie = weakZombie.lock()) {
    if (zombie->collidesWithItem(slot) && zombie->alive()) {
      zombie->destoryGif(":/zombie/boomdead.gif");
      this->slot->reset();
      destory();
      return;
    }
  }
  
  connect(this, &Potato::near, [this] {
    disconnect(this, &Potato::near, nullptr, nullptr);
    QWeakPointer<Zombie> weakZombie = manager->firstZombie(ij.x(), this->slot->pos());
    attackZombie.clear();
    if (auto zombie = weakZombie.lock()) {
      if (zombie->alive()) {
        zombie->destoryGif(":/zombie/boomdead.gif");
      }
    }
    this->slot->reset();
    destory();
  });
  
}

/* 攻击 */
void Potato::attack() {
}
void Potato::destory() {
  if (isAlive == false) {
    return;
  }
  isAlive = false;
  attack_timer->stop();
  for (QGraphicsItem *item : items) {
    item->scene()->removeItem(item);
    items.removeOne(item);
    delete item;
  }
  destoryGif(":/plants/Boom.gif");
  // disconnect();
}

void Potato::destoryGif(QString fileName) {
  movie->stop();
  movie->setFileName(fileName);
  movie->start();
  connect(movie, &QMovie::finished, [this] {
    emit deathed();
  });
}