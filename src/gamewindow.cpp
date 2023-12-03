/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-03 22:56:48
 * @LastEditTime: 2023-12-03 23:02:53
 * @Description: 游戏界面
 */
#include "include/gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
  QWidget(parent) {
  setFixedSize(900, 600);
  setObjectName("gamewindow");
  setStyleSheet("#gamewindow {background-color: rgba(0, 0, 0, 0.3)}");
}

GameWindow::~GameWindow() {
}