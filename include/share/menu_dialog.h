/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-02 11:49:50
 * @LastEditTime: 2023-12-02 16:25:40
 * @Description: 弹出窗口
 */

#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QDialog>
#include <qtmetamacros.h>

class MenuDialog : public QDialog {
  Q_OBJECT

  
  
public:
  MenuDialog(QWidget *parent = nullptr);
  virtual ~MenuDialog();

signals:
  void clicked();
  
protected:
  bool eventFilter(QObject *obj, QEvent *event) override;
  void mousePressEvent(QMouseEvent *ev) override;
  void mouseReleaseEvent(QMouseEvent *ev) override;
  
};

#endif