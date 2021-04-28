#pragma once

#include <cinder/app/AppBase.h>

#include "markable_point.h"
#include "colony.h"
#include "food_source.h"

namespace antsim {

class World {
 public:
  World();
  void Render() const;
  void AdvanceOneFrame();

 private:
  const size_t kAntSpeed = 2;

  // Constants for colony properties
  const size_t kMaxPopulation = 100;
  const float kColonyRadius = 50;

  std::vector<std::vector<MarkablePoint>> grid_;
  std::vector<Colony> colonies_;
  std::vector<FoodSource> food_sources_;

  void GenerateGrid();
  void GenerateColonies(const size_t num_colonies);
  void GenerateFoodSources(const size_t num_food_sources);
};

}