/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:50:06
 * @LastEditTime: 2023-12-09 14:04:26
 * @Description: 豌豆射手
 */
#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "include/plants/plant_slot.h"
#include "include/manager/global_config.h"
#include "plant.h"
#include <qgraphicsscene.h>
#include <qmovie.h>
#include <qpoint.h>

class SunFlower : public Plant {
public:
  SunFlower(PlantSlot *slot, const PlantData &plantData);
  virtual ~SunFlower() = default;

protected:
  virtual void attack() override;
  virtual void destory() override;

};

#endif