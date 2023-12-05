/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-03 16:31:01
 * @LastEditTime: 2023-12-05 21:36:33
 * @Description: 游戏开始
 */
#include "include/game.h"
#include "hpp/tools.hpp"
#include "include/gamewindow.h"
#include "include/share/menu_label.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <qboxlayout.h>
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <QGraphicsPixmapItem>
#include <qnamespace.h>
#include <qpixmap.h>
#include <QVBoxLayout>
#include <qtimer.h>
#include <qwidget.h>
#include <QScrollBar>
#include <QGraphicsProxyWidget>

Game::Game(QMainWindow *parent) :
  QMainWindow(parent), scene(new QGraphicsScene(this)), view(new QGraphicsView(scene)) {
  setFixedSize(900, 620);
  /* init */
  init();
  windowInit();
}

Game::~Game() {
}

void Game::init() {
  /* 加载背景图 */
  QGraphicsPixmapItem *longImageItem = new QGraphicsPixmapItem(QPixmap(":/map.png"));
  longImageItem->setZValue(0);
  scene->addItem(longImageItem);
  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(view);
  QWidget *widget = new QWidget(this);
  widget->setLayout(layout);
  layout->setContentsMargins(0, 0, 0, 0);
  setCentralWidget(widget);
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  QTimer *timer = new QTimer(this);
  timer->setInterval(10);
  scroll = view->horizontalScrollBar();
  timer->setSingleShot(true);
  timer->start();
  connect(timer, &QTimer::timeout, [this, timer]() {
    view->horizontalScrollBar()->setValue(scroll->maximum());
    timer->stop();
  });
}

/* 初始化游戏界面窗口 */
void Game::windowInit() {
  QGraphicsProxyWidget *proxyWidget = new QGraphicsProxyWidget;
  GameWindow *game = new GameWindow();
  proxyWidget->setWidget(game);
  proxyWidget->setZValue(1);
  proxyWidget->setPos(500, 0);
  scene->addItem(proxyWidget);
  view->setRenderHint(QPainter::Antialiasing);

  connect(game, &GameWindow::gameStart, [this,game, proxyWidget]() {
    QTimer *timer = new QTimer(this);
    timer->setInterval(1);
    timer->start();
    connect(timer, &QTimer::timeout, [this, game, timer, proxyWidget]() {
      scroll->setValue(scroll->value() - 1);
      proxyWidget->setPos(proxyWidget->pos().x() - 1, proxyWidget->pos().y());
      if (scroll->value() == 150) {
        game->start();
        timer->stop();
      }
    });
  });
}