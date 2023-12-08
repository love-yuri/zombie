/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-04 22:30:09
 * @LastEditTime: 2023-12-08 14:19:44
 * @Description: 卡片管理
 */
#ifndef CARD_MANAGER_H
#define CARD_MANAGER_H

#include <QMap>
#include <qlist.h>
#include <qmap.h>
#include "include/share/card_item.h"
#include "include/manager/global_config.h"

class CardManager : public QObject {
public:
  CardManager(QObject *parent, QGraphicsScene *scene, GlobalConfig *config);
  virtual ~CardManager() = default;

  /* func */
  void build();
  const QVector<CardItem *> &plantVec() const;

private:
  QGraphicsScene *scene;

  /* data */
  QVector<CardItem *> plant_vec;
  GlobalConfig *config;

  QList<QString> file_list;
};

#endif