/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-05 17:37:15
 * @LastEditTime: 2023-12-06 09:55:09
 * @Description: 植物卡片
 */

#include "include/plants/plant_card.h"
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QDrag>
#include <qdrag.h>
#include <QMimeData>
#include <qpixmap.h>
#include "hpp/tools.hpp"
#include <QPainter>
#include <qcolor.h>
#include <qevent.h>
#include <qmimedata.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qsize.h>
PlantCard::PlantCard(QString file_name, QString file_name_drop) :
  pixmap(QPixmap(file_name).scaled(45, 65)),
  drop_pixmap(QPixmap(file_name_drop).scaled(60, 60)) {
  setAcceptedMouseButtons(Qt::LeftButton);
  setAcceptDrops(true);
}

QRectF PlantCard::boundingRect() const {
  return QRectF(pixmap.rect());
}

void PlantCard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  painter->setRenderHint(QPainter::Antialiasing);
  painter->drawPixmap(pixmap.rect(), pixmap);
}
void PlantCard::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length()
      < QApplication::startDragDistance()) {
    return;
  }
  QDrag *darg = new QDrag(event->widget());
  QMimeData *mimeData = new QMimeData;
  mimeData->setText(plant_name);
  darg->setPixmap(drop_pixmap);
  darg->setMimeData(mimeData);
  darg->setHotSpot(QPoint(30, 30));
  darg->exec();
  // qinfo << "结束" << event->isAccepted();
}