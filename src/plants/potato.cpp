/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:55:15
 * @LastEditTime: 2023-12-11 16:34:03
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
  connect(this, &Potato::near, [this] {
    QWeakPointer<Zombie> weakZombie = manager->firstZombie(ij.x());
    destory();
    attackZombie = nullptr;
    if (auto zombie = weakZombie.lock()) {
      if (zombie->alive()) {
        zombie->destoryGif(":/zombie/boomdead.gif");
      }
    }
  });
}

/* 攻击 */
void Potato::attack() {
}
void Potato::destory() {
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