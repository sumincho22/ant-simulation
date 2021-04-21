#pragma once

#include <cmath>

#include "cinder/gl/gl.h"

namespace antsim {

class Direction {
 public:
  Direction(const float speed, const float angle);

  void ApplySmallTurn(glm::vec2& velocity);
  void ApplyBigTurn(glm::vec2& velocity);

 private:
  float kSmallTurn = static_cast<float>(M_PI) / 8;
  float kBigTurn = static_cast<float>(M_PI) / 2;

  float speed_;
  float angle_;

  const float GetRandomValue(const float min_value, const float max_value) const;

};

}  // namespace antsim