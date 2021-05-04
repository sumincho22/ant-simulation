#include "world.h"

namespace antsim {

World::World() {
  frame_count_ = 0;
  food_markers_ = std::vector<MarkablePoint*>();

  GenerateGrid();
  GenerateColonies(1);
  GenerateFoodSources(1);
}

void World::Render() const {
  for (const Colony& colony : colonies_) {
    colony.Render();
  }

  for (const FoodSource& food_source : food_sources_) {
    if (food_source.GetQuantity() > 0) {
      food_source.Render();
    }
  }
}

void World::AdvanceOneFrame() {
  for (Colony& colony : colonies_) {
    for (Ant& ant : colony.GetAnts()) {
      HandleBoundCollisions(ant);

      size_t pos_x =
          static_cast<size_t>(ceil(ant.GetPosition().x)) / kAntSpeed;
      size_t pos_y =
          static_cast<size_t>(ceil(ant.GetPosition().y)) / kAntSpeed;

      for (FoodSource& food_source : food_sources_) {
        // Ant found food source
        if (ant.GetState() != kGoingHome &&
            IsAtLocation(ant.GetPosition(), food_source.GetPosition(),
                         food_source.GetRadius())) {
          ant.AddMarker(&grid_[(size_t) food_source.GetPosition().x / 2]
                              [(size_t) food_source.GetPosition().y / 2]);
          ant.SetState(kGoingHome);
          ant.IncrementMarkers();

          if (food_markers_.empty()) {
            food_markers_ = ant.GetMarkers();
          }

          food_source.DecreaseQuantity();
          food_source.UpdateSize();
        }
      }

      // Ant brought the food back to the colony
      if (ant.GetState() == kGoingHome &&
          IsAtLocation(ant.GetPosition(), colony.GetPosition(),
                       colony.GetRadius())) {
        ant.SetState(kGettingFood);
        ant.GetDirection().TurnAround();
        ant.ClearMarkers();
        ant.AddMarker(&grid_[pos_x][pos_y]);
      }

      // Adding markers
      if (ant.GetState() != kGoingHome &&
          (frame_count_ == 0 || frame_count_ % 10 == 0)) {
        ant.AddMarker(&grid_[pos_x][pos_y]);
      }

      // Ant going back to get food
      if (ant.GetState() == kGettingFood) {
        ant.SetMarkers(food_markers_);
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
      grid_[pos_x][pos_y].position =
          glm::vec2(kAntSpeed * pos_x, kAntSpeed * pos_y);
    }
  }
}

void World::GenerateColonies(const size_t num_colonies) {
  for (size_t i = 0; i < num_colonies; ++i) {
    size_t population = rand() % kMinPopulation + kMinPopulation;

    float offset = kColonyRadius + kOffset;
    ci::Rand::randomize();
    float pos_x = ci::randFloat(offset, kWindowWidth - offset);
    ci::Rand::randomize();
    float pos_y = ci::randFloat(offset, kWindowHeight - offset);

    colonies_.push_back(
        Colony(population, glm::vec2(pos_x, pos_y), kColonyRadius));
  }
}

void World::GenerateFoodSources(const size_t num_food_sources) {
  for (size_t i = 0; i < num_food_sources; ++i) {
    float quantity = ci::Rand::randFloat(kMaxQuantity / 2.0f, kMaxQuantity);
    float offset = quantity + kOffset;  // FIXME: Quantity is not always equal to radius.

    ci::Rand::randomize();
    glm::vec2 position(ci::randFloat(offset, kWindowWidth - offset),
                       ci::randFloat(offset, kWindowHeight - offset));

    for (const Colony& colony : colonies_) {
      while (glm::length(colony.GetPosition() - position) <=
             colony.GetRadius() + quantity) {
        ci::Rand::randomize();
        position = glm::vec2(ci::randFloat(offset, kWindowWidth - offset),
                             ci::randFloat(offset, kWindowHeight - offset));
      }
    }

    food_sources_.push_back(FoodSource(position, quantity));
  }
}

void World::HandleBoundCollisions(Ant& ant) {
  bool is_collision = false;

  if ((ant.GetPosition().x + (ant.GetWidth() / 2.0f) >= kWindowWidth &&
       ant.GetVelocity().x > 0) ||
      (ant.GetPosition().x - (ant.GetWidth() / 2.0f) < 0 &&
       ant.GetVelocity().x < 0)) {
    ant.NegateXVel();
    is_collision = true;
  }

  if ((ant.GetPosition().y + (ant.GetWidth() / 2.0f) >= kWindowHeight &&
              ant.GetVelocity().y > 0) ||
             (ant.GetPosition().y - (ant.GetWidth() / 2.0f) < 0 &&
              ant.GetVelocity().y < 0)) {
    ant.NegateYVel();
    is_collision = true;
  }

  if (is_collision) {
    ant.GetDirection().TurnAround();
  }
}

bool World::IsAtLocation(const glm::vec2& ant_position,
                         const glm::vec2& location, const float distance) {
  return glm::length(ant_position - location) <= distance;
}

}  // namespace antsim