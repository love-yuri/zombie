/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-02 11:49:50
 * @LastEditTime: 2023-12-02 20:23:09
 * @Description: 弹出框
 *
 */

#include "include/share/menu_dialog.h"
#include "hpp/tools.hpp"
#include <QEvent>
#include <qdialog.h>

MenuDialog::MenuDialog(QWidget *parent) :
  QDialog(parent) {
  // setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
  setWindowFlags(this->windowFlags() | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
  hide();
  QPalette pl = palette();
  pl.setColor(QPalette::Window, QColor(0, 0, 0, 200)); //   设置背景颜色为黑色，如果不设置默认为白色
  setPalette(pl);
  setAutoFillBackground(true);
  setWindowOpacity(0.5); //   背景和元素都设置透明效果
}

MenuDialog::~MenuDialog() {
}

bool MenuDialog::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() == QEvent::Show && parentWidget()) {
    // 计算对话框居中的位置
    QPoint centerPos = parentWidget()->geometry().center() - rect().center();
    move(centerPos);
  }
  return QDialog::eventFilter(obj, event);
}

void MenuDialog::mousePressEvent(QMouseEvent *ev) {
  QDialog::mousePressEvent(ev);
}

void MenuDialog::mouseReleaseEvent(QMouseEvent *ev) {
  QDialog::mouseReleaseEvent(ev);
  emit clicked();
}