#pragma once

#include <cmath>

#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

namespace antsim {

/**
 * This class handles the direction of the ant using angles.
 */
class Direction {
 public:
  /**
   * Creates a direction with the provided speed and angle.
   *
   * @param speed the speed of the ant
   * @param angle the starting angle the ant is directed towards
   */
  Direction(const float speed, const float angle);

  /**
   * Applies an angle rotation to the ant's velocity vector.
   *
   * @param velocity    the ant's velocity
   * @param max_angle   the maximum magnitude of the angle rotation
   */
  void ApplyTurn(glm::vec2& velocity, float max_angle);

  void TurnAround();
  void TurnTowardsPoint(glm::vec2& velocity, const glm::vec2& pos_diff);

  const float GetAngle() const;

 private:
  float speed_;
  float angle_;
};

}  // namespace antsim