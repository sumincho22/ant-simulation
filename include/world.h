#pragma once

#include <cinder/app/AppBase.h>

#include "cinder/Rand.h"
#include "colony.h"
#include "food_source.h"
#include "markable_point.h"

namespace antsim {

/**
 * This class creates the world of the ant simulation, which includes colonies,
 * food sources, and ants.
 */
class World {
 public:
  /**
   * Creates the world in which colonies, food sources, and ants co-exist.
   */
  World(); // TODO: Add parameters later on.

  void Render() const;
  void AdvanceOneFrame();

 private:
  // FIXME: setFullScreen() method should be called before.
  const size_t kWindowWidth = 1920;
  const size_t kWindowHeight = 1080;
  const size_t kOffset = 50;

  // FIXME: The ant speed should be universal between different classes.
  const size_t kAntSpeed = 2;
  const float kPathRange = 8.0f;
  const float kVisionRange = static_cast<float>(M_PI) / 4.0f;

  // Colony properties
  const size_t kMinPopulation = 50;
  const float kColonyRadius = 50;

  // Food source properties
  const float kMaxQuantity = 100;

  const size_t kMaxFrames = 100;

  size_t frame_count_;

  std::vector<std::vector<MarkablePoint>> grid_;
  std::vector<Colony> colonies_;
  std::vector<FoodSource> food_sources_;

  void GenerateGrid();
  void GenerateColonies(const size_t num_colonies);
  void GenerateFoodSources(const size_t num_food_sources);

  void HandleBoundCollisions(Ant& ant);

  // FIXME: Parameters are little awkward.
  bool IsAtLocation(const glm::vec2& ant_position, const glm::vec2& location,
                    const float distance);
};

}  // namespace antsim