#pragma once

#include "cinder/gl/gl.h"

namespace antsim {

class FoodSource {
 public:
  FoodSource(const glm::vec2& position, const float quantity);

  void Render() const;

  void UpdateSize();
  void DecreaseQuantity();

  const glm::vec2& GetPosition() const;
  float GetRadius() const;
  float GetQuantity() const;

 private:
  const float kRadiusIncrement = 1;

  glm::vec2 position_;
  float radius_;
  float quantity_;
};

}
