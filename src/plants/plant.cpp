#include "include/plants/plant.h"
#include "hpp/tools.hpp"
#include "include/manager/game_manager.h"
#include <qlist.h>
#include <set>

Plant::Plant(PlantSlot *slot, PlantConfig::PlantData data) :
  slot(slot), plantData(data), manager(slot->gameManager()), ij(slot->ij) {
  manager->addPlant(this, slot->ij.x());
}