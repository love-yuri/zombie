/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 19:49:24
 * @LastEditTime: 2023-12-11 14:24:28
 * @Description: 游戏管理器
 */
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

class SunNumber;

#include "include/manager/global_config.h"
#include "include/plants/plant.h"
#include "include/zombie/zombie.h"
#include "include/plants/plant_card.h"
#include <qcontainerfwd.h>
#include <QReadWriteLock>
#include <QVector>
#include <QSharedPointer>
#include <qgraphicsscene.h>
#include <qlist.h>
#include <qobject.h>
#include <qpoint.h>
#include <QSet>

using plant_ptr = QSharedPointer<Plant>;
using zombie_ptr = QSharedPointer<Zombie>;

class GameManager : public QObject {
  Q_OBJECT
public:
  GameManager(QObject *parent, QGraphicsScene *scene, GlobalConfig *config);
  virtual ~GameManager();

  inline const QVector<QVector<QPoint>> posMap() const {
    return pos_map;
  }

  inline const QVector<QList<plant_ptr>> &plantList() const {
    return plant_list;
  }

  inline const QVector<QList<zombie_ptr>> &zombieList() const {
    return zombie_list;
  }

  inline const QVector<QVector<PlantSlot *>> &slotList() const {
    return slot_list;
  }

  inline const QList<QPoint> &zombiePos() const {
    return zombie_pos;
  }

  inline QList<QTimer *> &allTimers() {
    return timers;
  }

  inline const int sun() const {
    return sun_;
  }

  inline QList<PlantCard *> & plantCards() {
    return plant_cards;
  }

  QWeakPointer<Plant> firstPlant(int i) ;
  QWeakPointer<Zombie> firstZombie(int i);
  plant_ptr createPlant(QString, PlantSlot *);
  zombie_ptr createZombie(ZombieType, int);
  void start(const QList<QString> &plants); /* 游戏开始全局处理 */
  void addSun();
  void delSun(int val);

private:
  QVector<QVector<QPoint>> pos_map;
  QVector<QList<plant_ptr>> plant_list;
  QVector<QList<zombie_ptr>> zombie_list;
  QVector<QVector<PlantSlot*>> slot_list;
  QList<QPoint> zombie_pos;
  QList<plant_ptr> plant_list_temp;

  QList<QTimer *> timers;
  QList<PlantCard *> plant_cards;

  QGraphicsScene *scene;
  GlobalConfig *config;
  SunNumber *sun_number;
  QReadWriteLock plant_lock;
  QReadWriteLock zombie_lock;
  int sun_;
};

#endif