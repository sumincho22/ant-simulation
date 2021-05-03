#pragma once

#include <cinder/app/AppBase.h>
#include <cmath>

#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "direction.h"
#include "markable_point.h"
#include "state.h"

namespace antsim {

/**
 * This class holds the properties and handles the path movements of an ant.
 */
class Ant {
 public:
  /**
   * Creates an ant with the provided position, angle, and speed.
   *
   * @param position    the position of the ant
   * @param angle       the angle the ant is facing
   * @param speed       the speed of the ant
   */
  Ant(const glm::vec2& position, const float angle, const float speed);

  void AdvanceOneFrame();
  void DrawModel() const;

  // Marker functions
  void AddMarker(MarkablePoint* marker);
  void IncrementMarkers();
  void ClearMarkers();

  void NegateXVel();
  void NegateYVel();

  const glm::vec2& GetPosition() const;
  const glm::vec2& GetVelocity() const;
  State GetState() const;
  void SetState(State state);
  float GetWidth() const;
  float GetHeight() const;
  Direction& GetDirection();

 private:
  const ci::Color kFoodColor = ci::Color("green");
  const float kModelScale = 0.03f;

  // Constants for small and big turn probabilities
  const size_t kSmallChange = 10;
  const size_t kBigChange = 200;

  // Angle rotation increments for small and big turns
  const float kSmallTurn = static_cast<float>(M_PI) / 8;
  const float kBigTurn = static_cast<float>(M_PI) / 2;

  static float width_;
  static float height_;

  size_t frame_count_;
  size_t point_index_;

  glm::vec2 start_pos_;

 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  Direction direction_;
  State state_;

  std::vector<MarkablePoint*> markable_points_;

  void RenderFood() const;

  void UpdatePosition();

  // Movement functions
  void HandleMovement();
  void Wander();
  void FollowMarkers();
  void MoveTowardsPoint(const glm::vec2& point);
};

}  // namespace antsim
