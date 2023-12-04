/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-03 22:56:48
 * @LastEditTime: 2023-12-04 22:21:37
 * @Description: 游戏界面
 */
#include "include/gamewindow.h"
#include "include/share/menu_label.h"
#include "include/share/card_item.h"
#include <qgraphicsitem.h>
#include <qgraphicsview.h>
#include <QGraphicsProxyWidget>
#include <qlist.h>
#include <qnamespace.h>
#include <qpixmap.h>

GameWindow::GameWindow(QWidget *parent) :
  QWidget(parent),
  scene(new QGraphicsScene()),
  view(new QGraphicsView(scene)) {
  setFixedSize(900, 600);
  setObjectName("gamewindow");
  setStyleSheet(" \
    #gamewindow{background-color: rgba(0, 0, 0, 0)} \
    #view{background-color: rgba(0, 0, 0, 0)} \
  ");

  view->setGeometry(0, 0, 900, 600);
  view->setBackgroundBrush(Qt::transparent);
  view->setParent(this);
  view->setObjectName("view");
  init();
}

GameWindow::~GameWindow() {
}

void GameWindow::init() {
  QGraphicsPixmapItem *card_solt = new QGraphicsPixmapItem(QPixmap(":/choose/card_solt.png"));
  QGraphicsPixmapItem *choose_card = new QGraphicsPixmapItem(QPixmap(":/choose/choose_card.png"));
  card_solt->setPos(490, 20);
  choose_card->setPos(10, 20);
  QPixmap img = QPixmap(":/choose/game_start.png");
  QGraphicsPixmapItem *start = new QGraphicsPixmapItem(img.scaled(400, 71));
  start->setPos(40, 440);
  start->setZValue(2);
  scene->addItem(start);
  scene->addItem(card_solt);
  scene->addItem(choose_card);

  for (int i = 0; i < 6; i++) {
    CardItem *pix = new CardItem();
    pix->setPos(567 + i * (620 - 567), 28);
    scene->addItem(pix);
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      CardItem *pix = new CardItem(":/cards/potatomine.png");
      pix->setPos(35 + i * (88 - 35), 63 + j * (135 - 63));
      scene->addItem(pix);
    }
  }
}