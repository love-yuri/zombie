/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-07 14:04:22
 * @LastEditTime: 2023-12-07 21:50:47
 * @Description: 普通僵尸
 */
#include "hpp/tools.hpp"
#include "include/plants/plant.h"
#include "include/zombie/nomal_zombie.h"
#include "include/zombie/zombie.h"
#include <QTimer>
#include <qtimer.h>

NormalZombie::NormalZombie(GameManager *manager, int pos_i, ZombieConfig::ZombieData zombieData) :
  Zombie(manager, pos_i, zombieData) {
}

/* 僵尸攻击效果 */
void NormalZombie::attack(QSharedPointer<Plant>) {
  move_timer->stop();
  movie->stop();
  movie->setFileName(this->zombieData.attack_state);
  movie->start();
}

/* 受伤效果 */
void NormalZombie::injuried(int blod) {
  this->blod -= blod;
  // qinfo << this->blod;
  if (this->blod <= 0) {
    move_timer->stop();
    // scene()->removeItem(this);
    emit deathed();
  }
}