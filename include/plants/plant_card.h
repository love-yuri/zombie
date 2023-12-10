/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-04 17:40:16
 * @LastEditTime: 2023-12-10 22:17:57
 * @Description: 植物卡片
 */
#ifndef PLANT_CARD_H
#define PLANT_CARD_H

#include "include/manager/global_config.h"
#include "include/plants/plant_slot.h"
#include <QGraphicsItem>
#include <qgraphicsitem.h>
#include <qpixmap.h>
#include <qtmetamacros.h>

class CardManager;

class PlantCard : public QGraphicsObject {
public:
  PlantCard(const PlantData &data, GameManager *manager);
  virtual ~PlantCard() = default;

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
  }
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
  }
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override {
  }
  void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override {
  }
  void dropEvent(QGraphicsSceneDragDropEvent *event) override {
  }

private:
  QPixmap pixmap;
  PlantData plant_data;
  GameManager *manager;
  QTimer *cd_timer;
  int timeout;
};

#endif // COLORITEM_H