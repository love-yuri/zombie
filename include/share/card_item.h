/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-04 17:40:16
 * @LastEditTime: 2023-12-05 20:29:14
 * @Description: pixmap
 */
#ifndef CARD_ITEM_H
#define CARD_ITEM_H

#include <QGraphicsItem>
#include <qpixmap.h>
#include <qtmetamacros.h>

class CardManager;

class CardItem : public QGraphicsItem {
public:
  CardItem(CardManager *manager, int id);
  CardItem(CardManager *manager, QString file_name, int id);
  virtual ~CardItem();

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
  void clear();
  const QString &fileName() const;
  const QString &name() const {
    return name_y;
  }
  void setName(const QString &name) {
    name_y = name;
  }

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
  void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
  void dropEvent(QGraphicsSceneDragDropEvent *event) override;

private:
  QPixmap *pixmap;
  QString file_name;
  QString name_y;

  /* 管理器 */
  CardManager *manager;
  int id;
};

#endif // COLORITEM_H