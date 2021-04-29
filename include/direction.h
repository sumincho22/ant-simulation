#pragma once

#include <cmath>

#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

namespace antsim {

/**
 * This class handles the directional functions of an Ant and its movements.
 */
class Direction {
 public:
  /**
   * Creates a Direction object with the provided parameters.
   *
   * @param speed the speed of the Ant
   * @param angle the starting angle the Ant is directed towards
   */
  Direction(const float speed, const float angle);

  /**
   * Applies an angle rotation to the Ant's velocity vector.
   *
   * @param velocity    the Ant's velocity
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