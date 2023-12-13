/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-08 13:22:09
 * @LastEditTime: 2023-12-12 14:03:17
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
  QString attack_state;
  int blod;     // 血量
  int hurt;     // 伤害
  int sun;      // 需要阳光
  int cd;       // 冷却
  int interval; // 攻击频率
  bool isMelee; // 是否是近战
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
  NAORMAL = 0,
  BUCKET = 1,
  CONE = 2
};

/* 全局默认配置 */
typedef struct {
  int default_sun;
  int first_zombie;
  int zombie_num;
  int threshold;
  int min_interval;
  int max_interval;
} DefaultConfig;

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

  inline const DefaultConfig &defaultConfig() const {
    return default_config;
  }

private:
  QMap<QString, PlantData> plants_data;
  QMap<QString, PlantType> plants_type_map;
  QMap<QString, ZombieData> zombies_data;
  QMap<QString, ZombieType> zombies_type_map;
  DefaultConfig default_config;

  /* 加载配置文件 */
  void loadPlantConfig();
  void loadZombieConfig();
  void loadTypeConfig();
  void loadDefaultConfig();
};

#endif