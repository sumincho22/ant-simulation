#include <catch2/catch.hpp>

#include "world.h"

using antsim::World;
using antsim::Colony;
using antsim::FoodSource;
using antsim::Ant;

// Testing constants
const float kWindowWidth = 1920;
const float kWindowHeight = 1080;

const size_t kTestNum = 3;
const glm::vec2 kTestPos(50, 90);
const float kTestRadius = 5.0f;

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