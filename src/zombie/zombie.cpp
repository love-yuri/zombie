/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 18:51:57
 * @LastEditTime: 2023-12-06 20:26:01
 * @Description: 僵尸基类
 */
#include "include/zombie/zombie.h"
#include "hpp/tools.hpp"
#include <QPainter>
#include <qnamespace.h>
#include <qpen.h>
#include <qpixmap.h>
#include <qtimer.h>

Zombie::Zombie() {
  // setZValue(60);

  movie = new QMovie("/home/yuri/Documents/F95D39BF6C281CA828AFC0286ED5BC4B.gif");
  pixmap = QPixmap("/home/yuri/Documents/F95D39BF6C281CA828AFC0286ED5BC4B.gif");
  connect(movie, &QMovie::frameChanged, [this] {
    pixmap = movie->currentPixmap().scaled(pixmap.size());
    update();
  });
  movie->start();

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, [this, timer]() {
    setPos(pos() - QPointF(1, 0));
  });
  timer->start(200);
}

Zombie::~Zombie() {
  movie->stop();
  delete movie;
}

QRectF Zombie::boundingRect() const {
  return QRectF(pixmap.rect());
}

void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  painter->setRenderHint(QPainter::Antialiasing);
  QPen pen(Qt::red);
  pen.setWidth(2);
  painter->setPen(pen);
  painter->drawRect(pixmap.rect());
  painter->drawPixmap(pixmap.rect(), pixmap);
}

void Zombie::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
  qinfo << "植物靠近";
}
void Zombie::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
  qinfo << "植物离开";
}