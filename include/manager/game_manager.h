#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "include/manager/plant_config.h"
#include "include/zombie/zombie.h"
#include "include/plants/plant.h"
#include <qcontainerfwd.h>
#include <QVector>
#include <qlist.h>
#include <qobject.h>
#include <qpoint.h>
#include <QSet>

class GameManager : public QObject {
  Q_OBJECT
public:
  GameManager(QObject *parent);
  virtual ~GameManager();
  const QVector<QVector<QPoint>> posMap() {
    return pos_map;
  }

  inline QVector<QList<Plant*>>& plantList() {
    return plant_list;
  }

  void addPlant(Plant *, int i);

private:
  QVector<QVector<QPoint>> pos_map;
  QVector<QList<Plant*>> plant_list;
  // QVector<QSet<Zombie>> zombie_list;
};

#endif