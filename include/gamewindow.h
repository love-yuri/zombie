#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "include/game.h"
#include <QWidget>

class GameWindow : public QWidget {
public:
  GameWindow(QWidget *parent = nullptr);
  virtual ~GameWindow();
};

#endif