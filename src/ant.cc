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

  auto image = ci::loadImage(R"(C:\Users\scycl\Desktop\Cinder\my-projects\final-project-sumincho22\assets\ant.png)");
  ant_model_ = ci::gl::Texture2d::create(image);
}

void Ant::AdvanceOneFrame() {
  frame_count_++;
}

void Ant::DrawModel() {
  ci::gl::pushModelMatrix();
  ci::gl::translate(position_);
//  ci::gl::translate(1, 1);
//  ci::gl::rotate(direction_.GetAngle()); //TODO: find a way to rotate by model's center
//  ci::gl::translate(-1, -1);
  ci::gl::scale(0.03f, 0.03f);
  ci::gl::draw(ant_model_);
  ci::gl::popModelMatrix();
}

void Ant::UpdatePosition() {
  position_ += velocity_;
}

void Ant::Wander() {
  size_t big_turn_prob = rand() % (kBigChange - frame_count_) + frame_count_;
  size_t small_turn_prob = rand() % kSmallChange;

  if (frame_count_ == big_turn_prob) {
    direction_.ApplyTurn(velocity_, kBigTurn);

    // reset the frame count so its value does not get too big
    frame_count_ = 0;

  } else if (frame_count_ % small_turn_prob == 0) {
    direction_.ApplyTurn(velocity_, kSmallTurn);
  }

  UpdatePosition();
}

void Ant::NegateXVel() {
  velocity_.x *= -1;
}

void Ant::NegateYVel() {
  velocity_.y *= -1;
}

}  // namespace antsim
