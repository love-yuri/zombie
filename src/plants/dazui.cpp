/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:55:15
 * @LastEditTime: 2023-12-16 22:08:26
 * @Description: 豌豆射手
 */
#include "include/plants/dazui.h"
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

Dazui::Dazui(PlantSlot *slot, const PlantData &data) :
  Plant(slot, data) {
  isEating = false;
  // setParent(slot);
  connect(this, &Dazui::near, [this] {
    if (isEating) {
      return;
    }
    movie->disconnect(movie, &QMovie::finished, nullptr, nullptr);
    movie->stop();
    movie->setFileName(":/plants/dazui/ChomperAttack.gif");
    // movie
    connect(movie, &QMovie::finished, [this] {
      movie->stop();
      movie->setFileName(":/plants/dazui/ChomperDigest.gif");
      movie->start();
      QWeakPointer<Zombie> weakZombie = manager->firstZombie(ij.x(), this->slot->pos());
      attackZombie.clear();
      if (auto zombie = weakZombie.lock()) {
        if (zombie->alive()) {
          isEating = true;
          zombie->destory();
          QTimer *timer = new QTimer(this);
          timer->setSingleShot(true);
          connect(timer, &QTimer::timeout, [this]() {
            movie->stop();
            movie->setFileName(plantData.default_state);
            movie->start();
            QWeakPointer<Zombie> weakZombie = manager->firstZombie(ij.x(), this->slot->pos());
            isEating = false;
            if (auto zombie = weakZombie.lock()) {
              if (zombie->alive() && this->slot->collidesWithItem(zombie.data())) {
                emit this->near();
              }
            }
          });
          timer->start(10000);
        }
      }
    });
    movie->start();
  });
}

/* 攻击 */
void Dazui::attack() {
}
void Dazui::destory() {
  isAlive = false;
  attack_timer->stop();
  for (QGraphicsItem *item : items) {
    item->scene()->removeItem(item);
    items.removeOne(item);
    delete item;
  }
  emit deathed();
}