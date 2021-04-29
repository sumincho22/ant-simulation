#pragma once

#include "cinder/gl/gl.h"

namespace antsim {

/**
 * This class holds the properties of a food source.
 */
class FoodSource {
 public:
  /**
   * Creates a food source with the provided position and quantity.
   *
   * @param position    the position of the food source
   * @param quantity    the quantity of the food source
   */
  FoodSource(const glm::vec2& position, const float quantity);

  void Render() const;

  void UpdateSize();
  void DecreaseQuantity();

  const glm::vec2& GetPosition() const;
  float GetRadius() const;
  float GetQuantity() const;

 private:
  const ci::Color kColor = ci::Color("green");

  // Radius decreases per this value
  const float kRadiusIncrement = 1;

  glm::vec2 position_;
  float radius_;
  float quantity_;
};

}
