/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-11-30 22:31:31
 * @LastEditTime: 2023-12-02 20:41:48
 * @Description: 主界面
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qmainwindow.h>
#include <qtconfigmacros.h>
#include "include/menu/info_dialog.h"
#include "include/menu/setting_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : QMainWindow {
  Q_OBJECT
public:
  MainWindow(QMainWindow *parent = nullptr);
  ~MainWindow();

protected:
  void paintEvent(QPaintEvent *ev) override;

private:
  Ui::MainWindow *ui;
  SettingDialog *setting_dialog;
  InfoDialog *info_dialog;
  bool isShow;

/* 初始化函数 */
private:
  void menuInit();
};

#endif