/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-11-30 22:31:31
 * @LastEditTime: 2023-12-03 13:12:15
 * @Description: 启动函数
 */
#include <QApplication>
#include <QTranslator>
#include <hpp/tools.hpp>
#include "include/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "yuri_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }
  yuri::Tools::init();
  MainWindow window;
  return a.exec();
}
