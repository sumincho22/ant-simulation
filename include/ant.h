#pragma once

#include <cmath>

#include "cinder/gl/gl.h"
#include "direction.h"
#include "state.h"

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
  Ant(const glm::vec2& position, const float angle, const float speed);

  void AdvanceOneFrame();

  void DrawModel() const;

  State GetState() const;
  void SetState(State state);

 private:
  const float kModelScale = 0.03f;

  const size_t kSmallChange = 10;
  const size_t kBigChange = 200;

  const float kSmallTurn = static_cast<float>(M_PI) / 8;
  const float kBigTurn = static_cast<float>(M_PI) / 2;

  size_t frame_count_;

  glm::vec2 position_;

 public:
  const glm::vec2& GetPosition() const;

 private:
  glm::vec2 velocity_;

  Direction direction_;
  State state_;

  static float width_;
  static float height_;

  void HandleMovement();

  void CollideVertBound();
  void CollideHorizBound();
  void Wander();

  void UpdatePosition();

  void NegateXVel();
  void NegateYVel();

  void RenderFood() const;
};

}  // namespace antsim
