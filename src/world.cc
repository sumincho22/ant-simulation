#include "world.h"

namespace antsim {

World::World(const size_t sim_speed,
             const size_t num_colonies, const size_t num_food_sources) {
  frame_count_ = 0;
  sim_speed_ = sim_speed;
  food_markers_ = std::vector<MarkablePoint*>();

  GenerateGrid();
  GenerateColonies(num_colonies);
  GenerateFoodSources(num_food_sources);
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
      for (FoodSource& food_source : food_sources_) {
        if (food_source.GetQuantity() <= 0 && ant.GetState() == kGettingFood) {
          food_markers_.clear();
          ant.ClearFoodMarkers();
          ant.SetState(kWandering);
        } else if (ant.GetState() != kGoingHome &&
                   IsAtLocation(ant.GetPosition(),
                                food_source.GetPosition(),
                                food_source.GetRadius())) {
          ant.AddHomeMarker(&grid_
                            [(size_t) food_source.GetPosition().x / sim_speed_]
                            [(size_t) food_source.GetPosition().y / sim_speed_]);
          ant.SetState(kGoingHome);
          ant.IncrementMarkers();

          if (food_markers_.empty()) {
            food_markers_ = ant.GetHomeMarkers();
          }

          food_source.DecreaseQuantity();
          food_source.UpdateSize();
        }
      }

      HandleBoundCollisions(ant);

      size_t pos_x =
          static_cast<size_t>(ant.GetPosition().x) / sim_speed_;
      size_t pos_y =
          static_cast<size_t>(ant.GetPosition().y) / sim_speed_;

      // Adding markers
      if (ant.GetState() != kGoingHome &&
          (frame_count_ == 0 || frame_count_ % 10 == 0)) {
        ant.AddHomeMarker(&grid_[pos_x][pos_y]);
      }

      // Ant returns to the colony with food.
      if (ant.GetState() == kGoingHome && IsAtLocation(ant.GetPosition(),
                                                       colony.GetPosition(),
                                                       colony.GetRadius())) {
        ant.ClearHomeMarkers();
        ant.ClearFoodMarkers();
        ant.AddHomeMarker(&grid_[pos_x][pos_y]);

        if (!food_markers_.empty()) {
          ant.SetState(kGettingFood);
          ant.SetFoodMarkers(food_markers_);
        } else {
          ant.SetState(kWandering);
        }
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
  size_t grid_width = kWindowWidth / sim_speed_;
  size_t grid_height = kWindowHeight / sim_speed_;

  grid_.resize(grid_width + 1);
  for (size_t pos_x = 0; pos_x <= grid_width; ++pos_x) {
    grid_[pos_x].resize(grid_height + 1);
    for (size_t pos_y = 0; pos_y <= grid_height; ++pos_y) {
      grid_[pos_x][pos_y].position =
          glm::vec2(sim_speed_ * pos_x, sim_speed_ * pos_y);
    }
  }
}

void World::GenerateColonies(const size_t num_colonies) {
  for (size_t i = 0; i < num_colonies; ++i) {
    size_t population = rand() % kMinPopulation + kMinPopulation;
    float offset = kColonyRadius + kMargin;

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
    size_t quantity = ci::Rand::randInt(kMaxQuantity / 2, kMaxQuantity);

    // NOTE: Quantity is not always equal to radius.
    float offset = static_cast<float>(quantity) + kMargin;

    ci::Rand::randomize();
    glm::vec2 position(ci::randFloat(offset, kWindowWidth - offset),
                       ci::randFloat(offset, kWindowHeight - offset));

    // Compare food source location to other colonies' locations.
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
  // Using to handle corner boundary collisions.
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

const std::vector<Colony>& World::GetColonies() const {
  return colonies_;
}

const std::vector<FoodSource>& World::GetFoodSources() const {
  return food_sources_;
}

}  // namespace antsim