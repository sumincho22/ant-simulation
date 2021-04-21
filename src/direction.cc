#include "direction.h"

namespace antsim {

Direction::Direction(const float speed, const float angle) {
  speed_ = speed;
  angle_ = angle;
}

void Direction::ApplySmallTurn(glm::vec2& velocity) {
  float angle_rotation = GetRandomValue(-kSmallTurn, kSmallTurn);
  angle_ += angle_rotation;
  velocity = glm::vec2(speed_ * cos(angle_), speed_ * sin(angle_));
}

void Direction::ApplyBigTurn(glm::vec2& velocity) {
  float angle_rotation = GetRandomValue(-kBigTurn, kBigTurn);
  angle_ += angle_rotation;
  velocity = glm::vec2(speed_ * cos(angle_), speed_ * sin(angle_));
}

const float Direction::GetAngle() const { return angle_; }

const float Direction::GetRandomValue(const float min_value, const float max_value) const {
  return min_value + (static_cast<float>(rand()) /
                      static_cast<float>(RAND_MAX) * (max_value - min_value));
}

}  // namespace antsim