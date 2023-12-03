/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-03 16:29:29
 * @LastEditTime: 2023-12-03 22:06:01
 * @Description: 游戏界面
 */
#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QGraphicsView>

class Game : public QMainWindow {
  Q_OBJECT

public:
  explicit Game(QMainWindow *parent = nullptr);
  virtual ~Game();

private:
  QGraphicsScene *scene;
  QGraphicsView *view;
  QScrollBar *scroll;

  /* init function */
  void init();
  void windowInit();
};

#endif