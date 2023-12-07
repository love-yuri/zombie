/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 19:49:24
 * @LastEditTime: 2023-12-07 22:26:32
 * @Description: 游戏管理器
 */
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "include/manager/plant_config.h"
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

class GameManager : public QObject {
  Q_OBJECT
public:
  using plant_ptr = QSharedPointer<Plant>;
  using zombie_ptr = QSharedPointer<Zombie>;
  
public:
  GameManager(QObject *parent, QGraphicsScene *scene);
  virtual ~GameManager();
  inline const QVector<QVector<QPoint>> posMap() {
    return pos_map;
  }

  inline QVector<QList<plant_ptr>> &plantList() {
    return plant_list;
  }

  inline QVector<QList<zombie_ptr>> &zombieList() {
    return zombie_list;
  }

  inline QList<QPoint> &
    zombiePos() {
    return zombie_pos;
  }

  void addPlant(plant_ptr);
  void addZombie(zombie_ptr);

private:
  QVector<QVector<QPoint>> pos_map;
  QVector<QList<plant_ptr>> plant_list;
  QVector<QList<zombie_ptr>> zombie_list;
  QList<QPoint> zombie_pos;

  QGraphicsScene *scene;
  // QVector<QSet<Zombie>> zombie_list;
};

#endif