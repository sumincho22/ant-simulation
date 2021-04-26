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
  frame_count_ = 0;
}

void Ant::AdvanceOneFrame() {
  HandleMovement();
  frame_count_++;
}

void Ant::DrawModel() {
  // loading
  static ci::gl::Texture2dRef ant_model = ci::gl::Texture2d::create(ci::loadImage(
      R"(C:\Users\scycl\Desktop\Cinder\my-projects\final-project-sumincho22\assets\ant.png)"));
  if (width_ == -1 && height_ == -1) {
    width_ = static_cast<float>(ant_model->getWidth());
    height_ = static_cast<float>(ant_model->getHeight());
  }

  // drawing
  ci::gl::pushModelMatrix();
  ci::gl::translate(position_ +
                    kModelScale *
                        glm::vec2(width_ / 2.0f,
                                          height_ / 2.0f));
  ci::gl::rotate(direction_.GetAngle());
  ci::gl::translate(-kModelScale *
                    glm::vec2(width_ / 2.0f,
                              height_ / 2.0f));
  ci::gl::scale(kModelScale, kModelScale);
  ci::gl::draw(ant_model);
  ci::gl::popModelMatrix();
}

void Ant::HandleMovement() {
  if (position_.x + width_ > ci::app::getWindowSize().x || position_.x < 0) {
    CollideVertBound();
  } else if (position_.y + height_ > ci::app::getWindowSize().y || position_.y < 0) {
    CollideHorizBound();
  } else {
    Wander();
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

}  // namespace antsim
