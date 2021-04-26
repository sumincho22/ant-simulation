#pragma once

#include "ant.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace antsim {

/**
 * An app for visualizing the behavior of ants.
 */
class AntSimApp : public ci::app::App {
 public:
  AntSimApp();

  void draw() override;
  void update() override;

  const int kWindowWidth = 1920;
  const int kWindowHeight = 1080;

 private:
  Ant ant_;
};

}  // namespace antsim