/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-05 17:37:15
 * @LastEditTime: 2023-12-16 22:05:00
 * @Description: 植物卡片
 */

#include "include/plants/plant_slot.h"
#include "include/plants/plant.h"
#include "include/manager/game_manager.h"
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QDrag>
#include <qdrag.h>
#include <QMimeData>
#include <qmovie.h>
#include <qpixmap.h>
#include "hpp/tools.hpp"
#include "include/manager/global_config.h"
#include "include/plants/plant_card.h"
#include <QPainter>
#include <qcolor.h>
#include <qevent.h>
#include <qmimedata.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qsize.h>
PlantSlot::PlantSlot(QGraphicsScene *scene, GameManager *manager) :
  scene(scene), manager(manager) {
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
    qinfo << "不是0, 返回";
    return;
  } else {
    state++;
  }
  QString name = event->mimeData()->text();
  plant_ptr p = manager->createPlant(event->mimeData()->text(), this);
  for (PlantCard *card : manager->plantCards()) {
    if (card->plantData().name == name) {
      card->startToCd();
      break;
    }
  }
  connect(p.data(), &Plant::deathed, [this]() {
    pixmap = QPixmap(81, 81);
    pixmap.fill(QColor(0, 0, 0, 0));
    movie = nullptr;
    update();
    state = 0;
  });
}