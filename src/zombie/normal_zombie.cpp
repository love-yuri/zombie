/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-07 14:04:22
 * @LastEditTime: 2023-12-09 13:23:15
 * @Description: 普通僵尸
 */
#include "hpp/tools.hpp"
#include "include/plants/plant.h"
#include "include/zombie/nomal_zombie.h"
#include "include/zombie/zombie.h"
#include <QTimer>
#include <qtimer.h>

NormalZombie::NormalZombie(GameManager *manager, int pos_i, const ZombieData &zombieData) :
  Zombie(manager, pos_i, zombieData) {
}

/* 僵尸攻击效果 */
void NormalZombie::attack(QWeakPointer<Plant> weakPlant) {
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
void NormalZombie::destory() {
  isAlive = false;
  move_timer->stop();
  destoryGif(":/zombie/normalZombie/ZombieDie.gif");
}