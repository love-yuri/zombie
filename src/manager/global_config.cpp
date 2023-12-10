/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-08 14:26:16
 * @LastEditTime: 2023-12-10 21:08:58
 * @Description: 全局配置文件
 */
#include "include/manager/global_config.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "hpp/tools.hpp"

GlobalConfig::GlobalConfig(QObject *parent) :
  QObject(parent) {
  loadPlantConfig();
  loadTypeConfig();
  loadZombieConfig();
  loadDefaultConfig();
}

void GlobalConfig::loadPlantConfig() {
  QFile file(":/config/plant.json"); // 打开文件
  if (!file.open(QFile::ReadOnly | QIODevice::Text)) {
    qinfo << "文件打开失败! -> "
          << ":/config/plant.json";
  } else {
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    // this->json = new QVariantMap(doc.array().toVariantList());

    /* 读取配置文件 */
    for (auto j : doc.array()) {
      PlantData plant{
        .name = j.toObject()["name"].toString(),
        .img = j.toObject()["img"].toString(),
        .img_g = j.toObject()["img_g"].toString(),
        .img_drop = j.toObject()["img_drop"].toString(),
        .default_state = j.toObject()["default_state"].toString(),
        .attack_state = j.toObject()["attack_state"].toString(),
        .blod = j.toObject()["blod"].toInt(),
        .hurt = j.toObject()["hurt"].toInt(),
        .sun = j.toObject()["sun"].toInt(),
        .cd = j.toObject()["cd"].toInt(),
        .interval = j.toObject()["interval"].toInt(),
        .isMelee = j.toObject()["isMelee"].toBool()};
      plants_data.insert(plant.name, plant);
    }
    file.close();
  }
}

void GlobalConfig::loadZombieConfig() {
  QFile file(":/config/zombie.json"); // 打开文件
  if (!file.open(QFile::ReadOnly | QIODevice::Text)) {
    qinfo << "文件打开失败! -> "
          << ":/config/zombie.json";
  } else {
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    // this->json = new QVariantMap(doc.array().toVariantList());

    /* 读取配置文件 */
    for (auto j : doc.array()) {
      ZombieData zombie{
        .name = j.toObject()["name"].toString(),
        .default_state = j.toObject()["default_state"].toString(),
        .attack_state = j.toObject()["attack_state"].toString(),
        .blod = j.toObject()["blod"].toInt(),
        .hurt = j.toObject()["hurt"].toInt(),
        .speed = j.toObject()["speed"].toInt(),
        .interval = j.toObject()["interval"].toInt(),
      };
      zombies_data.insert(zombie.name, zombie);
    }
    file.close();
  }
}

void GlobalConfig::loadTypeConfig() {
  zombies_type_map = QMap<QString, ZombieType>(
    {{"normal", NAORMAL},
     {"bucket", BUCKET},
     {"cone", CONE}});
  plants_type_map = QMap<QString, PlantType>(
    {{"cherry", CHERRY},
     {"csquash", CSQUASH},
     {"dazui", DAZUI},
     {"pea", PEA},
     {"potatomine", POTATOMINE},
     {"repeaterpea", REPEATERPEA},
     {"spikeweed", SKIKEWEED},
     {"sunflower", SUNFLOWER},
     {"tallnut", TALLNUT},
     {"wallnut", WALLNUT}});
}

void GlobalConfig::loadDefaultConfig() {
  QFile file(":/config/default.json"); // 打开文件
  if (!file.open(QFile::ReadOnly | QIODevice::Text)) {
    qinfo << "文件打开失败! -> "
          << ":/config/zombie.json";
  } else {
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    auto j = new QVariantMap(doc.toVariant().toMap());
    default_config.default_sun = j->value("default-sun").toInt();
    file.close();
  }
}