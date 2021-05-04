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
   * Creates the world with the provided parameters.
   *
   * @param sim_speed           the speed of the simulation (ant's speed)
   * @param num_colonies        the number of colonies
   * @param num_food_sources    the number of food sources
   */
  World(const size_t sim_speed,
        const size_t num_colonies, const size_t num_food_sources);

  void Render() const;
  void AdvanceOneFrame();

 private:
  const size_t kMaxFrames = 100;

  // Full screen
  const size_t kWindowWidth = 1920;
  const size_t kWindowHeight = 1080;
  const size_t kMargin = 50;

  // Colony & food source properties
  const size_t kMinPopulation = 50;
  const float kColonyRadius = 50;
  const float kMaxQuantity = 200;

  size_t frame_count_;
  size_t sim_speed_;

  std::vector<std::vector<MarkablePoint>> grid_;

  // Markers leading to the food source
  std::vector<MarkablePoint*> food_markers_;

  std::vector<Colony> colonies_;
  std::vector<FoodSource> food_sources_;

  void GenerateGrid();
  void GenerateColonies(const size_t num_colonies);
  void GenerateFoodSources(const size_t num_food_sources);

  void HandleBoundCollisions(Ant& ant);

  /**
   * Checks if the ant is at a certain location.
   *
   * @param ant_position    the position of the ant
   * @param location        the location to check
   * @param distance        the distance between the ant and the location
   * @return true or false
   */
  bool IsAtLocation(const glm::vec2& ant_position,
                    const glm::vec2& location, const float distance);
};

}  // namespace antsim