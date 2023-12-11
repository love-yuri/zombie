/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-05 10:47:32
 * @LastEditTime: 2023-12-11 17:27:54
 * @Description:
 */
#include "include/manager/card_manager.h"
#include "include/manager/global_config.h"
#include "hpp/tools.hpp"
#include "include/share/card_item.h"
#include <QGraphicsScene>

CardManager::CardManager(QObject *parent, QGraphicsScene *scene, GlobalConfig *config) :
  QObject(parent), scene(scene), config(config) {
  // PlantCard *card = new PlantCard(":/cards/cherry.png", 0);
}

void CardManager::build() {
  int i(0), j(0);
  for (PlantData plant : config->plantsData()) {
    if (i == 8) {
      i = 0;
      j++;
    }
    CardItem *pix = new CardItem(this, plant.img, j * 8 + i);
    pix->setName(plant.name);
    pix->setPos(35 + i * (88 - 35), 63 + j * (135 - 63));
    scene->addItem(pix);
    plant_vec.push_back(pix);
    i++;
  }
  for (int i = 0; i < 6; i++) {
    CardItem *pix = new CardItem(this, i + config->plantsData().size());
    pix->setPos(567 + i * (620 - 567), 28);
    scene->addItem(pix);
    plant_vec.push_back(pix);
  }
}

const QVector<CardItem *> &CardManager::plantVec() const {
  return plant_vec;
}

CardItem *CardManager::filstCard(int id) {
  if (id < config->plantsData().size()) {
    for (int i = config->plantsData().size(); i < plant_vec.size(); i++) {
      if (plant_vec[i]->fileName().isEmpty()) {
        return plant_vec[i];
      }
    }
  } else {
    for (int i = 0; i < config->plantsData().size(); i++) {
      if (plant_vec[i]->fileName().isEmpty()) {
        return plant_vec[i];
      }
    }
  }

  return nullptr;
}