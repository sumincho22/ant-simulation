#include "direction.h"

namespace antsim {

Direction::Direction(const float speed, const float angle) {
  speed_ = speed;
  angle_ = angle;
}

void Direction::ApplyTurn(glm::vec2& velocity, float max_angle) {
  float rotation = GetRandomValue(-max_angle, max_angle);
  angle_ += rotation;
  velocity = glm::vec2(speed_ * cos(angle_), speed_ * sin(angle_));
}

void Direction::TurnAround() {
  angle_ += static_cast<float>(M_PI);
}

const float Direction::GetRandomValue(const float min_value, const float max_value) const {
  return min_value + (static_cast<float>(rand()) /
      static_cast<float>(RAND_MAX) * (max_value - min_value));
}

const float Direction::GetAngle() const { return angle_; }

}  // namespace antsim