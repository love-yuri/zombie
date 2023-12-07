/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-05 18:44:37
 * @LastEditTime: 2023-12-07 22:30:04
 * @Description: 全局配置类
 */
#include "include/manager/zombie_config.h"
#include "hpp/tools.hpp"
#include "include/plants/pea.h"
#include "include/plants/plant_slot.h"
#include "include/zombie/nomal_zombie.h"
#include "include/zombie/zombie.h"
#include <QJsonArray>
#include <qmap.h>

/* 初始化静态变量 */
QMap<QString, ZombieConfig::ZombieData> ZombieConfig::zombies = QMap<QString, ZombieConfig::ZombieData>();
QMap<QString, ZombieConfig::ZombieType> ZombieConfig::type_map = QMap<QString, ZombieConfig::ZombieType>(
  {
    { "normal", NAORMAL },
    { "bucket", BUCKET },
    { "cone", CONE }

  });

void ZombieConfig::loadConfig() {
  QFile file(":/config/zombie.json"); // 打开文件
  if (!file.open(QFile::ReadOnly | QIODevice::Text)) {
    qinfo << "文件打开失败! -> "
          << ":/config/zombie.json";
  } else {
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    // this->json = new QVariantMap(doc.array().toVariantList());

    /* 读取配置文件 */
    for (auto j : doc.array()) {
      ZombieConfig::ZombieData zombie {
        .name = j.toObject()["name"].toString(),
        .default_state = j.toObject()["default_state"].toString(),
        .attack_state = j.toObject()["attack_state"].toString(),
        .blod = j.toObject()["blod"].toInt(),
        .hurt = j.toObject()["hurt"].toInt(),
        .speed = j.toObject()["speed"].toInt(),
        .interval = j.toObject()["interval"].toInt(),
      };
      zombies.insert(zombie.name, zombie);
    }
  }
}

const QMap<QString, ZombieConfig::ZombieData> &ZombieConfig::allZombies() {
  if (zombies.empty()) {
    loadConfig();
  }
  return zombies;
}

QSharedPointer<Zombie> ZombieConfig::createZombie(ZombieConfig::ZombieType type, GameManager *manager, int pos_i) {
  ZombieData zombieData = allZombies().value(type_map.key(type));
  switch (type) {
    case ZombieConfig::ZombieType::NAORMAL : return QSharedPointer<Zombie>(new NormalZombie(manager, pos_i, zombieData));
  default:
    return nullptr;
  }
}
