/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-07 14:00:23
 * @LastEditTime: 2023-12-15 21:15:44
 * @Description: 普通僵尸
 */
#ifndef CONE_ZOMBIE_h
#define CONE_ZOMBIE_h

#include "include/zombie/zombie.h"

class ConeZombie : public Zombie {
public:
  ConeZombie(GameManager *manager, int pos_i, const ZombieData &zombieData);

  void attack(QWeakPointer<Plant>) override;
  virtual void destory() override;
  virtual void injuried(int blod) override;

  
};

#endif