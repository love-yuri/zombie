/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:55:15
 * @LastEditTime: 2023-12-06 21:34:05
 * @Description: 豌豆射手
 */
#include "include/plants/pea.h"
#include "hpp/tools.hpp"
#include "include/plants/plant.h"
#include "include/manager/game_manager.h"
#include "include/plants/plant_slot.h"
#include "include/zombie/zombie.h"
#include <QMovie>
#include <qgraphicsitem.h>
#include <qpixmap.h>
#include <qtimer.h>

Pea::Pea(PlantSlot *slot, PlantConfig::PlantData data) : Plant(slot, data) {
  setParent(slot);
  movie = nullptr;
  this->scene = slot->mutableScene();
  this->pixmap = slot->mutablePixmap();
  movie = new QMovie(data.default_state);
  connect(movie, &QMovie::frameChanged, [this] {
    QPixmap pix(movie->currentPixmap().scaled(pixmap->size()));
    pixmap->swap(pix);
    this->slot->update();
  });
  movie->start();
  // manager-

  QTimer *timer = new QTimer(this);
  timer->start(1000);
  Zombie *zombie = new Zombie();
  zombie->setPos(600, 400);
  zombie->setParent(this);
  scene->addItem(zombie);
  connect(timer, &QTimer::timeout, [this, zombie] {
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(":/plants/bullet_normal.png"));
    item->setPos(this->slot->pos() + QPoint(100, 10));
    scene->addItem(item);
    QTimer *timer = new QTimer(this);
    timer->start(30);
    connect(timer, &QTimer::timeout, [this, item, timer, zombie] {
      item->setPos(item->pos() + QPoint(10, 0));
      if (item->pos().x() > 900 || item->collidesWithItem(zombie)) {
        scene->removeItem(item);
        delete item;
        timer->stop();
      }
    });
  });
}

Pea::~Pea() {
  if (movie != nullptr) {
    movie->stop();
    delete movie;
  }
}