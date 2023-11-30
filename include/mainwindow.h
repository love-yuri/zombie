#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qmainwindow.h>
#include <qtconfigmacros.h>

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

private:
  Ui::MainWindow *ui;
};


#endif 