/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 18:49:14
 * @LastEditTime: 2023-12-06 21:14:37
 * @Description: 僵尸基类
 */
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsObject>
#include <qmovie.h>

class Zombie : public QGraphicsObject {
public:
  Zombie();
  virtual ~Zombie();

  /* 坐标标识 */
  QPoint ij;

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
  QPixmap pixmap;
  QMovie *movie;
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
  void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
};

#endif