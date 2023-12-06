/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 11:04:50
 * @LastEditTime: 2023-12-06 21:40:14
 * @Description: 植物基类 
 */
#ifndef PLANT_H
#define PLANT_H

#include "include/manager/plant_config.h"
#include "include/plants/plant_slot.h"
#include <QGraphicsObject>
#include <qgraphicsscene.h>
#include <qpixmap.h>
#include <qpoint.h>

class Plant : public QObject {
public:
  Plant(PlantSlot *slot, PlantConfig::PlantData plantData);
  virtual ~Plant() = default;

  /* 坐标标识 */
  QPoint ij;

  // /* 植物方法 */
  // virtual void attack() = 0;
  // virtual void injuried() = 0;
  // virtual void death() = 0;

  bool operator<(const Plant &p) const;

protected:
  PlantSlot *slot;
  QPixmap *pixmap;
  PlantConfig::PlantData plantData;
  QGraphicsScene *scene;
  GameManager *manager;

  /* 植物属性 */
  int blod;
  int hurt;
  int sum;
  int cd;
  int interval;
};

#endif