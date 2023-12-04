/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-02 11:49:50
 * @LastEditTime: 2023-12-04 17:30:57
 * @Description: 菜单label
 *
 */

#include "include/share/menu_label.h"
#include <QRegularExpression>
#include <qpixmap.h>
#include "hpp/tools.hpp"

MenuLabel::MenuLabel(QWidget *parent) :
  QLabel(parent) {
  isButton = false;
  m_isClicked = false;
}

MenuLabel::MenuLabel(QWidget *parent, QString bgImg) :
  QLabel(parent), bgImg(bgImg) {
  isButton = false;
  m_isClicked = false;
  resize(QPixmap(bgImg).size());
  setStyleSheet(QString("border-image: url(%1.png);").arg(bgImg));
  show();
}

MenuLabel::~MenuLabel() {
}

void MenuLabel::setIsButton(bool isButton) {
  this->isButton = isButton;
}

bool MenuLabel::isClicked() const {
  return m_isClicked;
}

void MenuLabel::mousePressEvent(QMouseEvent *ev) {
  if (bgImg.isEmpty()) {
    QString inputString = styleSheet();
    int startIndex = inputString.indexOf("url(") + QString("url(").length();
    int endIndex = inputString.indexOf(".png", startIndex);

    // 提取文件名
    if (startIndex != -1 && endIndex != -1) {
      bgImg = inputString.mid(startIndex, endIndex - startIndex);
    }
  }
  m_isClicked = !m_isClicked;
  if (isButton) {
    if (m_isClicked) {
      setStyleSheet(QString("border-image: url(%1(click).png);").arg(bgImg));
    } else {
      setStyleSheet(QString("border-image: url(%1.png);").arg(bgImg));
    }
    emit clicked();
  } else {
    setStyleSheet(QString("border-image: url(%1(click).png);").arg(bgImg));
  }
  QLabel::mousePressEvent(ev);
}

void MenuLabel::mouseReleaseEvent(QMouseEvent *ev) {
  if (!isButton) {
    setStyleSheet(QString("border-image: url(%1.png);").arg(bgImg));
    emit clicked();
  }
  QLabel::mouseReleaseEvent(ev);
}