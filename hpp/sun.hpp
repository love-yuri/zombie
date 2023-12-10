/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-10 17:34:50
 * @LastEditTime: 2023-12-10 21:59:48
 * @Description: 太阳花
 */
#ifndef SUN_H
#define SUN_H

#include "hpp/tools.hpp"
#include "include/manager/game_manager.h"
#include <QGraphicsObject>
#include <QPainter>
#include <qmovie.h>
#include <qpixmap.h>
#include <qpropertyanimation.h>

class Sun : public QGraphicsObject {
public:
  Sun(GameManager *manager) :
    manager(manager) {
    setZValue(22);
    movie = new QMovie(":/Sun.gif");
    animation = new QPropertyAnimation(this, "pos");
    animation->setParent(this);
    animation->setDuration(1000);
    pixmap = QPixmap("Sun.gif");
    connect(movie, &QMovie::frameChanged, [this] {
      pixmap = movie->currentPixmap();
      update();
    });
    movie->start();
  }

  virtual ~Sun() {
    movie->stop();
    delete movie;
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

  void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
  }
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
    Q_UNUSED(event);
    manager->addSun();
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    moveTo(QPoint(0, 0));
    connect(timer, &QTimer::timeout, [this] {
      scene()->removeItem(this);
      this->deleteLater();
    });
    timer->start(1000);
  }

  void moveTo(QPointF p) {
    animation->stop();
    animation->setStartValue(QPointF(pos()));
    animation->setEndValue(QPointF(p));
    animation->start();
  }

private:
  QPixmap pixmap;
  QMovie *movie;
  QPropertyAnimation *animation;
  GameManager *manager;
};

#endif