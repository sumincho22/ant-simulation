#include "food_source.h"

namespace antsim {

FoodSource::FoodSource(const glm::vec2& position, const size_t quantity) {
  position_ = position;
  quantity_ = static_cast<float>(quantity);
  radius_ = quantity / kRadiusIncrement;
}

void FoodSource::Render() const {
  ci::gl::color(kColor);
  ci::gl::drawSolidCircle(position_, radius_);
}

void FoodSource::UpdateSize() {
  radius_ = quantity_ / kRadiusIncrement;
}

void FoodSource::DecreaseQuantity() {
  if (quantity_ > 0) {
    quantity_--;
  }
}

const glm::vec2& FoodSource::GetPosition() const {
  return position_;
}

float FoodSource::GetRadius() const {
  return radius_;
}

float FoodSource::GetQuantity() const {
  return quantity_;
}

}  // namespace antsim