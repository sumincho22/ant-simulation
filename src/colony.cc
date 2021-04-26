#include "colony.h"

namespace antsim {

Colony::Colony(const size_t population, const glm::vec2& position, const float radius) {
  position_ = position;
  radius_ = radius;
  GenerateAnts(population);
}

void Colony::AdvanceOneFrame() {
  for (Ant& ant : ants_) {
    if (ant.GetState() == kGoingHome && IsAtColony(ant)) {
      ant.SetState(kGettingFood);
    }
    ant.AdvanceOneFrame();
  }
}

void Colony::Draw() {
  for (const Ant& ant : ants_) {
    ant.DrawModel();
  }

  ci::gl::color(ci::Color("green"));
  ci::gl::drawSolidCircle(position_, radius_);
}

void Colony::GenerateAnts(size_t population) {
  float angle = 0;
  float increment = (2.0f * static_cast<float>(M_PI)) / population;
  for (size_t i = 0; i < population; ++i) {
    glm::vec2 offset = glm::vec2(radius_ * cos(angle), radius_ * sin(angle));
    glm::vec2 spawn_point = position_ + offset;

    ants_.emplace_back(Ant(spawn_point, angle, kAntSpeed));
    angle += increment;
  }
}

bool Colony::IsAtColony(const Ant& ant) {
  return glm::length(ant.GetPosition() - position_) == radius_;
}

}