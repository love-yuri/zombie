/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 17:50:06
 * @LastEditTime: 2023-12-10 22:32:57
 * @Description: 豌豆射手
 */
#ifndef CHERRY_H
#define CHERRY_H

#include "include/plants/plant_slot.h"
#include "include/manager/global_config.h"
#include "plant.h"
#include <qgraphicsscene.h>
#include <qmovie.h>
#include <qpoint.h>

class Cherry : public Plant {
public:
  Cherry(PlantSlot *slot, const PlantData &plantData);
  virtual ~Cherry() = default;

protected:
  virtual void attack() override;
  void destoryGif(QString fileName);
  void boom(int x, int y);

  virtual void destory() override;
};

#endif