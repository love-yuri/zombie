/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:50:06
 * @LastEditTime: 2023-12-08 14:07:14
 * @Description: 豌豆射手
 */
#ifndef PEA_H
#define PEA_H

#include "include/plants/plant_slot.h"
#include "include/manager/global_config.h"
#include "plant.h"
#include <qgraphicsscene.h>
#include <qmovie.h>
#include <qpoint.h>

class Pea : public Plant {
public:
  Pea(PlantSlot *slot, const PlantData &plantData);
  virtual ~Pea();

protected:
  virtual void attack() override;
  virtual void injuried(int blod) override;

  void destory();
};

#endif