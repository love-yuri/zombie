#ifndef NORMAL_ZOMBIE_h
#define NORMAL_ZOMBIE_h

#include "include/zombie/zombie.h"

class NormalZombie : public Zombie {
public:
  NormalZombie(GameManager *manager, int pos_i, ZombieConfig::ZombieData zombieData);

  void attack(plant_ptr) override;
  virtual void injuried(int blod) override;
};

#endif