/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-05 17:37:15
 * @LastEditTime: 2023-12-11 17:43:18
 * @Description: 植物卡片
 */

#include "include/plants/plant_card.h"
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QDrag>
#include <qdrag.h>
#include <QMimeData>
#include <qpen.h>
#include <qpixmap.h>
#include "hpp/tools.hpp"
#include "include/manager/global_config.h"
#include "include/plants/plant_slot.h"
#include "include/manager/game_manager.h"
#include <QPainter>
#include <qcolor.h>
#include <qevent.h>
#include <qmimedata.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qpoint.h>
#include <qsize.h>
#include <qtimer.h>
PlantCard::PlantCard(const PlantData &data, GameManager *manager) :
  plant_data(data), manager(manager),
  pixmap(QPixmap(data.img).scaled(45, 65)) {
  setAcceptedMouseButtons(Qt::LeftButton);
  setAcceptDrops(true);
  timeout = 0;
  cd_timer = new QTimer(this);
  connect(cd_timer, &QTimer::timeout, [this]() {
    timeout--;
    update();
    if (timeout == 0) {
      cd_timer->stop();
    }
  });
}

QRectF PlantCard::boundingRect() const {
  return QRectF(pixmap.rect());
}

void PlantCard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  if (manager->sun() < plant_data.sun) {
    pixmap = QPixmap(plant_data.img_g).scaled(45, 65);
  } else {
    pixmap = QPixmap(plant_data.img).scaled(45, 65);
  }
  painter->setRenderHint(QPainter::Antialiasing);
  
  painter->drawPixmap(pixmap.rect(), pixmap);
  if (timeout != 0) {
    double bl = double(timeout) / (plant_data.cd / 200.0);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(0, 0, 0, 80));
    painter->drawRect(0, 65 * bl, 45, 65 * (1 - bl));
  }
}
void PlantCard::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length()
      < QApplication::startDragDistance()) {
    return;
  }
  if (manager->sun() < plant_data.sun || timeout != 0) {
    return;
  }
  QDrag *darg = new QDrag(event->widget());
  QMimeData *mimeData = new QMimeData;
  mimeData->setText(plant_data.name);
  darg->setPixmap(QPixmap(plant_data.img_drop));
  darg->setMimeData(mimeData);
  darg->setHotSpot(QPoint(30, 30));
  darg->exec();
  timeout = plant_data.cd / 200;
  cd_timer->start(200);
  qinfo << "结束" << pixmap.size();
}