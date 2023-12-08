/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 11:04:50
 * @LastEditTime: 2023-12-08 20:49:04
 * @Description: 植物基类
 */
#ifndef PLANT_H
#define PLANT_H

#include "include/plants/plant_slot.h"
#include "include/manager/global_config.h"
#include <QGraphicsObject>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qtimer.h>
#include <qtmetamacros.h>

class Zombie;
class Plant : public QObject {
  Q_OBJECT
public:

  Plant(PlantSlot *slot, const PlantData &plantData);
  virtual ~Plant();

  /* 坐标标识 */
  QPoint ij;

  /* 植物方法 */
  virtual void attack() = 0; /* 攻击 */
  virtual void injuried(int blod) = 0; /* 受伤 */

  inline const PlantSlot *plantSlot() {
    return slot;
  }

  Zombie *attackZombie;

signals:
  void deathed(); /* 植物死亡 */
  void near(); /* 僵尸靠近 */

protected:
  PlantSlot *slot;
  QPixmap *pixmap;
  QMovie *movie;
  const PlantData plantData;
  QGraphicsScene *scene;
  GameManager *manager;

  QList<QGraphicsItem *> items;

  /* 植物属性 */
  int blod;     // 血量

  /* 定时器 */
  QTimer *attack_timer;
};

#endif