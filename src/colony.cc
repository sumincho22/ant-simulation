#include "colony.h"

namespace antsim {

Colony::Colony(const size_t population, const glm::vec2& position,
               const float radius) {
  position_ = position;
  radius_ = radius;

  GenerateAnts(population);
}

void Colony::AdvanceOneFrame() {
  for (Ant& ant : ants_) {
    ant.AdvanceOneFrame();
  }
}

void Colony::Render() const {
  // Reset color to properly render ant model
  ci::gl::color(1, 1, 1);
  RenderAnts();

  ci::gl::color(kColor);
  ci::gl::drawSolidCircle(position_, radius_);
}

void Colony::GenerateAnts(size_t population) {
  float angle = 0;
  float increment = (2.0f * static_cast<float>(M_PI)) / population;
  for (size_t i = 0; i < population; ++i) {
    ants_.emplace_back(Ant(position_, angle, kAntSpeed));
    angle += increment;
  }
}

void Colony::RenderAnts() const {
  for (const Ant& ant : ants_) {
    ant.DrawModel();
  }
}

std::vector<Ant>& Colony::GetAnts() {
  return ants_;
}

float Colony::GetRadius() const {
  return radius_;
}

const glm::vec2& Colony::GetPosition() const {
  return position_;
}

}  // namespace antsim