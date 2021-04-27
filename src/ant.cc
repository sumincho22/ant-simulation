#include "ant.h"

#include <cinder/app/AppBase.h>

using ci::Color;
using glm::vec2;

namespace antsim {
//
float Ant::width_ = -1;
float Ant::height_ = -1;

Ant::Ant(const glm::vec2& position, const float angle, const float speed)
    : direction_(speed, angle) {
  position_ = position;
  velocity_ = vec2();
  state_ = State::kWandering;
  frame_count_ = 0;
}

void Ant::AdvanceOneFrame() {
  HandleMovement();
  frame_count_++;
}

void Ant::DrawModel() const {
  // loading
  static ci::gl::Texture2dRef ant_model = ci::gl::Texture2d::create(ci::loadImage(
      R"(C:\Users\scycl\Desktop\Cinder\my-projects\final-project-sumincho22\assets\ant.png)"));
  if (width_ == -1 && height_ == -1) {
    width_ = kModelScale * static_cast<float>(ant_model->getWidth());
    height_ = kModelScale * static_cast<float>(ant_model->getHeight());
  }

  // drawing
  ci::gl::pushModelMatrix();
  ci::gl::translate(position_);
  ci::gl::rotate(direction_.GetAngle());
  ci::gl::translate(-glm::vec2(width_ / 2.0f, height_ / 2.0f));
  ci::gl::scale(kModelScale, kModelScale);
  ci::gl::draw(ant_model);
  ci::gl::popModelMatrix();

  if (state_ == kGoingHome) {
    RenderFood();
  }
}

void Ant::HandleMovement() {
  if ((position_.x + (width_ / 2.0f) >= ci::app::getWindowSize().x &&
       velocity_.x > 0) ||
      (position_.x - (width_ / 2.0f) < 0 && velocity_.x < 0)) {
    CollideVertBound();
    return;
  } else if ((position_.y + (height_ / 2.0f) >= ci::app::getWindowSize().y &&
              velocity_.y > 0) ||
             (position_.y - (height_ / 2.0f) < 0 && velocity_.y < 0)) {
    CollideHorizBound();
    return;
  }

  switch (state_) {
    case kWandering:
      Wander();
      break;
    case kGettingFood:
      break;
    case kGoingHome:
      break;
    default:
      break;
  }
}

void Ant::UpdatePosition() {
  position_ += velocity_;
}

void Ant::Wander() {
  int big_turn_prob = rand() % (kBigChange - frame_count_) + frame_count_;
  int small_turn_prob = rand() % kSmallChange + 1;

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

void Ant::CollideVertBound() {
  NegateXVel();
  direction_.TurnAround();
  UpdatePosition();
}

void Ant::CollideHorizBound() {
  NegateYVel();
  direction_.TurnAround();
  UpdatePosition();
}

State Ant::GetState() const {
  return state_;
}

void Ant::SetState(State state) {
  state_ = state;
}

const vec2& Ant::GetPosition() const {
  return position_;
}

void Ant::RenderFood() const {
  ci::gl::color(ci::Color("green"));
  ci::gl::drawSolidCircle(position_, 5);
}

}  // namespace antsim
