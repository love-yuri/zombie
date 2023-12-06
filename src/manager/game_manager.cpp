#include "include/manager/game_manager.h"
#include "hpp/tools.hpp"
#include "include/plants/plant.h"
#include <qcontainerfwd.h>
#include <qlist.h>
#include <qpoint.h>

GameManager::GameManager(QObject *parent) :
  QObject(parent) {
  /* 初始化位置map */
  for (int i = 0; i < 5; i++) {
    QVector<QPoint> vec;
    for (int j = 0; j < 9; j++) {
      QPoint p(77 + j * 84, 90 + i * 94);
      vec.push_back(p);
    }
    pos_map.push_back(vec);
  }
  plant_list = QVector<QList<Plant *>>(pos_map.size());
}

GameManager::~GameManager() {
  for (QList<Plant *> plant : plant_list) {
    QString s;
    for (Plant *p : plant) {
      s = QString("%1 %2").arg(s).arg(p->ij.y());
    }
    qinfo << s;
  }
}

void GameManager::addPlant(Plant *plant, int i) {
  plant_list[i].push_back(plant);
  QList<Plant *> &list = plant_list[i];
  std::sort(list.begin(), list.end(), [](Plant *a, Plant *b) {
    return a->ij.y() < b->ij.y();
  });
}