#include "ant_simulation_app.h"

namespace antsim {

AntSimApp::AntSimApp() :
      ant_(glm::vec2(kWindowWidth / 3, kWindowHeight / 3), 0, 2) {
  ci::app::setWindowSize(kWindowWidth, kWindowHeight);
  ci::app::setFullScreen();
}

void AntSimApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  ant_.DrawModel();
}

void AntSimApp::update() {
  ant_.AdvanceOneFrame();
}

}  // namespace antsim