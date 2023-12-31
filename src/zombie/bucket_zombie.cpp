/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-07 14:04:22
 * @LastEditTime: 2023-12-21 20:36:36
 * @Description: 普通僵尸
 */
#include "hpp/tools.hpp"
#include "include/manager/global_config.h"
#include "include/plants/plant.h"
#include "include/plants/plant_slot.h"
#include "include/zombie/bucket_zombie.h"
#include "include/zombie/zombie.h"
#include "include/manager/game_manager.h"
#include <QTimer>
#include <qtimer.h>

BucketZombie::BucketZombie(GameManager *manager, int pos_i, const ZombieData &zombieData) :
  Zombie(manager, pos_i, zombieData) {
  move();
  isAttacking = false;
}

/* 僵尸攻击效果 */
void BucketZombie::attack(QWeakPointer<Plant> weakPlant) {
  if (auto plant = weakPlant.lock()) {
    isAttacking = true;
    move_timer->stop();
    plant->attackZombie.push_back(this);

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
void BucketZombie::destory() {
  isAttacking = false;
  isAlive = false;
  move_timer->stop();
  destoryGif(":/zombie/normalZombie/ZombieDie.gif");
}

void BucketZombie::injuried(int blod) {
  this->blod -= blod;
  if (this->blod == 10) {
    movie_mutex.lock();
    movie->stop();
    QString normal = manager->globalConfig()->zombiesTypeMap().key(ZombieType::NAORMAL);
    ZombieData data = manager->globalConfig()->zombiesData().value(normal);
    zombieData.default_state = data.default_state;
    zombieData.attack_state = data.attack_state;
    if (isAttacking) {
      movie->setFileName(data.attack_state);
    } else {
      movie->setFileName(data.default_state);
    }
    movie->start();
    movie_mutex.unlock();
  }
  if (this->blod <= 0) {
    isAlive = false;
    destory();
  }
}