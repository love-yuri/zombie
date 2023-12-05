/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-05 21:27:59
 * @LastEditTime: 2023-12-05 21:31:07
 * @Description: 植物的坑位
 */
#ifndef PLANT_SLOT_H
#define PLANT_SLOT_H

#include <QGraphicsItem>
#include <qgraphicsitem.h>
#include <qpixmap.h>
#include <qtmetamacros.h>

class PlantSlot : public QGraphicsObject {
public:
  PlantSlot();
  virtual ~PlantSlot() = default;

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {}
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override {}
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {}
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override {}
  void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override {}
  void dropEvent(QGraphicsSceneDragDropEvent *event) override;

private:
  QPixmap pixmap;
};

#endif // COLORITEM_H