/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-05 21:27:59
 * @LastEditTime: 2023-12-21 20:14:27
 * @Description: 植物的坑位
 */
#ifndef PLANT_SLOT_H
#define PLANT_SLOT_H

#include <QGraphicsItem>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qmovie.h>
#include <qpixmap.h>
#include <qtmetamacros.h>

class GameManager;
class PlantSlot : public QGraphicsObject {
  Q_OBJECT
public:
  PlantSlot(QGraphicsScene *scene, GameManager *manager);
  virtual ~PlantSlot() {
    emit destory();
  }

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
  void reset();

  /* 坐标标识 */
  QPoint ij;

  /* 内联 */
  inline QGraphicsScene *mutableScene() {
    return scene;
  }

  inline QPixmap *mutablePixmap() {
    return &pixmap;
  }

  inline GameManager *gameManager() {
    return manager;
  }

signals:
  void destory();

protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override {
  }
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
  }
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override {
  }
  void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override {
  }
  void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override {
  }
  void dropEvent(QGraphicsSceneDragDropEvent *event) override;

private:
  QPixmap pixmap;
  QMovie *movie;

  QGraphicsScene *scene;
  GameManager *manager;
  int state;
};

#endif // COLORITEM_H