/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-07 14:00:23
 * @LastEditTime: 2023-12-08 21:06:04
 * @Description: 普通僵尸
 */
#ifndef BUCKET_ZOMBIE_H
#define BUCKET_ZOMBIE_H

#include "include/zombie/zombie.h"

class BucketZombie : public Zombie {
public:
  BucketZombie(GameManager *manager, int pos_i, const ZombieData &zombieData);

  void attack(QWeakPointer<Plant>) override;
  virtual void injuried(int blod) override;
};

#endif