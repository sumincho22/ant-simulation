#include "ant_simulation_app.h"

namespace antsim {

AntSimApp::AntSimApp() :
      colony_(100, glm::vec2(kWindowWidth / 2.0f, kWindowHeight / 2.0f), 50) {
  ci::app::setWindowSize(kWindowWidth, kWindowHeight);
  ci::app::setFullScreen();
}

void AntSimApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  colony_.Draw();
}

void AntSimApp::update() {
  colony_.AdvanceOneFrame();
}

}  // namespace antsim