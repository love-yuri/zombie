/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-04 17:41:17
 * @LastEditTime: 2023-12-11 16:18:20
 * @Description:
 */
#include "include/share/card_item.h"
#include "include/manager/card_manager.h"
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
CardItem::CardItem(CardManager *manager, int id) :
  id(id), pixmap(new QPixmap(45, 65)), manager(manager) {
  setAcceptedMouseButtons(Qt::LeftButton);
  pixmap->fill(QColor(0, 0, 0, 60));
  setAcceptDrops(true);
  setZValue(5);
}
CardItem::CardItem(CardManager *manager, QString file_name, int id) :
  pixmap(new QPixmap(file_name)), file_name(file_name), id(id), manager(manager) {
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

void CardItem::clear() {
  QPixmap img(45, 65);
  img.fill(QColor(0, 0, 0, 60));
  pixmap->swap(img);
  file_name.clear();
  name_y.clear();
  update();
}

void CardItem::mousePressEvent(QGraphicsSceneMouseEvent *) {
  // qinfo << "点击";
}

void CardItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  if (file_name.isEmpty()) {
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
  mimeData->setText(QString("%1").arg(id));
  darg->setPixmap(pix);
  darg->exec();
  // qinfo << "结束" << event->isAccepted();
}

void CardItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *) {
  if (file_name.isEmpty()) {
    return;
  }
  CardItem *item = manager->filstCard(id);
  if (item != nullptr) {
    item->setCard(this);
  }
}

void CardItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
  // qinfo << "靠近";
}

void CardItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
  Q_UNUSED(event);
}

void CardItem::dropEvent(QGraphicsSceneDragDropEvent *event) {
  if (!file_name.isEmpty()) {
    return;
  }
  CardItem *item = manager->plantVec().at(event->mimeData()->text().toInt());
  file_name = item->fileName();
  name_y = item->name();
  QPixmap img(QPixmap(file_name).scaled(QSize(45, 65)));
  pixmap->swap(img);
  item->clear();
  update();
}

const QString &CardItem::fileName() const {
  return file_name;
}

void CardItem::setCard(CardItem *item) {
  file_name = item->fileName();
  name_y = item->name();
  QPixmap img(QPixmap(file_name).scaled(QSize(45, 65)));
  pixmap->swap(img);
  item->clear();
  update();
}
