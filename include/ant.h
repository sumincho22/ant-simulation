#pragma once

#include <cmath>

#include "cinder/gl/gl.h"
#include "direction.h"

namespace antsim {

class Ant {
 public:
  Ant(const ci::Color& color, const glm::vec2& position, const glm::vec2& velocity);
  
  void DrawModel();

  void UpdatePosition();
  void NegateXVel();
  void NegateYVel();

 private:
  float kSpeed = 1;
  float kStartingAngle = static_cast<float>(M_PI) / 2;
  float kRadius = 4;

  size_t kSmallChange = 10;
  size_t kBigChange = 100;

  ci::Color color_;
  glm::vec2 position_;
  glm::vec2 velocity_;
  Direction direction_;
  size_t frame_count_;

  ci::gl::Texture2dRef ant_model_;

};

}  // namespace antsim
