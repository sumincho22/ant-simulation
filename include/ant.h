#pragma once

#include "cinder/gl/gl.h"

namespace antsim {

class Ant {
 public:
  Ant(const ci::Color& color, const glm::vec2& position, const glm::vec2& velocity);

  void DrawModel();

  void UpdatePosition();

 private:
  float kSpeed = 4;
  float kRadius = 4;

  ci::Color color_;
  glm::vec2 position_;
  glm::vec2 velocity_;

};

}
