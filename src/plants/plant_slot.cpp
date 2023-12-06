/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-05 17:37:15
 * @LastEditTime: 2023-12-06 21:44:49
 * @Description: 植物卡片
 */

#include "include/plants/plant_slot.h"
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QDrag>
#include <qdrag.h>
#include <QMimeData>
#include <qmovie.h>
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
PlantSlot::PlantSlot(QGraphicsScene *scene, GameManager *manager) : scene(scene), manager(manager) {
  setAcceptDrops(true);
  pixmap = QPixmap(81, 81);
  pixmap.fill(QColor(0, 0, 0, 0));
  movie = nullptr;
  state = 0;
}

QRectF PlantSlot::boundingRect() const {
  return QRectF(pixmap.rect());
}

void PlantSlot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  painter->setRenderHint(QPainter::Antialiasing);
  painter->drawPixmap(QRect(0, 0, 81, 81), pixmap);
}

void PlantSlot::dropEvent(QGraphicsSceneDragDropEvent *event) {
  if (state != 0) {
    return;
  } else {
    state++;
  }
  PlantConfig::PlantData plant = PlantConfig::allPlants().value(event->mimeData()->text());
  auto type_map = PlantConfig::typeMap();
  PlantConfig::PlantType type = type_map.value(plant.name);
  Plant *p = PlantConfig::createPlant(type, this, plant);
  //   QMovie * backgroundGifMovie = new QMovie(this);

  // movie = new QMovie(plant.default_state);
  // connect(movie, &QMovie::frameChanged, [this] {
  //   pixmap = movie->currentPixmap().scaled(pixmap.size());
  //   update();
  // });
  // movie->start();
  // QPixmap img(QPixmap(plant.img).scaled(pixmap.size()));
  // pixmap.swap(img);
  // update();
}