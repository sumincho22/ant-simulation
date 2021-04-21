#include "ant.h"

using ci::Color;
using glm::vec2;

namespace antsim {

Ant::Ant(const Color& color, const vec2& position, const vec2& velocity) :
 direction_(kSpeed, kStartingAngle)
{
  color_ = color;
  position_ = position;
  velocity_ = velocity;
  frame_count_ = 0;
}

void Ant::DrawModel() {
  ci::gl::color(Color(color_));
  ci::gl::drawSolidCircle(position_, kRadius);
}

void Ant::UpdatePosition() {
  if (frame_count_ % kSmallChange == 0) {
    direction_.ApplySmallTurn(velocity_);
  }
  if (frame_count_ == kBigChange) {
    direction_.ApplyBigTurn(velocity_);
    frame_count_ = 0;
  }

  position_ += velocity_;

  frame_count_++;
}

}  // namespace antsim
