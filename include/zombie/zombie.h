/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 18:49:14
 * @LastEditTime: 2023-12-08 22:16:00
 * @Description: 僵尸基类
 */
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "include/manager/global_config.h"
#include <QGraphicsObject>
#include <qlist.h>
#include <qmovie.h>
#include <qtmetamacros.h>

class GameManager;
class Plant;

class Zombie : public QGraphicsObject {

  Q_OBJECT
public:
  Zombie(GameManager *manager, int pos_i, const ZombieData &zombieData);
  virtual ~Zombie();

  int pos_i;

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  virtual void attack(QWeakPointer<Plant>) = 0; /* 攻击 */
  virtual void injuried(int blod) = 0; /* 僵尸受伤 */
  // virtual void injuried() = 0;

  inline const int state() const {
    return zom_state;
  }

  void restart();
  void destoryGif(QWeakPointer<Zombie>);

signals:
  void gameOver();/* 游戏结束 */
  void deathed(); /* 僵尸死亡 */

protected:
  QPixmap pixmap;
  QMovie *movie;
  GameManager *manager;
  const ZombieData zombieData;

  QList<QTimer *> timers;


  /* 僵尸属性 */
  int blod; // 血量
  int zom_state; // 状态

  /* 定时器 */
  QTimer *attack_timer;
  QTimer *move_timer;

  void move();
};

#endif