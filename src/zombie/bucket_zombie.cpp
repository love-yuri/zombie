/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-07 14:04:22
 * @LastEditTime: 2023-12-08 22:29:44
 * @Description: 普通僵尸
 */
#include "hpp/tools.hpp"
#include "include/plants/plant.h"
#include "include/zombie/bucket_zombie.h"
#include "include/zombie/zombie.h"
#include <QTimer>
#include <qtimer.h>

BucketZombie::BucketZombie(GameManager *manager, int pos_i, const ZombieData &zombieData) :
  Zombie(manager, pos_i, zombieData) {
}

/* 僵尸攻击效果 */
void BucketZombie::attack(QWeakPointer<Plant> weakPlant) {
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
void BucketZombie::injuried(int blod) {
  this->blod -= blod;
  if (this->blod <= 0) {
    zom_state = 0;
    move_timer->stop();
    movie->stop();
    movie->setFileName(":/zombie/normalZombie/ZombieDie.gif");
    movie->start();
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, [this]() {
      emit deathed();
    });
    timer->start(1000);
  }
}