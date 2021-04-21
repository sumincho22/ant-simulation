#include "ant.h"

using ci::Color;
using glm::vec2;

namespace antsim {

Ant::Ant(const vec2& position, const vec2& velocity) :
 direction_(kSpeed, kStartingAngle)
{
  position_ = position;
  velocity_ = velocity;
  frame_count_ = 0;

  ci::Surface surface(60, 75, true);
  auto image = ci::loadImage(R"(C:\Users\scycl\Desktop\Cinder\my-projects\final-project-sumincho22\assets\ant.png)");
  ant_model_ = ci::gl::Texture2d::create(image);
}

void Ant::DrawModel() {
  ci::gl::pushModelMatrix();
  ci::gl::translate(position_);
  ci::gl::scale(0.03f, 0.03f);
  ci::gl::draw(ant_model_);
  ci::gl::popModelMatrix();
}

void Ant::UpdatePosition() {
  if (frame_count_ == kBigChange) {
    direction_.ApplyBigTurn(velocity_);
    frame_count_ = 0;
  } else if (frame_count_ % kSmallChange == 0) {
    direction_.ApplySmallTurn(velocity_);
  }

  if (position_.x <= 0 || position_.x >= kWindowLength) {
    NegateXVel();
  }
  if (position_.y <= 0 || position_.y >= kWindowHeight) {
    NegateYVel();
  }

  position_ += velocity_;

  frame_count_++;
}

void Ant::NegateXVel() {
  velocity_.x *= -1;
}

void Ant::NegateYVel() {
  velocity_.y *= -1;
}

}  // namespace antsim
