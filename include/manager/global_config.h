/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-08 13:22:09
 * @LastEditTime: 2023-12-08 14:13:09
 * @Description:  全局配置类
 */

#ifndef GLOBAL_CONFIG_H
#define GLOBAL_CONFIG_H

#include <QString>
#include <QMap>
#include <qobject.h>

class Plant;
class Zombie;

using plant_ptr = QSharedPointer<Plant>;
using zombie_ptr = QSharedPointer<Zombie>;

/* 植物配置 */
typedef struct {
  QString name;
  QString img;
  QString img_g;
  QString img_drop;
  QString default_state;
  int blod;     // 血量
  int hurt;     // 伤害
  int sum;      // 需要阳光
  int cd;       // 冷却
  int interval; // 攻击频率
} PlantData;

enum PlantType {
  CHERRY,
  CSQUASH,
  DAZUI,
  PEA,
  POTATOMINE,
  REPEATERPEA,
  SKIKEWEED,
  SUNFLOWER,
  TALLNUT,
  WALLNUT
};

/* 僵尸配置 */
typedef struct {
  QString name;
  QString default_state;
  QString attack_state;
  int blod;     // 血量
  int hurt;     // 伤害
  int speed;    // 移速
  int interval; // 攻击频率
} ZombieData;

enum ZombieType {
  NAORMAL,
  BUCKET,
  CONE
};

class GlobalConfig : public QObject {
  Q_OBJECT
public:
  GlobalConfig(QObject *parent);
  virtual ~GlobalConfig() = default;

  inline const QMap<QString, PlantData> &plantsData() const {
    return plants_data;
  }
  inline const QMap<QString, PlantType> &plantsTypeMap() const {
    return plants_type_map;
  }
  inline const QMap<QString, ZombieData> &zombiesData() const {
    return zombies_data;
  }
  inline const QMap<QString, ZombieType> &zombiesTypeMap() const {
    return zombies_type_map;
  }

private:
  QMap<QString, PlantData> plants_data;
  QMap<QString, PlantType> plants_type_map;
  QMap<QString, ZombieData> zombies_data;
  QMap<QString, ZombieType> zombies_type_map;

  /* 加载配置文件 */
  void loadPlantConfig();
  void loadZombieConfig();
  void loadTypeConfig();
};

#endif