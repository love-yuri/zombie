/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-05 18:44:37
 * @LastEditTime: 2023-12-06 18:14:24
 * @Description: 全局配置类
 */
#include "include/manager/plant_config.h"
#include "hpp/tools.hpp"
#include "include/plants/pea.h"
#include "include/plants/plant_slot.h"
#include <QJsonArray>
#include <qmap.h>

/* 初始化静态变量 */
QMap<QString, PlantConfig::PlantData> PlantConfig::plants = QMap<QString, PlantConfig::PlantData>();
QMap<QString, PlantConfig::PlantType> PlantConfig::type_map = QMap<QString, PlantConfig::PlantType>(
  {{"cherry", CHERRY},
   {"csquash", CSQUASH},
   {"dazui", DAZUI},
   {"pea", PEA},
   {"potatomine", POTATOMINE},
   {"repeaterpea", REPEATERPEA},
   {"skikeweed", SKIKEWEED},
   {"sunflower", SUNFLOWER},
   {"tallnut", TALLNUT},
   {"wallnut", WALLNUT}});

void PlantConfig::loadConfig() {
  QFile file(":/config/plant.json"); // 打开文件
  if (!file.open(QFile::ReadOnly | QIODevice::Text)) {
    qinfo << "文件打开失败! -> "
          << ":/config/plant.json";
  } else {
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    // this->json = new QVariantMap(doc.array().toVariantList());
    for (auto j : doc.array()) {
      PlantData plant{
        .name = j.toObject()["name"].toString(),
        .img = j.toObject()["img"].toString(),
        .img_g = j.toObject()["img_g"].toString(),
        .img_drop = j.toObject()["img_drop"].toString(),
        .default_state = j.toObject()["default_state"].toString(),
      };
      plants.insert(plant.name, plant);
    }
  }
}

const QMap<QString, PlantConfig::PlantData> &PlantConfig::allPlants() {
  if (plants.empty()) {
    loadConfig();
  }
  return plants;
}

Plant *PlantConfig::createPlant(PlantConfig::PlantType type, PlantSlot *slot, PlantConfig::PlantData data) {
  switch (type) {
    case PlantConfig::PEA: return new Pea(slot, data);
  default:
    return nullptr;
  }
}