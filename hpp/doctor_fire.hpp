/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-08 20:14:25
 * @LastEditTime: 2023-12-15 17:55:21
 * @Description: 获
 */
#ifndef DOCTOR_FIRE_HPP
#define DOCTOR_FIRE_HPP

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

class DoctorFire : public QGraphicsObject {
public:
  DoctorFire(QString fileName) :
    pixmap(QPixmap(fileName)) {
    move_timer = new QTimer(this);
    setZValue(40);
    movie = new QMovie(fileName);
    connect(movie, &QMovie::frameChanged, [this] {
      pixmap = movie->currentPixmap();
      update();
    });
    connect(movie, &QMovie::finished, [this] {
      scene()->removeItem(this);
      deleteLater();
    });
    movie->start();
  }

  virtual ~DoctorFire() {
    movie->stop();
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

private:
  QPixmap pixmap;
  QTimer *move_timer;
  QMovie *movie;
};

#endif