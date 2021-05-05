#include <catch2/catch.hpp>

#include "world.h"

using antsim::World;
using antsim::Colony;
using antsim::FoodSource;
using antsim::Ant;
using antsim::State;
using antsim::MarkablePoint;

// Testing constants
const float kWindowWidth = 1920;
const float kWindowHeight = 1080;

const size_t kTestNum = 3;
const glm::vec2 kTestPos(50, 90);
const glm::vec2 kTestPos2(60, 100);
const float kTestRadius = 5.0f;
const float kTestAngle = (float) M_PI;
const float kTestSpeed = 1.0f;
const float kTestFrames = 100;

TEST_CASE("World", "[world]") {
  World world(kTestNum, kTestNum, kTestNum);

  std::vector<Colony> colonies = world.GetColonies();
  std::vector<FoodSource> food_sources = world.GetFoodSources();

  SECTION("Constructor") {
    REQUIRE(colonies.size() == kTestNum);
    REQUIRE(food_sources.size() == kTestNum);
  }

  SECTION("Locations of colonies & food sources are different") {
    for (const Colony& colony : colonies) {
      for (const FoodSource& food_source : food_sources) {
        REQUIRE(colony.GetPosition() != food_source.GetPosition());
      }
    }
  }

  SECTION("Locations of colonies & food sources are within boundaries") {
    for (const Colony& colony : colonies) {
      REQUIRE(colony.GetPosition().x > 0);
      REQUIRE(colony.GetPosition().x < kWindowWidth);
      REQUIRE(colony.GetPosition().y > 0);
      REQUIRE(colony.GetPosition().y < kWindowHeight);
    }

    for (const FoodSource& food_source : food_sources) {
      REQUIRE(food_source.GetPosition().x > 0);
      REQUIRE(food_source.GetPosition().x < kWindowWidth);
      REQUIRE(food_source.GetPosition().y > 0);
      REQUIRE(food_source.GetPosition().y < kWindowHeight);
    }
  }
}

TEST_CASE("Colony", "[colony]") {
  Colony colony(kTestNum, kTestPos, kTestRadius);

  std::vector<Ant> ants = colony.GetAnts();

  SECTION("Constructor") {
    REQUIRE(ants.size() == kTestNum);
    REQUIRE(colony.GetPosition() == kTestPos);
    REQUIRE(colony.GetRadius() == kTestRadius);
  }

  SECTION("Ants are generated at the center of the colony") {
    for (const Ant& ant : ants) {
      REQUIRE(ant.GetPosition() == colony.GetPosition());
    }
  }
}

TEST_CASE("Food source", "[food_source]") {
  FoodSource food_source(kTestPos, kTestNum);

  SECTION("Constructor") {
    REQUIRE(food_source.GetPosition() == kTestPos);
    REQUIRE(food_source.GetQuantity() == kTestNum);
    REQUIRE(food_source.GetRadius() == (float) kTestNum);
  }

  SECTION("DecreaseQuantity") {
    auto val_before = food_source.GetQuantity();
    food_source.DecreaseQuantity();
    auto val_after = food_source.GetQuantity();

    REQUIRE(val_after - val_before == -1);
  }

  SECTION("Quantity cannot be below zero") {
    for (size_t i = 0; i < kTestNum; ++i) {
      food_source.DecreaseQuantity();
    }

    // Calling the method after depleting the entire quantity
    food_source.DecreaseQuantity();

    REQUIRE(food_source.GetQuantity() == 0);
  }

  SECTION("UpdateSize") {
    auto val_before = food_source.GetRadius();
    food_source.DecreaseQuantity();
    food_source.UpdateSize();
    auto val_after = food_source.GetRadius();

    REQUIRE(val_after - val_before == -1);
  }
}

TEST_CASE("Ant", "[ant]") {
  Ant ant(kTestPos, kTestAngle, kTestSpeed);

  SECTION("Constructor") {
    REQUIRE(ant.GetPosition() == kTestPos);
    REQUIRE(ant.GetState() == State::kWandering);
    REQUIRE(ant.GetDirection().GetAngle() == kTestAngle);
  }

  SECTION("Velocity vector is always same speed") {
    for (size_t i = 0; i < kTestNum; ++i) {
      ant.AdvanceOneFrame();

      float vec_mag = ceil(sqrt(pow(ant.GetVelocity().x, 2.0f) +
          pow(ant.GetVelocity().y, 2.0f)));

      REQUIRE(vec_mag == kTestSpeed);
    }
  }

  SECTION("Ant follows home markers") {
    ant.SetState(State::kGoingHome);

    MarkablePoint marker;
    marker.position = kTestPos2;

    std::vector<MarkablePoint*> home_markers = std::vector<MarkablePoint*>();
    home_markers.push_back(&marker);
    ant.SetHomeMarkers(home_markers);

    for (size_t i = 0; i < kTestFrames; ++i) {
      ant.AdvanceOneFrame();
    }

    REQUIRE(ceil(ant.GetPosition().x) == kTestPos2.x);
    REQUIRE(ceil(ant.GetPosition().y) == kTestPos2.y);
  }

  SECTION("Ant follows food markers") {
    ant.SetState(State::kGettingFood);

    MarkablePoint marker;
    marker.position = kTestPos2;

    std::vector<MarkablePoint*> food_markers = std::vector<MarkablePoint*>();
    food_markers.push_back(&marker);
    ant.SetFoodMarkers(food_markers);

    for (size_t i = 0; i < kTestFrames; ++i) {
      ant.AdvanceOneFrame();
    }

    REQUIRE(ceil(ant.GetPosition().x) == kTestPos2.x);
    REQUIRE(ceil(ant.GetPosition().y) == kTestPos2.y);
  }

  SECTION("Clear home markers") {
    MarkablePoint marker;
    marker.position = kTestPos2;

    std::vector<MarkablePoint*> home_markers = std::vector<MarkablePoint*>();
    home_markers.push_back(&marker);
    ant.SetHomeMarkers(home_markers);

    ant.ClearHomeMarkers();

    REQUIRE(ant.GetHomeMarkers().size() == 0);
  }

  SECTION("Clear food markers") {
    MarkablePoint marker;
    marker.position = kTestPos2;

    std::vector<MarkablePoint*> food_markers = std::vector<MarkablePoint*>();
    food_markers.push_back(&marker);
    ant.SetFoodMarkers(food_markers);

    ant.ClearFoodMarkers();

    REQUIRE(ant.GetFoodMarkers().size() == 0);
  }
}