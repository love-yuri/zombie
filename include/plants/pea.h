#ifndef PEA_H
#define PEA_H

#include "include/plants/plant_slot.h"
#include "plant.h"
#include <qgraphicsscene.h>
#include <qmovie.h>
#include <qpoint.h>

class Pea : public Plant {
public:
  Pea(PlantSlot *slot, PlantConfig::PlantData plantData);
  virtual ~Pea();

private:
  QMovie *movie;
};

#endif