/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-05 17:37:15
 * @LastEditTime: 2023-12-05 22:14:44
 * @Description: 植物卡片
 */

#include "include/plants/plant_slot.h"
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QDrag>
#include <qdrag.h>
#include <QMimeData>
#include <qpixmap.h>
#include "hpp/tools.hpp"
#include "include/manager/plant_config.h"
#include <QPainter>
#include <qcolor.h>
#include <qevent.h>
#include <qmimedata.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qsize.h>
PlantSlot::PlantSlot() {
  setAcceptDrops(true);
  pixmap = QPixmap(81, 81);
  pixmap.fill(QColor(0, 0, 0, 120));
}

QRectF PlantSlot::boundingRect() const {
  return QRectF(pixmap.rect());
}

void PlantSlot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  painter->setRenderHint(QPainter::Antialiasing);
  painter->drawPixmap(pixmap.rect(), pixmap);
}

void PlantSlot::dropEvent(QGraphicsSceneDragDropEvent *event) {
  PlantConfig::Plant plant = PlantConfig::allPlants().value(event->mimeData()->text());
  QPixmap img(QPixmap(plant.img).scaled(pixmap.size()));
  pixmap.swap(img);
  update();
}