/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-05 18:42:32
 * @LastEditTime: 2023-12-05 21:16:14
 * @Description: 植物配置文件读物
 */

#ifndef PLANT_CONFIG_H
#define PLANT_CONFIG_H

#include <QFile>
#include <QJsonDocument>
#include <QMap> // 可以存储任何数据的map 容器
#include <QJsonObject>
#include <qmap.h>

class PlantConfig {
public:
  // mysql 结构体
  typedef struct {
    QString name;
    QString img;
    QString img_g;
    QString img_drop;
  } Plant;

public:

  const static QMap<QString, Plant> &allPlants();

private:
  static void loadConfig();
  static QMap<QString, Plant> plants;
};

#endif // YURI_SETTING_H