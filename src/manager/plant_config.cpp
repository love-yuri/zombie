#include "include/manager/plant_config.h"
#include "hpp/tools.hpp"
#include <QJsonArray>
#include <qmap.h>

/* 初始化静态变量 */
QMap<QString, PlantConfig::Plant> PlantConfig::plants = QMap<QString, PlantConfig::Plant>();
void PlantConfig::loadConfig() {
  QFile file(":/config/plant.json"); // 打开文件
  if (!file.open(QFile::ReadOnly | QIODevice::Text)) {
    qinfo << "文件打开失败! -> "
          << ":/config/plant.json";
  } else {
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    // this->json = new QVariantMap(doc.array().toVariantList());
    for (auto j : doc.array()) {
      Plant plant{
        .name = j.toObject()["name"].toString(),
        .img = j.toObject()["img"].toString(),
        .img_g = j.toObject()["img_g"].toString(),
        .img_drop = j.toObject()["img_drop"].toString(),
      };
      plants.insert(plant.name, plant);
    }
  }
}

const QMap<QString, PlantConfig::Plant> &PlantConfig::allPlants() {
  if (plants.empty()) {
    loadConfig();
  }
  return plants;
}