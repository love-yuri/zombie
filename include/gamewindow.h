/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-03 22:54:33
 * @LastEditTime: 2023-12-10 22:58:33
 * @Description: 游戏主窗口
 */
#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "include/game.h"
#include "include/manager/card_manager.h"
#include "include/manager/game_manager.h"
#include "include/manager/global_config.h"
#include <QWidget>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <qtmetamacros.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class GameWindow;
}

QT_END_NAMESPACE

class GameWindow : public QWidget {
  Q_OBJECT
public:
  GameWindow(QWidget *parent = nullptr);
  virtual ~GameWindow();

signals:
  void gameStart();  

private:
  QGraphicsScene *scene;
  QGraphicsView *view;

  QList<QString> plants;

  /* ui */
  Ui::GameWindow *ui;

  /* manager */
  GlobalConfig *config;
  CardManager *card_manager;
  GameManager *game_manager;

  /* init func */
  void init();
};

#endif