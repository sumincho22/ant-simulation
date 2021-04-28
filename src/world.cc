#include "world.h"

namespace antsim {

World::World() {
  GenerateGrid();
  GenerateColonies(1);
  GenerateFoodSources(1);
}

void World::Render() const {
  for (const Colony& colony : colonies_) {
    colony.Render();
  }

  for (const FoodSource& food_source : food_sources_) {
    food_source.Render();
  }
}

void World::AdvanceOneFrame() {
  for (Colony& colony : colonies_) {
    for (Ant& ant : colony.GetAnts()) {
      for (FoodSource& food_source : food_sources_) {
        if (ant.GetState() != kGoingHome &&
            IsAtLocation(ant.GetPosition(), food_source.GetPosition(),
                         food_source.GetRadius())) {
          ant.SetState(kGoingHome);
          ant.IncrementMarkers();

          food_source.DecreaseQuantity();
          food_source.UpdateSize();
        }
      }

      // Ant brought the food back to the colony
      if (ant.GetState() == kGoingHome &&
          IsAtLocation(ant.GetPosition(), colony.GetPosition(),
                       colony.GetRadius())) {
        ant.ClearMarkers();
        ant.SetState(kGettingFood);
      }

      if (ant.GetState() != kGoingHome &&
          (frame_count_ == 0 || frame_count_ % 20 == 0)) {
        size_t pos_x =
            static_cast<size_t>(floor(ant.GetPosition().x)) / kAntSpeed;
        size_t pos_y =
            static_cast<size_t>(floor(ant.GetPosition().y)) / kAntSpeed;
        ant.AddMarker(&grid_[pos_x][pos_y]);
      }
    }
    colony.AdvanceOneFrame();
  }

  // Maintaining minimal value to prevent overflow.
  if (frame_count_ == kMaxFrames) {
    frame_count_ = 0;
  }
  frame_count_++;
}

void World::GenerateGrid() {
  size_t grid_width = kWindowWidth / kAntSpeed;
  size_t grid_height = kWindowHeight / kAntSpeed;

  grid_.resize(grid_width + 1);
  for (size_t pos_x = 0; pos_x <= grid_width; ++pos_x) {
    grid_[pos_x].resize(grid_height + 1);
    for (size_t pos_y = 0; pos_y <= grid_height; ++pos_y) {
      grid_[pos_x][pos_y].position = glm::vec2(pos_x, pos_y);
    }
  }
}

void World::GenerateColonies(const size_t num_colonies) {
  for (size_t i = 0; i < num_colonies; ++i) {
    size_t population = rand() % kMaxPopulation + 1;

    float radius_offset = 2.0f * kColonyRadius;
    float pos_x =
        SimLogic::GetRandomValue(radius_offset, kWindowWidth - radius_offset);
    float pos_y =
        SimLogic::GetRandomValue(radius_offset, kWindowHeight - radius_offset);

    colonies_.push_back(
        Colony(population, glm::vec2(pos_x, pos_y), kColonyRadius));
  }
}

void World::GenerateFoodSources(const size_t num_food_sources) {
  for (size_t i = 0; i < num_food_sources; ++i) {
    size_t quantity = rand() % kMinQuantity + kMinQuantity;

    float radius_offset = 2.0f * static_cast<float>(quantity);
    float pos_x =
        SimLogic::GetRandomValue(radius_offset, kWindowWidth - radius_offset);
    float pos_y =
        SimLogic::GetRandomValue(radius_offset, kWindowHeight - radius_offset);

    food_sources_.push_back(FoodSource(glm::vec2(pos_x, pos_y), quantity));
  }
}

bool World::IsAtLocation(const glm::vec2& ant_position,
                         const glm::vec2& location, const float radius) {
  return glm::length(ant_position - location) <= radius;
}

}  // namespace antsim