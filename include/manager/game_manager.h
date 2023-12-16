/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 19:49:24
 * @LastEditTime: 2023-12-16 22:47:44
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

  inline QVector<QList<plant_ptr>> &plantList() {
    return plant_list;
  }

  inline QVector<QList<zombie_ptr>> &zombieList() {
    return zombie_list;
  }

  inline QVector<QVector<PlantSlot *>> &slotList() {
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

  inline const GlobalConfig *globalConfig() const {
    return config;
  }

  QWeakPointer<Plant> firstPlant(int i) ;
  QWeakPointer<Zombie> firstZombie(int i, const QPointF &pos);
  plant_ptr createPlant(QString, PlantSlot *);
  zombie_ptr createZombie(ZombieType, int);
  void createZombieDoctor();
  void start(const QList<QString> &plants); /* 游戏开始全局处理 */
  void addSun();
  void delSun(int val);

signals:
  void victory();
  void gameOver();

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
  int zom_num;
};

#endif