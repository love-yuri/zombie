/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-05 18:42:32
 * @LastEditTime: 2023-12-06 18:14:45
 * @Description: 植物配置文件读物
 */

#ifndef PLANT_CONFIG_H
#define PLANT_CONFIG_H

#include "include/plants/plant_slot.h"
#include <QFile>
#include <QJsonDocument>
#include <QMap> // 可以存储任何数据的map 容器
#include <QJsonObject>
#include <qgraphicsscene.h>
#include <qmap.h>

class Plant;
class PlantConfig {
public:
  // mysql 结构体
  typedef struct {
    QString name;
    QString img;
    QString img_g;
    QString img_drop;
    QString default_state;
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

public:
  const static QMap<QString, PlantData> &allPlants();
  const static QMap<QString, PlantType> &typeMap() {
    return type_map;
  }

  static Plant *createPlant(PlantType, PlantSlot*, PlantConfig::PlantData);

private:
  static void loadConfig();
  static QMap<QString, PlantData> plants;
  static QMap<QString, PlantType> type_map;
};

#endif // YURI_SETTING_H