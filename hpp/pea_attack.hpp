/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-08 20:14:25
 * @LastEditTime: 2023-12-10 16:10:42
 * @Description: 豌豆射手的种子
 */
#ifndef PEA_ATTACK_HPP
#define PEA_ATTACK_HPP

#include "hpp/tools.hpp"
#include "include/manager/game_manager.h"
#include "include/plants/plant.h"
#include <QGraphicsObject>
#include <QTimer>
#include <qgraphicswidget.h>
#include <qpixmap.h>
#include <QPainter>
#include <QGraphicsScene>
#include <qtpreprocessorsupport.h>

class PeaAttack : public QGraphicsObject {
public:
  PeaAttack(QString fileName) :
    pixmap(QPixmap(fileName)) {
    move_timer = new QTimer(this);
  }

  virtual ~PeaAttack() {
  }
  QRectF boundingRect() const override {
    return QRectF(pixmap.rect());
  }
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPixmap(pixmap.rect(), pixmap);
  }

  void start(int inverval, Plant *plant, GameManager *manager, int hurt) {
    move_timer->start(30);
    connect(move_timer, &QTimer::timeout, [this, hurt, manager, plant]() {
      setPos(pos() + QPointF(10, 0));
      update();
      if (auto zombie = manager->firstZombie(plant->ij.x()).lock()) {
        if (pos().x() >= scene()->sceneRect().width()) {
          scene()->removeItem(this);
          // items.removeOne(this);
          move_timer->stop();
          deleteLater();
        } else if (zombie->alive() && collidesWithItem(zombie.data())) {
          zombie->injuried(hurt);
          move_timer->stop();
          scene()->removeItem(this);
          deleteLater();
          // items.removeOne(attack);
        }
      }
    });
  }

private:
  QPixmap pixmap;
  QTimer *move_timer;
  ;
};

#endif