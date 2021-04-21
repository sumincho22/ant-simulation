#include "ant_simulation_app.h"

namespace antsim {

AntSimApp::AntSimApp() :
      ant_(glm::vec2(kWindowWidth / 3, kWindowHeight / 3), glm::vec2(1, 0)) {
  ci::app::setWindowSize(kWindowWidth, kWindowHeight);
}

void AntSimApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  ant_.DrawModel();
}

void AntSimApp::update() {
  ant_.UpdatePosition();
}

}  // namespace antsim