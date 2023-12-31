/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 18:51:57
 * @LastEditTime: 2023-12-22 10:14:41
 * @Description: 僵尸基类
 */
#include "include/zombie/zombie.h"
#include "hpp/tools.hpp"
#include <QPainter>
#include <exception>
#include <qgraphicsscene.h>
#include <qnamespace.h>
#include <qpen.h>
#include <qpixmap.h>
#include <qtimer.h>
#include "include/manager/game_manager.h"
#include "include/plants/plant.h"

Zombie::Zombie(GameManager *manager, int pos_i, const ZombieData &zombieData) :
  manager(manager), pos_i(pos_i), zombieData(zombieData), blod(zombieData.blod) {
  // setZValue(60);
  deathedCount = 0;
  isAlive = true;
  isZombieDoctor = false;

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
}

Zombie::~Zombie() {
  movie->stop();
  attack_timer->stop();
  move_timer->stop();
}

QRectF Zombie::boundingRect() const {
  return QRectF(pixmap.rect());
}

void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  painter->setRenderHint(QPainter::Antialiasing);
  painter->drawPixmap(pixmap.rect(), pixmap);
}

void Zombie::move() {
  connect(move_timer, &QTimer::timeout, [this]() {
    setPos(pos() - QPointF(1, 0));
    if (pos().x() < 10) {
      move_timer->stop();
      emit this->gameOver();
      return;
    }
    QWeakPointer<Plant> weakPlant = manager->firstPlant(pos_i);
    if (auto plant = weakPlant.lock()) {
      /* 如果发生了碰撞 */
      if (collidesWithItem(plant->plantSlot()) && plant->alive()) {
        emit plant->near();
        if (isAlive) {
          attack(weakPlant);
        }
      }
    }
  });
  restart();
}

void Zombie::restart() {
  if (isAlive) {
    try {
      isAttacking = false;
      movie_mutex.lock();
      movie->stop();
      movie->setFileName(zombieData.default_state);
      move_timer->start(zombieData.speed);
      movie->start();
      movie_mutex.unlock();
    } catch (std::exception e) {
      emit destory();
      qerror << e.what();
    }
    
  }
}

void Zombie::destoryGif(const QString &fileName) {
  isAlive = false;
  attack_timer->stop();
  move_timer->stop();
  movie_mutex.lock();
  movie->stop();
  movie->setFileName(fileName);
  movie->start();
  connect(movie, &QMovie::finished, [this] {
    emit deathed();
  });
  movie_mutex.unlock();
}