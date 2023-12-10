/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:50:06
 * @LastEditTime: 2023-12-10 14:58:22
 * @Description: 豌豆射手
 */
#ifndef POTATO_H
#define POTATO_H

#include "include/plants/plant_slot.h"
#include "include/manager/global_config.h"
#include "plant.h"
#include <qgraphicsscene.h>
#include <qmovie.h>
#include <qpoint.h>

class Potato : public Plant {
public:
  Potato(PlantSlot *slot, const PlantData &plantData);
  virtual ~Potato() = default;

protected:
  virtual void attack() override;
  void destoryGif(QString fileName);

  virtual void destory() override;
};

#endif