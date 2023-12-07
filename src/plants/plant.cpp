/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 21:32:53
 * @LastEditTime: 2023-12-07 21:38:04
 * @Description: 植物基类
 */
#include "include/plants/plant.h"
#include "hpp/tools.hpp"
#include "include/manager/game_manager.h"
#include <qlist.h>
#include <qtimer.h>
#include <set>

Plant::Plant(PlantSlot *slot, const PlantConfig::PlantData &data) :
  slot(slot), plantData(data), manager(slot->gameManager()), ij(slot->ij), blod(data.blod) {
  this->scene = slot->mutableScene();
  this->pixmap = slot->mutablePixmap();

  /* 播放默认效果 */
  movie = new QMovie(data.default_state);
  connect(movie, &QMovie::frameChanged, [this] {
    QPixmap pix(movie->currentPixmap().scaled(pixmap->size()));
    pixmap->swap(pix);
    this->slot->update();
  });
  movie->start();

  /* 绑定攻击 */
  if (data.interval > 0) {
    attack_timer = new QTimer(this);
    attack_timer->start(data.interval);
    connect(attack_timer, &QTimer::timeout, this, &Plant::attack);
  }
}

Plant::~Plant() {
  movie->stop();
  attack_timer->stop();
}