#pragma once

#include "ant.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "colony.h"

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
  const float kColonyPosX = 960;
  const float kColonyPosY = 540;

  Colony colony_;
};

}  // namespace antsim