#pragma once

#include "ant.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "world.h"

namespace antsim {

/**
 * An app for visualizing the behavior of ants.
 */
class AntSimApp : public ci::app::App {
 public:
  AntSimApp();

  void draw() override;
  void update() override;

 private:
  World world_;
};

}  // namespace antsim