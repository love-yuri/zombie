/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-05 15:42:25
 * @LastEditTime: 2023-12-05 16:17:47
 * @Description: 重写QGraphicsPixmatpItem
 */
#ifndef PIXMAP_ITEM_H
#define PIXMAP_ITEM_H

#include <QGraphicsItem>
#include <qgraphicsitem.h>
#include <qpixmap.h>
#include <qtmetamacros.h>

class PixmapItem : public QGraphicsObject {
  Q_OBJECT
public:
  PixmapItem(QString file_name, QString file_click_name);

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
  const QSize size() const;
  void resize(QSize size);

signals:
  void clicked();

private:
  QPixmap file;
  QPixmap file_click;

  QSize size_;
  bool isClicking;

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif