/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-11-30 22:31:31
 * @LastEditTime: 2023-12-23 21:31:32
 * @Description: 启动函数
 */
#include <QApplication>
#include <QTranslator>
#include <hpp/tools.hpp>
#include "include/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  yuri::Tools::init();
  MainWindow window;
  return a.exec();
}
