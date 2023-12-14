/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-07 14:04:22
 * @LastEditTime: 2023-12-14 21:05:34
 * @Description: 普通僵尸
 */
#include "hpp/tools.hpp"
#include "include/plants/plant.h"
#include "include/zombie/zombie_doctor.h"
#include "include/manager/game_manager.h"
#include <QPropertyAnimation>
#include "include/zombie/zombie.h"
#include <QTimer>
#include <qpoint.h>
#include <qtimer.h>

ZombieDoctor::ZombieDoctor(GameManager *manager, int pos_i, const ZombieData &zombieData) :
  Zombie(manager, pos_i, zombieData) {
  move();
}

/* 僵尸攻击效果 */
void ZombieDoctor::attack(QWeakPointer<Plant> weakPlant) {
  if (auto plant = weakPlant.lock()) {
    move_timer->stop();
    plant->attackZombie = this;

    /* 更换攻击动画 */
    movie->stop();
    movie->setFileName(zombieData.attack_state);
    movie->start();

    attack_timer->start(zombieData.interval);
    connect(attack_timer, &QTimer::timeout, [this, weakPlant]() {
      if (auto plant = weakPlant.lock()) {
        plant->injuried(zombieData.hurt);
      }
    });
  }
}

/* 受伤效果 */
void ZombieDoctor::destory() {
  isAlive = false;
  move_timer->stop();
  destoryGif(":/zombie/normalZombie/ZombieDie.gif");
}

void ZombieDoctor::move() {
  auto animation = new QPropertyAnimation(this, "pos");
  animation->setParent(this);
  animation->setDuration(1000);
  animation->setStartValue(pos());
  animation->setEndValue(manager->zombiePos().at(pos_i) + QPointF(-100, -40));
  animation->start();
}

void ZombieDoctor::injuried(int blod) {
  this->blod -= blod;
  if (this->blod <= 0) {
    isAlive = false;
    destory();
  }
}