/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-02 18:45:35
 * @LastEditTime: 2023-12-16 22:24:18
 * @Description: 最终结算弹出框
 */
#ifndef LAST_DIALOG_H
#define LAST_DIALOG_H

#include <QDialog>
#include <qlabel.h>
#include <qtmetamacros.h>
#include <qwidget.h>

class Label : public QLabel {
  Q_OBJECT
public:
  Label(QWidget *parent) :
    QLabel(parent) {
  }
signals:
  void clicked();

protected:
  void mousePressEvent(QMouseEvent *event) override {
    emit clicked();
  }
};

class LastDialog : public QDialog {
  Q_OBJECT

public:
  LastDialog(QWidget *parent, QString fileName);
  
signals:
  void clicked();
};

#endif