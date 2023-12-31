/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 18:49:14
 * @LastEditTime: 2023-12-16 20:30:23
 * @Description: 僵尸基类
 */
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "hpp/tools.hpp"
#include "include/manager/global_config.h"
#include <QGraphicsObject>
#include <qlist.h>
#include <qmovie.h>
#include <qmutex.h>
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

  /* 僵尸受伤 */
  virtual void injuried(int blod) = 0;

  virtual void destory() = 0; /* 死亡 */

  inline const bool alive() const {
    return isAlive;
  }

  inline const bool zombieDoctor() const {
    return isZombieDoctor;
  }

  void restart();
  void destoryGif(const QString &);

signals:
  void gameOver(); /* 游戏结束 */
  void deathed();  /* 僵尸死亡 */

protected:
  QPixmap pixmap;
  QMovie *movie;
  GameManager *manager;
  ZombieData zombieData;

  QList<QTimer *> timers;

  /* 僵尸属性 */
  int blod;         // 血量
  int deathedCount; // 动画计数
  bool isAlive;     // 存活状态
  bool isZombieDoctor;
  bool isAttacking;

  /* 定时器 */
  QTimer *attack_timer;
  QTimer *move_timer;

  QMutex movie_mutex;

  void move();
};

#endif