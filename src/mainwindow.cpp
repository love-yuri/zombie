/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-09-27 13:27:55
 * @LastEditTime: 2023-10-07 21:09:58
 * @Description:
 */

#include "include/mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include <qmainwindow.h>

MainWindow::MainWindow(QMainWindow *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  show();
}

MainWindow::~MainWindow() {
  delete ui;
}