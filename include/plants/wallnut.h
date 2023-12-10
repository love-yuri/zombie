/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:50:06
 * @LastEditTime: 2023-12-09 14:08:01
 * @Description: 豌豆射手
 */
#ifndef WALLNUT_H
#define WALLNUT_H

#include "include/plants/plant_slot.h"
#include "include/manager/global_config.h"
#include "plant.h"
#include <qgraphicsscene.h>
#include <qmovie.h>
#include <qpoint.h>

class Wallnut : public Plant {
public:
  Wallnut(PlantSlot *slot, const PlantData &plantData);
  virtual ~Wallnut() = default;

protected:
  virtual void attack() override;
  virtual void destory() override;

};

#endif