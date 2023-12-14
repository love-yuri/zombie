/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-07 14:00:23
 * @LastEditTime: 2023-12-14 20:49:09
 * @Description: 普通僵尸
 */
#ifndef ZOMBIE_DOCTOR_h
#define ZOMBIE_DOCTOR_h

#include "include/zombie/zombie.h"

class ZombieDoctor : public Zombie {
public:
  ZombieDoctor(GameManager *manager, int pos_i, const ZombieData &zombieData);

  void attack(QWeakPointer<Plant>) override;
  virtual void destory() override;
  virtual void injuried(int blod) override;

protected:
  
  void move();
};

#endif