/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-04 17:40:16
 * @LastEditTime: 2023-12-04 22:40:00
 * @Description: pixmap
 */
#ifndef CARD_ITEM_H
#define CARD_ITEM_H

#include <QGraphicsItem>
#include <qpixmap.h>
#include <qtmetamacros.h>

class CardItem : public QGraphicsItem {
public:
  CardItem();
  CardItem(QString fileName);
  virtual ~CardItem();

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
  void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
  void dropEvent(QGraphicsSceneDragDropEvent *event) override;

private:
  QPixmap *pixmap;
  QString fileName;
};

#endif // COLORITEM_H