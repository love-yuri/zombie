/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-03 22:56:48
 * @LastEditTime: 2023-12-14 19:11:15
 * @Description: 游戏界面
 */
#include "include/gamewindow.h"
#include "include/manager/card_manager.h"
#include "include/manager/game_manager.h"
#include "include/manager/global_config.h"
#include "include/plants/plant_card.h"
#include "include/plants/plant_slot.h"
#include "include/share/menu_label.h"
#include "include/share/card_item.h"
#include "hpp/tools.hpp"
#include "include/share/pixmap_item.h"
#include "include/zombie/zombie.h"
#include <qcontainerfwd.h>
#include <qgraphicsitem.h>
#include <qgraphicsview.h>
#include <QSharedPointer>
#include <QGraphicsProxyWidget>
#include <qlist.h>
#include <QScrollBar>
#include <qnamespace.h>
#include <qpixmap.h>
#include <QMovie>
#include <qpoint.h>
#include <qsize.h>
#include <qtimer.h>
#include <qtypes.h>
#include <qwindowdefs.h>

GameWindow::GameWindow(QWidget *parent) :
  QWidget(parent),
  scene(new QGraphicsScene(this)),
  view(new QGraphicsView(scene)),
  config(new GlobalConfig(this)),
  card_manager(new CardManager(this, scene, config)),
  game_manager(new GameManager(this, scene, config)) {
  setFixedSize(900, 600);
  setObjectName("gamewindow");
  setStyleSheet(" \
    #gamewindow{background-color: rgba(0, 0, 0, 0)} \
    #view{background-color: rgba(0, 0, 0, 0)} \
  ");

  view->setGeometry(0, 0, 900, 600);
  scene->setSceneRect(0, 0, 900, 600);
  view->setBackgroundBrush(Qt::transparent);
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 隐藏水平滚动条
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // 隐藏垂直滚动条
  view->setParent(this);
  view->setObjectName("view");

  init();
}

GameWindow::~GameWindow() {
  /* 提前断开和scens的关系, 防止智能指针重复析构 */
  for (QList<QSharedPointer<Zombie>> zombies : game_manager->zombieList()) {
    for (const QSharedPointer<Zombie> zombie : zombies) {
      scene->removeItem(zombie.data());
    }
  }
}

void GameWindow::init() {
  QGraphicsPixmapItem *card_solt = new QGraphicsPixmapItem(QPixmap(":/choose/card_solt.png"));
  QGraphicsPixmapItem *choose_card = new QGraphicsPixmapItem(QPixmap(":/choose/choose_card.png"));
  card_solt->setPos(490, 20);
  choose_card->setPos(10, 20);
  PixmapItem *start = new PixmapItem(":/choose/game_start(click).png", ":/choose/game_start.png");
  start->resize(QSize(400, 71));
  start->setPos(40, 440);
  start->setZValue(2);
  scene->addItem(start);
  scene->addItem(card_solt);
  scene->addItem(choose_card);
  card_manager->build();
  connect(start, &PixmapItem::clicked, [this, start, card_solt, choose_card]() {
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->start(200);
    emit gameStart();
    qsizetype size = config->plantsData().size();
    for (int i = 0; i < 6; i++) {
      if (!card_manager->plantVec()[i + size]->name().isEmpty()) {
        plants << card_manager->plantVec()[i + size]->name();
      }
    }
    connect(timer, &QTimer::timeout, [this, timer, start, card_solt, choose_card]() {
      for (CardItem *item : card_manager->plantVec()) {
        scene->removeItem(item);
        delete item;
      }
      scene->removeItem(start);
      scene->removeItem(choose_card);
      card_solt->setPos(0, 0);
      game_manager->start(plants);
      delete choose_card;
      delete start;
    });
  });
}