/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-06 21:32:53
 * @LastEditTime: 2023-12-11 13:39:20
 * @Description: 植物基类
 */
#include "include/plants/plant.h"
#include "hpp/tools.hpp"
#include "include/manager/game_manager.h"
#include <qlist.h>
#include <qtimer.h>
#include <set>

Plant::Plant(PlantSlot *slot, const PlantData &data) :
  slot(slot), plantData(data), manager(slot->gameManager()), ij(slot->ij), blod(data.blod) {
  this->scene = slot->mutableScene();
  this->pixmap = slot->mutablePixmap();
  deathedCount = 0;
  /* 播放默认效果 */
  movie = new QMovie(data.default_state);
  // movie
  connect(movie, &QMovie::frameChanged, [this] {
    QPixmap pix(movie->currentPixmap().scaled(pixmap->size()));
    pixmap->swap(pix);
    this->slot->update();
  });
  movie->start();

  /* 绑定攻击 */
  attack_timer = new QTimer(this);
  if (data.interval > 0) {
    
    if (data.isMelee) {
      // connect(this, &Plant::near, [this] {
      //   attack_timer->start(plantData.interval);
      // });
    } else {
      connect(attack_timer, &QTimer::timeout, this, &Plant::attack);
      attack_timer->start(data.interval);
    }
  }

  /* 绑定销毁事件,防止出现slot先销毁后出问题的情况更 */
  connect(slot, &PlantSlot::destory, movie, &QMovie::stop);
}

Plant::~Plant() {
  movie->stop();
  attack_timer->stop();
  disconnect();
}