/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 20:46:20
 * @LastEditTime: 2023-12-07 22:57:07
 * @Description:
 */
#include "include/manager/game_manager.h"
#include "hpp/tools.hpp"
#include "include/plants/plant.h"
#include "include/zombie/zombie.h"
#include <qcontainerfwd.h>
#include <QSharedPointer>
#include <qgraphicsscene.h>
#include <qlist.h>
#include <qpoint.h>
#include <qtimer.h>

GameManager::GameManager(QObject *parent, QGraphicsScene *scene) :
  QObject(parent), scene(scene) {
  /* 初始化位置map */
  for (int i = 0; i < 5; i++) {
    QVector<QPoint> vec;
    for (int j = 0; j < 9; j++) {
      QPoint p(77 + j * 84, 90 + i * 94);
      vec.push_back(p);
    }
    zombie_pos.push_back(QPoint(vec.back()) + QPoint(90, -20));
    pos_map.push_back(vec);
  }
  plant_list = QVector<QList<plant_ptr>>(pos_map.size());
  zombie_list = QVector<QList<zombie_ptr>>(pos_map.size());
}

GameManager::~GameManager() {
  // for (QList<Plant *> plant : plant_list) {
  //   QString s;
  //   for (Plant *p : plant) {
  //     s = QString("%1 %2").arg(s).arg(p->ij.y());
  //   }
  //   qinfo << s;
  // }
  // for (QList<Zombie *> zombies : zombie_list) {
  //   QString s;
  //   for (Zombie *zombie : zombies) {
  //     s = QString("%1 %2").arg(s).arg(zombie->pos_i);
  //   }
  //   qinfo << s;
  // }
}

void GameManager::addPlant(plant_ptr plant) {
  plant_list[plant->ij.x()].push_back(plant);
  QList<plant_ptr> &list = plant_list[plant->ij.x()];
  std::sort(list.begin(), list.end(), [](plant_ptr a, plant_ptr b) {
    return a->ij.y() < b->ij.y();
  });
  qinfo << plant_list[plant->ij.x()].size();
  connect(plant.data(), &Plant::deathed, [this, plant]() {
    plant_list[plant->ij.x()].removeOne(plant);
  });
}

void GameManager::addZombie(zombie_ptr zombie) {
  zombie_list[zombie->pos_i].push_back(zombie);
  // QList<Zombie *> &list = zombie_list[i];
  // std::sort(list.begin(), list.end(), [](Zombie *a, Zombie *b) {
  //   return a->pos_i < b->pos_i;
  // });
  // connect(zombie.data(), &Zombie::deathed, [this, zombie]() {
  //   zombie_list[zombie->pos_i].removeOne(zombie);
  //   zombie->disconnect();
  //   zombie->scene()->removeItem(z ombie.data());
  //   zombie->deleteLater();
  // });
}