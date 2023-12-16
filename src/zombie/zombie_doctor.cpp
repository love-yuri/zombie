/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-07 14:04:22
 * @LastEditTime: 2023-12-16 20:45:04
 * @Description: 普通僵尸
 */
#include "hpp/tools.hpp"
#include "include/plants/plant.h"
#include "include/zombie/zombie_doctor.h"
#include "include/manager/game_manager.h"
#include "hpp/doctor_fire.hpp"
#include <QPropertyAnimation>
#include "include/zombie/zombie.h"
#include <QTimer>
#include <qpoint.h>
#include <qtimer.h>

ZombieDoctor::ZombieDoctor(GameManager *manager, int pos_i, const ZombieData &zombieData) :
  Zombie(manager, pos_i, zombieData) {
  animation = new QPropertyAnimation(this, "pos");
  animation->setParent(this);
  isZombieDoctor = true;
  moveTo(manager->zombiePos().at(pos_i) + QPointF(-130, 0));
  connect(attack_timer, &QTimer::timeout, [this]() {
    attack(QWeakPointer<Plant>());
  });
  attack_timer->start(zombieData.interval);
}

/* 僵尸攻击效果 */
void ZombieDoctor::attack(QWeakPointer<Plant> weakPlant) {
  movie->stop();
  movie->setFileName(":/zombie/zombie_doctor_complete_form/attack_1.gif");
  movie->start();
  movie->disconnect(movie, &QMovie::finished, nullptr, nullptr);
  connect(movie, &QMovie::finished, [this] {
    DoctorFire *fire = new DoctorFire(":/zombie/zombie_doctor_complete_form/fire.gif");
    fire->setPos(QPointF(20, pos().y()));
    scene()->addItem(fire);
    movie->stop();
    movie->disconnect(movie, &QMovie::finished, nullptr, nullptr);
    movie->setFileName(":/zombie/zombie_doctor_complete_form/attack_2.gif");
    movie->start();
    for (auto plant : manager->plantList().at(pos_i)) {
      plant->destory();
    }
    connect(movie, &QMovie::finished, [this] {
      movie->stop();
      movie->setFileName(zombieData.default_state);
      movie->start();
      pos_i--;
      if (pos_i >= 0) {
        manager->zombieList()[pos_i + 1].removeOne(sharedPtr);
        manager->zombieList()[pos_i].push_back(sharedPtr);
        moveTo(manager->zombiePos().at(pos_i) - QPointF(130, 0));
      }
    });
  });
}

/* 死亡效果 */
void ZombieDoctor::destory() {
  isAlive = false;
  move_timer->stop();
  sharedPtr = QSharedPointer<Zombie>();
  QString file = QString(":/zombie/zombie_doctor_complete_form/died.gif");
  destoryGif(file);
}

void ZombieDoctor::moveTo(QPointF point) {
  animation->stop();
  animation->setDuration(2000);
  animation->setStartValue(pos());
  animation->setEndValue(point);
  animation->start();
}

void ZombieDoctor::injuried(int blod) {
  this->blod -= blod;
  if (this->blod <= 0) {
    isAlive = false;
    destory();
  }
}