/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-05 10:47:32
 * @LastEditTime: 2023-12-06 20:07:36
 * @Description:
 */
#include "include/manager/card_manager.h"
#include "hpp/tools.hpp"
#include "include/manager/plant_config.h"
#include "include/share/card_item.h"
#include <QGraphicsScene>

CardManager::CardManager(QObject *parent, QGraphicsScene *scene) :
  QObject(parent), scene(scene) {
  // PlantCard *card = new PlantCard(":/cards/cherry.png", 0);
}

void CardManager::build() {
  int i(0), j(0);
  for (PlantConfig::PlantData plant : PlantConfig::allPlants()) {
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
    CardItem *pix = new CardItem(this, i + PlantConfig::allPlants().size());
    pix->setPos(567 + i * (620 - 567), 28);
    scene->addItem(pix);
    plant_vec.push_back(pix);
  }
}

const QVector<CardItem *> &CardManager::plantVec() const {
  return plant_vec;
}