/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 19:49:24
 * @LastEditTime: 2023-12-08 20:35:24
 * @Description: 游戏管理器
 */
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "include/manager/global_config.h"
#include "include/plants/plant.h"
#include "include/zombie/zombie.h"
#include <qcontainerfwd.h>
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

  inline const QList<QPoint> &zombiePos() const {
    return zombie_pos;
  }

  inline QList<QTimer *> &allTimers() {
    return timers;
  }

  plant_ptr createPlant(QString, PlantSlot *);
  zombie_ptr createZombie(ZombieType, int);

  QWeakPointer<Plant> firstPlant(int i) {
    if (i >= plant_list.size() || plant_list[i].isEmpty()) {
      return QWeakPointer<Plant>();
    }
    return plant_list[i].first();
  }

  QWeakPointer<Zombie> firstZombie(int i) {
    if (i >= zombie_list.size() || zombie_list[i].isEmpty()) {
      return QWeakPointer<Zombie>();
    }
    return zombie_list[i].first();
  }

private:
  QVector<QVector<QPoint>> pos_map;
  QVector<QList<plant_ptr>> plant_list;
  QVector<QList<zombie_ptr>> zombie_list;
  QList<QPoint> zombie_pos;

  QList<QTimer *> timers;

  QGraphicsScene *scene;
  GlobalConfig *config;
  // QVector<QSet<Zombie>> zombie_list;
};

#endif