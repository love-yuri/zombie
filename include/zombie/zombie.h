/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 18:49:14
 * @LastEditTime: 2023-12-07 18:58:01
 * @Description: 僵尸基类
 */
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "include/manager/zombie_config.h"
#include <QGraphicsObject>
#include <qmovie.h>
#include <qtmetamacros.h>

class GameManager;
class Plant;

class Zombie : public QGraphicsObject {
public:
  using plant_ptr = QSharedPointer<Plant>;
  using zombie_ptr = QSharedPointer<Zombie>;
  Q_OBJECT
public:
  Zombie(GameManager *manager, int pos_i, const ZombieConfig::ZombieData &zombieData);
  virtual ~Zombie();

  int pos_i;

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  virtual void attack(plant_ptr) = 0; /* 攻击 */
  virtual void injuried(int blod) = 0; /* 僵尸受伤 */
  // virtual void injuried() = 0;

signals:
  void gameOver();/* 游戏结束 */
  void deathed(); /* 僵尸死亡 */

protected:
  QPixmap pixmap;
  QMovie *movie;
  GameManager *manager;
  const ZombieConfig::ZombieData zombieData;


  /* 僵尸属性 */
  int blod; // 血量

  /* 定时器 */
  QTimer *attack_timer;
  QTimer *move_timer;

  void move();
};

#endif