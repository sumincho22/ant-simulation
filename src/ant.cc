#include "ant.h"

using ci::Color;
using glm::vec2;

namespace antsim {

Ant::Ant(const Color& color, const vec2& position, const vec2& velocity) {
  color_ = color;
  position_ = position;
  velocity_ = velocity;
}

void Ant::DrawModel() {
  ci::gl::color(Color(color_));
  ci::gl::drawSolidCircle(position_, kRadius);
}

void Ant::UpdatePosition() {
  position_ += velocity_;
}

}
