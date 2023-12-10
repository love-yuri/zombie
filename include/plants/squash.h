/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:50:06
 * @LastEditTime: 2023-12-10 16:26:27
 * @Description: 食人花
 */
#ifndef SQUASH_H
#define SQUASH_H

#include "include/plants/plant_slot.h"
#include "include/manager/global_config.h"
#include "plant.h"
#include <qgraphicsscene.h>
#include <qmovie.h>
#include <qpoint.h>

class Squash : public Plant {
public:
  Squash(PlantSlot *slot, const PlantData &plantData);
  virtual ~Squash() = default;

protected:
  virtual void attack() override;
  virtual void destory() override;

  bool isEating;
};

#endif