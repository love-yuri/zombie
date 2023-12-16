/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:55:15
 * @LastEditTime: 2023-12-16 22:06:00
 * @Description: 豌豆射手
 */
#include "include/plants/cherry.h"
#include "hpp/tools.hpp"
#include "include/manager/global_config.h"
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

Cherry::Cherry(PlantSlot *slot, const PlantData &data) :
  Plant(slot, data) {
  // setParent(slot);
  int x = ij.x();
  int y = ij.y();
  boom(x - 1, y);
  boom(x - 1, y - 1);
  boom(x - 1, y + 1);
  boom(x + 1, y + 1);
  boom(x + 1, y - 1);
  boom(x + 1, y);
  boom(x, y);
  boom(x, y - 1);
  boom(x, y + 1);
  destory();
}

/* 攻击 */
void Cherry::attack() {
}
void Cherry::destory() {
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

void Cherry::destoryGif(QString fileName) {
  // movie->disconnect(movie, &QMovie::frameChanged, nullptr, nullptr);
  movie->stop();
  movie->setFileName(fileName);
  movie->start();
  connect(movie, &QMovie::finished, [this] {
    slot->setState(0);
    emit deathed();
  });
}

void Cherry::boom(int x, int y) {
  if (x < 0 || y < 0) {
    return;
  }
  if (x >= manager->slotList().size() || y >= manager->slotList().at(x).size()) {
    return;
  }
  auto slot = manager->slotList().at(x).at(y);
  for (QWeakPointer<Zombie> zombieWeak : manager->zombieList().at(x)) {
    if (auto zombie = zombieWeak.lock()) {
      if (zombie->collidesWithItem(slot) && !zombie->zombieDoctor()) {
        zombie->destoryGif(":/zombie/boomdead.gif");
      }
    }
  }
}