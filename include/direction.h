#pragma once

#include <cmath>

#include "cinder/gl/gl.h"

namespace antsim {

/**
 * This class handles the directional functions of an Ant and its movements
 */
class Direction {
 public:
  /**
   * Creates a Direction object with the provided parameters
   *
   * @param speed the speed of the Ant
   * @param angle the starting angle the Ant is directed towards
   */
  Direction(const float speed, const float angle);

  /**
   * Applies a minimal angle rotation to the Ant's velocity vector
   *
   * @param velocity the Ant's velocity
   */
  void ApplySmallTurn(glm::vec2& velocity);

  /**
   * Applies a relatively large angle rotation to the Ant's velocity vector
   *
   * @param velocity the Ant's velocity
   */
  void ApplyBigTurn(glm::vec2& velocity);

  const float GetAngle() const;

 private:
  float kSmallTurn = static_cast<float>(M_PI) / 8;
  float kBigTurn = static_cast<float>(M_PI) / 2;

  float speed_;
  float angle_;

  const float GetRandomValue(const float min_value, const float max_value) const;

};

}  // namespace antsim