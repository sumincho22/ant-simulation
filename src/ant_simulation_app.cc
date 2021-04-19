#include "ant_simulation_app.h"

namespace antsim {

AntSimApp::AntSimApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void AntSimApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
}

void AntSimApp::update() {}

}  // namespace antsim