/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 18:51:57
 * @LastEditTime: 2023-12-07 22:47:07
 * @Description: 僵尸基类
 */
#include "include/zombie/zombie.h"
#include "hpp/tools.hpp"
#include <QPainter>
#include <qnamespace.h>
#include <qpen.h>
#include <qpixmap.h>
#include <qtimer.h>
#include "include/manager/game_manager.h"
#include "include/plants/plant.h"

Zombie::Zombie(GameManager *manager, int pos_i, const ZombieConfig::ZombieData &zombieData) :
  manager(manager), pos_i(pos_i), zombieData(zombieData), blod(zombieData.blod) {
  // setZValue(60);

  /* 播放默认状态 */
  movie = new QMovie(zombieData.default_state);
  movie->setParent(this);
  pixmap = QPixmap(zombieData.default_state);
  connect(movie, &QMovie::frameChanged, [this] {
    pixmap = movie->currentPixmap().scaled(pixmap.size());
    update();
  });

  /* 初始化定时器 */
  move_timer = new QTimer(this);
  attack_timer = new QTimer(this);

  movie->start();
  move();
}

Zombie::~Zombie() {
  movie->stop();
}

QRectF Zombie::boundingRect() const {
  return QRectF(pixmap.rect());
}

void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  painter->setRenderHint(QPainter::Antialiasing);
  QPen pen(Qt::red);
  pen.setWidth(2);
  painter->setPen(pen);
  painter->drawRect(pixmap.rect());
  painter->drawPixmap(pixmap.rect(), pixmap);
}

void Zombie::move() {
  connect(move_timer, &QTimer::timeout, [this]() {
    QSharedPointer<Plant> plant = nullptr;
    if (!this->manager->plantList().at(this->pos_i).isEmpty()) {
      plant = this->manager->plantList().at(this->pos_i).last();
    }
    setPos(pos() - QPointF(1, 0));
    if (pos().x() < 10) {
      move_timer->stop();
      emit this->gameOver();
    }
    if (plant && plant->plantSlot()->collidesWithItem(this)) {
      emit plant->near();
      this->attack_timer->start(zombieData.interval);
      connect(attack_timer, &QTimer::timeout, [this, plant]() {
        plant->injuried(zombieData.hurt);
      });
      connect(plant.data(), &Plant::deathed, [this, plant]() {
        attack_timer->stop();
        manager->plantList()[pos_i].removeOne(plant);
        plant->disconnect();
        // delete plant;
        movie->stop();
        movie->setFileName(zombieData.default_state);
        movie->start();
        move_timer->start(zombieData.speed);
      });
      attack(plant);
    }
  });
  move_timer->start(zombieData.speed);
}