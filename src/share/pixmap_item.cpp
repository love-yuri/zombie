#include "include/share/pixmap_item.h"
#include <qpixmap.h>
#include <qsize.h>
#include <QPainter>
#include <qtmetamacros.h>

PixmapItem::PixmapItem(QString file_name, QString file_click_name) :
  file(file_name), file_click(file_click_name) {
  isClicking = false;
  size_ = file.size();
}

void PixmapItem::resize(QSize size) {
  this->size_ = size;
  QPixmap new_file(file.scaled(size));
  QPixmap new_file_click(file_click.scaled(size));
  file.swap(new_file);
  file_click.swap(new_file_click);
}

const QSize PixmapItem::size() const {
  return size_;
}

QRectF PixmapItem::boundingRect() const {
  return QRectF(file.rect());
}

void PixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  if (isClicking) {
    painter->drawPixmap(0, 0, file_click);
  } else {
    painter->drawPixmap(0, 0, file);
  }
}

void PixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *) {
  isClicking = true;
  update();
}

void PixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *) {
  isClicking = false;
  update();
  emit clicked();
}
