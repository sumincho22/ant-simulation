#include "world.h"

namespace antsim {

World::World() {
  GenerateGrid();
  GenerateColonies(1);
}

void World::Render() const {
  for (const Colony& colony : colonies_) {
    colony.Render();
  }
}

void World::AdvanceOneFrame() {
  for (Colony& colony : colonies_) {
    colony.AdvanceOneFrame();
  }
}

void World::GenerateGrid() {
  size_t grid_width = static_cast<size_t>(ci::app::getWindowSize().x) / kAntSpeed;
  size_t grid_height = static_cast<size_t>(ci::app::getWindowSize().y) / kAntSpeed;

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

    colonies_.push_back(Colony(population, ci::app::getWindowCenter(), kColonyRadius)); // TODO: Randomize these parameters
  }
}

//void World::GenerateFoodSources(const size_t num_food_sources) {
//}

}