#include <catch2/catch.hpp>

#include "world.h"

using antsim::World;
using antsim::Colony;
using antsim::FoodSource;

// Testing constants
const size_t kTestNum = 3;
const float kWindowWidth = 1920;
const float kWindowHeight = 1080;

TEST_CASE("World", "[world]") {
  World world(kTestNum, kTestNum, kTestNum);

  std::vector<Colony> colonies = world.GetColonies();
  std::vector<FoodSource> food_sources = world.GetFoodSources();

  SECTION("Constructor") {
    REQUIRE(world.GetColonies().size() == kTestNum);
    REQUIRE(world.GetFoodSources().size() == kTestNum);
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