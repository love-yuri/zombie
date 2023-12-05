/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-04 17:40:16
 * @LastEditTime: 2023-12-05 21:58:04
 * @Description: 植物卡片
 */
#ifndef PLANT_CARD_H
#define PLANT_CARD_H

#include <QGraphicsItem>
#include <qgraphicsitem.h>
#include <qpixmap.h>
#include <qtmetamacros.h>

class CardManager;

class PlantCard : public QGraphicsObject {
public:
  PlantCard(QString file_name, QString file_name_drop);
  virtual ~PlantCard() = default;

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  void setPlantName(QString name) { plant_name = name; }

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override {}
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {}
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override {}
  void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override {}
  void dropEvent(QGraphicsSceneDragDropEvent *event) override {}

private:
  QPixmap pixmap;
  QPixmap drop_pixmap;
  QString plant_name;
};

#endif // COLORITEM_H