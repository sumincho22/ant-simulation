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
  start_pos_ = position;
  position_ = position;
  velocity_ = vec2();
  state_ = State::kWandering;
  frame_count_ = 0;
  point_index_ = 0;
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
      Wander();
      break;
    case kGoingHome:
      FollowMarkers();
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
  glm::vec2 food_pos(position_.x + (width_ / 2.0f) * cos(direction_.GetAngle()),
                     position_.y + (height_ / 2.0f) * sin(direction_.GetAngle()));

  ci::gl::color(ci::Color("green"));
  ci::gl::drawSolidCircle(food_pos, 5);
  ci::gl::color(1,1,1);
}

void Ant::AddMarker(MarkablePoint* marker) {
  markable_points_.emplace_back(marker);
  point_index_ = markable_points_.size() - 1;
}

void Ant::IncrementMarkers() {
  for (MarkablePoint* marker : markable_points_) {
    marker->count++;
  }
}

void Ant::ClearMarkers() {
  markable_points_.clear();
  point_index_ = 0;
}

void Ant::FollowMarkers() {
  if (glm::length(2.0f * (markable_points_[point_index_]->position) - position_) <= width_) {
    if (point_index_ == 0) {
      MoveTowardsPoint(start_pos_);
      return;
    }
    point_index_--;
    markable_points_.pop_back();
  }
  MoveTowardsPoint(2.0f * (markable_points_[point_index_]->position));
}

void Ant::MoveTowardsPoint(const glm::vec2& point) {
  glm::vec2 pos_diff = point - position_;
  direction_.TurnTowardsPoint(velocity_, pos_diff);
  UpdatePosition();
}

}  // namespace antsim
