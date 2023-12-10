/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:50:06
 * @LastEditTime: 2023-12-10 15:15:35
 * @Description: 豌豆射手
 */
#ifndef DOUBLE_PEA_H
#define DOUBLE_PEA_H

#include "include/plants/plant_slot.h"
#include "include/manager/global_config.h"
#include "plant.h"
#include <qgraphicsscene.h>
#include <qmovie.h>
#include <qpoint.h>

class DoublePea : public Plant {
public:
  DoublePea(PlantSlot *slot, const PlantData &plantData);
  virtual ~DoublePea() = default;

protected:
  virtual void attack() override;

  virtual void destory() override;
};

#endif