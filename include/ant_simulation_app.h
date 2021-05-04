#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "world.h"

namespace antsim {

/**
 * A visual app for simulating the behavior of ants.
 */
class AntSimApp : public ci::app::App {
 public:
  AntSimApp();

  void draw() override;
  void update() override;

 private:
  const ci::Color kBackgroundColor = ci::Color("black");

  // World parameters
  const size_t kSimSpeed = 2;
  const size_t kNumColonies = 1;
  const size_t kNumFoodSources = 1;

  World world_;
};

}  // namespace antsim