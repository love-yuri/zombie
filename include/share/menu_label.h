/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-02 11:49:50
 * @LastEditTime: 2023-12-02 18:38:58
 * @Description: 重写点击按钮
 */

#ifndef MENU_HPP
#define MENU_HPP

#include <QLabel>
#include <qtmetamacros.h>

class MenuLabel : public QLabel {
  Q_OBJECT

public:
  MenuLabel(QWidget *parent = nullptr);
  virtual ~MenuLabel();

  void setIsButton(bool isButton);
  bool isClicked() const;

signals:
  void clicked();

protected:
  void mousePressEvent(QMouseEvent *ev) override;
  void mouseReleaseEvent(QMouseEvent *ev) override;

private:
  QString bgImg;
  bool isButton;
  bool m_isClicked;
};

#endif