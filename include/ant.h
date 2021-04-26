#pragma once

#include <cmath>
#include <stdlib.h>

#include "cinder/gl/gl.h"
#include "direction.h"

namespace antsim {

/**
 * This class holds all the properties of an Ant.
 */
class Ant {
 public:
  /**
   * Creates an Ant with the provided position and velocity.
   *
   * @param position the location of the Ant (the x- and y-coordinates)
   * @param velocity the velocity of the Ant (in x- and y-velocities)
   */
  Ant(const glm::vec2& position, const glm::vec2& velocity);

  void AdvanceOneFrame();

  void DrawModel();

  void Wander();

  void UpdatePosition();
  void NegateXVel();
  void NegateYVel();

 private:
  float kSmallTurn = static_cast<float>(M_PI) / 8;
  float kBigTurn = static_cast<float>(M_PI) / 2;

  float kSpeed = 1;
  float kStartingAngle = static_cast<float>(M_PI) / 2;

  float kWindowLength = 1500;
  float kWindowHeight = 1000;

  size_t kSmallChange = 10;
  size_t kBigChange = 100;

  glm::vec2 position_;
  glm::vec2 velocity_;
  Direction direction_;
  size_t frame_count_;

  ci::gl::Texture2dRef ant_model_;

};

}  // namespace antsim
