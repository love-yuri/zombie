/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-04 17:41:17
 * @LastEditTime: 2023-12-04 22:41:37
 * @Description:
 */
#include "include/share/card_item.h"
#include "hpp/tools.hpp"

#include <QPainter>
#include <qcolor.h>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <qdrag.h>
#include <qevent.h>
#include <qmimedata.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qsize.h>
CardItem::CardItem() :
  pixmap(new QPixmap(45, 65)) {
  setAcceptedMouseButtons(Qt::LeftButton);
  pixmap->fill(QColor(0, 0, 0, 60));
  setAcceptDrops(true);
  setZValue(5);
}
CardItem::CardItem(QString fileName) :
  pixmap(new QPixmap(fileName)), fileName(fileName) {
  setAcceptedMouseButtons(Qt::LeftButton);
  QPixmap p(pixmap->scaled(QSize(45, 65)));
  pixmap->swap(p);
  setAcceptDrops(true);
  setZValue(5);
}

CardItem::~CardItem() {
  delete pixmap;
}

QRectF CardItem::boundingRect() const {
  return QRectF(pixmap->rect());
}

void CardItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  painter->setRenderHint(QPainter::Antialiasing);
  painter->drawPixmap(pixmap->rect(), *pixmap);
}

void CardItem::mousePressEvent(QGraphicsSceneMouseEvent *) {
  // qinfo << "点击";
}

void CardItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  if (fileName.isEmpty()) {
    return;
  }
  if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length()
      < QApplication::startDragDistance()) {
    return;
  }
  QDrag *darg = new QDrag(event->widget());
  QMimeData *mimeData = new QMimeData;
  darg->setMimeData(mimeData);
  QPixmap pix(pixmap->size());
  QPainter painter(&pix);
  paint(&painter, nullptr, nullptr);
  mimeData->setText(fileName);
  darg->setPixmap(pix);
  darg->exec();
  // qinfo << "结束" << event->isAccepted();
}

void CardItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *) {
  // qinfo << "放开n";
}

void CardItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
  // qinfo << "靠近";
}

void CardItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
  Q_UNUSED(event);
}

void CardItem::dropEvent(QGraphicsSceneDragDropEvent *event) {
  QPixmap img(QPixmap(event->mimeData()->text()).scaled(QSize(45, 65)));
  pixmap->swap(img);
  fileName = event->mimeData()->text();
  update();
}
