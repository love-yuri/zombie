/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:50:06
 * @LastEditTime: 2023-12-12 14:45:08
 * @Description: 豌豆射手
 */
#ifndef TALLNUT_H
#define TALLNUT_H

#include "include/plants/plant_slot.h"
#include "include/manager/global_config.h"
#include "plant.h"
#include <qgraphicsscene.h>
#include <qmovie.h>
#include <qpoint.h>

class Tallnut : public Plant {
public:
  Tallnut(PlantSlot *slot, const PlantData &plantData);
  virtual ~Tallnut() = default;
  virtual void injuried(int blod) override;

protected:
  virtual void attack() override;
  virtual void destory() override;

};

#endif