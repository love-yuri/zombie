#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "include/game.h"
#include <QWidget>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class GameWindow;
}

QT_END_NAMESPACE

class GameWindow : public QWidget {
public:
  GameWindow(QWidget *parent = nullptr);
  virtual ~GameWindow();

private:
  QGraphicsScene *scene;
  QGraphicsView *view;

  Ui::GameWindow *ui;

  void init();
};

#endif