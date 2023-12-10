/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-10 17:34:50
 * @LastEditTime: 2023-12-10 21:00:05
 * @Description: 太阳花的产量
 */
#ifndef SUN_NUMBER_H
#define SUN_NUMBER_H

#include "hpp/tools.hpp"
#include "include/manager/game_manager.h"
#include <QGraphicsObject>
#include <QPainter>
#include <qcolor.h>
#include <QFontMetrics>
#include <qfont.h>
#include <qmovie.h>
#include <qnamespace.h>
#include <qpen.h>
#include <qpixmap.h>
#include <qpropertyanimation.h>

class SunNumber : public QGraphicsObject {
public:
  SunNumber(GameManager *manager) :
    manager(manager) {
    // pixmap = QPixmap(100, 50);
    setZValue(20);
    setPos(502, 77);
  }

  virtual ~SunNumber() {
  }

  QRectF boundingRect() const override {
    return QRectF(0, 0, 50, 25);
  }

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing);
    QFont font("", 16);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(boundingRect(), Qt::AlignCenter, QString("%1").arg(manager->sun()));
  }

private:
  QPixmap pixmap;
  GameManager *manager;
};

#endif