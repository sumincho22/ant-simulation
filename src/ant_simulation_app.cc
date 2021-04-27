#include "ant_simulation_app.h"

namespace antsim {

AntSimApp::AntSimApp() : world_() {
  ci::app::setFullScreen();
}

void AntSimApp::draw() {
  ci::gl::clear(ci::Color("black"));
  world_.Render();
}

void AntSimApp::update() {
  world_.AdvanceOneFrame();
}

}  // namespace antsim