#include "direction.h"

namespace antsim {

Direction::Direction(const float speed, const float angle) {
  speed_ = speed;
  angle_ = angle;
}

void Direction::ApplyTurn(glm::vec2& velocity, float max_angle) {
  float rotation = ci::randFloat(-max_angle, max_angle);
  angle_ += rotation;
  velocity = speed_ * glm::vec2(cos(angle_), sin(angle_));
}

void Direction::TurnTowardsPoint(glm::vec2& velocity,
                                 const glm::vec2& pos_diff) {
  if (pos_diff.x > 0) {
    angle_ = atan(pos_diff.y / pos_diff.x);
  } else {
    angle_ = atan(pos_diff.y / pos_diff.x) - static_cast<float>(M_PI);
  }

  velocity = speed_ * glm::vec2(cos(angle_), sin(angle_));
}

void Direction::TurnAround() {
  angle_ += static_cast<float>(M_PI);
}

const float Direction::GetAngle() const {
  return angle_;
}

}  // namespace antsim