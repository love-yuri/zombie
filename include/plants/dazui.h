/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:50:06
 * @LastEditTime: 2023-12-10 15:47:55
 * @Description: 食人花
 */
#ifndef DAZUI_H
#define DAZUI_H

#include "include/plants/plant_slot.h"
#include "include/manager/global_config.h"
#include "plant.h"
#include <qgraphicsscene.h>
#include <qmovie.h>
#include <qpoint.h>

class Dazui : public Plant {
public:
  Dazui(PlantSlot *slot, const PlantData &plantData);
  virtual ~Dazui() = default;

protected:
  virtual void attack() override;
  virtual void destory() override;

  bool isEating;
};

#endif