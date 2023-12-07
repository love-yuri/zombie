/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-07 13:29:35
 * @LastEditTime: 2023-12-07 22:29:46
 * @Description: 植物配置文件
 */
#ifndef ZOMBIE_CONFIG_H
#define ZOMBIE_CONFIG_H

#include "include/plants/plant_slot.h"
#include <QFile>
#include <QJsonDocument>
#include <QMap> // 可以存储任何数据的map 容器
#include <QJsonObject>
#include <qgraphicsscene.h>
#include <qmap.h>

class Zombie;
class ZombieConfig {
public:
  using zombie_ptr = QSharedPointer<Zombie>;
public:
  
  // mysql 结构体
  typedef struct {
    QString name;
    QString default_state;
    QString attack_state;
    int blod;     // 血量
    int hurt;     // 伤害
    int speed;      // 移速
    int interval; // 攻击频率
  } ZombieData;

  enum ZombieType {
    NAORMAL,
    BUCKET,
    CONE
  };

public:
  const static QMap<QString, ZombieData> &allZombies();
  inline const static QMap<QString, ZombieType> &typeMap() {
    return type_map;
  }

  static zombie_ptr createZombie(ZombieType, GameManager *, int);

private:
  static void loadConfig();
  static QMap<QString, ZombieData> zombies;
  static QMap<QString, ZombieType> type_map;
};

#endif // YURI_SETTING_H