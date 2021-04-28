#include "ant_simulation_app.h"

namespace antsim {

AntSimApp::AntSimApp() : world_() {
  ci::app::setFullScreen();
}

void AntSimApp::draw() {
  ci::gl::clear(kBackgroundColor);

  world_.Render();
}

void AntSimApp::update() {
  world_.AdvanceOneFrame();
}

}  // namespace antsim