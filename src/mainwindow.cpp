/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-09-27 13:27:55
 * @LastEditTime: 2023-12-23 21:28:47
 * @Description:
 */

#include "include/mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include <qimage.h>
#include <qlabel.h>
#include <QMessageBox>
#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qsize.h>
#include <qwindowdefs.h>
#include <qpainter.h>
#include "hpp/tools.hpp"
#include <QDialog>
#include "include/game.h"
#include "include/menu/info_dialog.h"
#include "include/menu/last_dialog.h"
#include "include/menu/setting_dialog.h"

MainWindow::MainWindow(QMainWindow *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  setting_dialog(new SettingDialog(this)),
  info_dialog(new InfoDialog(this)) {
  ui->setupUi(this);
  setFixedSize(QSize(800, 600));

  /* 初始化 */
  menuInit();

  show();
}

void MainWindow::paintEvent(QPaintEvent *ev) {
  QMainWindow::paintEvent(ev);
}

MainWindow::~MainWindow() {
  delete ui;
}

/* init */

/* 菜单初始化 */
void MainWindow::menuInit() {
  isShow = false;
  connect(ui->setting, &MenuLabel::clicked, this, [this]() {
    if (!isShow) {
      isShow = true;
      setting_dialog->exec();
      isShow = false;
    }
  });
  connect(ui->we, &MenuLabel::clicked, this, [this]() {
    if (!isShow) {
      isShow = true;
      info_dialog->exec();
      isShow = false;
    }
  });

  connect(ui->adventure, &MenuLabel::clicked, this, [this]() {
    if (!isShow) {
      isShow = true;
      Game *game = new Game();
      game->show();
      this->hide();
      connect(game, &Game::victory, this, [this, game] {
        LastDialog *dialog = new LastDialog(this, ":/victory.png");
        game->close();
        hide();
        connect(dialog, &LastDialog::clicked, [this, game] {
          show();
        });
      });
      connect(game, &Game::gameOver, this, [this, game] {
        LastDialog *dialog = new LastDialog(this, ":/gameOver.png");
        game->close();
        hide();
        connect(dialog, &LastDialog::clicked, [this] {
          show();
        });
      });
      connect(game, &Game::closed, this, [this, game]() {
        game->disconnect();
        show();
        delete game;
      });
      isShow = false;
    }
  });
}