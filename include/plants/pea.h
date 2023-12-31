/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:50:06
 * @LastEditTime: 2023-12-10 15:15:12
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
  virtual ~Pea() = default;

protected:
  virtual void attack() override;

  virtual void destory() override;
};

#endif