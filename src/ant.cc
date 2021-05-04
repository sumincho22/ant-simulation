#include "ant.h"

using ci::Color;
using glm::vec2;

namespace antsim {
float Ant::width_ = -1;
float Ant::height_ = -1;

Ant::Ant(const glm::vec2& position, const float angle, const float speed)
    : direction_(speed, angle) {
  position_ = position;
  velocity_ = vec2();
  state_ = State::kWandering;
  frame_count_ = 0;
  point_index_ = 0;
  markable_points_ = std::vector<MarkablePoint*>();
}

void Ant::AdvanceOneFrame() {
  HandleMovement();
  frame_count_++;
}

void Ant::DrawModel() const {
  // Loading
  static ci::gl::Texture2dRef ant_model = ci::gl::Texture2d::create(ci::loadImage(
      R"(C:\Users\scycl\Desktop\Cinder\my-projects\final-project-sumincho22\assets\ant.png)"));
  if (width_ == -1 && height_ == -1) {
    width_ = kModelScale * static_cast<float>(ant_model->getWidth());
    height_ = kModelScale * static_cast<float>(ant_model->getHeight());
  }

  // Drawing
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
  switch (state_) {
    case kWandering:
      Wander();
      break;
    case kGoingHome:
      FollowMarkers();
      break;
    case kGettingFood:
      FollowFoodMarkers(); // TODO: Need to implement.
      break;
    default:
      break;
  }
}

void Ant::Wander() {
  int big_turn_prob = ci::randInt(frame_count_, kBigChange);
  int small_turn_prob = ci::randInt(1, kSmallChange);

  if (frame_count_ == big_turn_prob) {
    direction_.ApplyTurn(velocity_, kBigTurn);

    // reset the frame count so its value does not get too big
    frame_count_ = 0;

  } else if (frame_count_ % small_turn_prob == 0) {
    direction_.ApplyTurn(velocity_, kSmallTurn);
  }

  UpdatePosition();
}

void Ant::FollowMarkers() {
  if (glm::length(markable_points_[point_index_]->position - position_)
      <= width_) {
    if (point_index_ > 0) {
      point_index_--;
    }
  }
  MoveTowardsPoint(markable_points_[point_index_]->position);
}

void Ant::FollowFoodMarkers() {
  if (glm::length(food_markers_[food_marker_index_]->position - position_)
      <= width_) {
    if (food_marker_index_ < food_markers_.size() - 1) {
      food_marker_index_++;
    }
  }
  MoveTowardsPoint(food_markers_[food_marker_index_]->position);
}

void Ant::MoveTowardsPoint(const glm::vec2& point) {
  glm::vec2 pos_diff = point - position_;
  direction_.TurnTowardsPoint(velocity_, pos_diff);
  UpdatePosition();
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
  food_marker_index_ = 0;
}

void Ant::UpdatePosition() {
  position_ += velocity_;
}

void Ant::NegateXVel() {
  velocity_.x *= -1;
}

void Ant::NegateYVel() {
  velocity_.y *= -1;
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

const vec2& Ant::GetVelocity() const {
  return velocity_;
}

float Ant::GetWidth() const {
  return width_;
}

float Ant::GetHeight() const {
  return height_;
}

Direction& Ant::GetDirection() {
  return direction_;
}

void Ant::RenderFood() const {
  glm::vec2 food_pos(
      position_.x + (width_ / 2.0f) * cos(direction_.GetAngle()),
      position_.y + (height_ / 2.0f) * sin(direction_.GetAngle()));

  ci::gl::color(kFoodColor);
  ci::gl::drawSolidCircle(food_pos, 5);
  ci::gl::color(1, 1, 1);
}

const std::vector<MarkablePoint*>& Ant::GetMarkers() const {
  return markable_points_;
}

void Ant::SetMarkers(const std::vector<MarkablePoint*>& food_markers) {
  food_markers_ = food_markers;
}

}  // namespace antsim
