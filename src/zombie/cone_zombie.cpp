/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-07 14:04:22
 * @LastEditTime: 2023-12-15 21:18:40
 * @Description: 普通僵尸
 */
#include "hpp/tools.hpp"
#include "include/manager/global_config.h"
#include "include/plants/plant.h"
#include "include/zombie/cone_zombie.h"
#include "include/manager/game_manager.h"
#include "include/zombie/zombie.h"
#include <QTimer>
#include <qtimer.h>

ConeZombie::ConeZombie(GameManager *manager, int pos_i, const ZombieData &zombieData) :
  Zombie(manager, pos_i, zombieData) {
  move();
}

/* 僵尸攻击效果 */
void ConeZombie::attack(QWeakPointer<Plant> weakPlant) {
  if (auto plant = weakPlant.lock()) {
    attack_timer->start(zombieData.interval);
    connect(attack_timer, &QTimer::timeout, [this, weakPlant]() {
      if (auto plant = weakPlant.lock()) {
        plant->injuried(zombieData.hurt);
      }
    });
    move_timer->stop();
    plant->attackZombie.push_back(this);

    /* 更换攻击动画 */
    movie->stop();
    movie->setFileName(zombieData.attack_state);
    movie->start();
  }
}

/* 受伤效果 */
void ConeZombie::destory() {
  isAlive = false;
  move_timer->stop();
  destoryGif(":/zombie/normalZombie/ZombieDie.gif");
}

void ConeZombie::injuried(int blod) {
  this->blod -= blod;
  if (this->blod == 10) {
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
  }
  if (this->blod <= 0) {
    isAlive = false;
    destory();
  }
}