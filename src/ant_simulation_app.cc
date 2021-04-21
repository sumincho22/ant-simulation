#include "ant_simulation_app.h"

namespace antsim {

AntSimApp::AntSimApp() :
      ant_(ci::Color("red"), glm::vec2(kWindowWidth / 2, kWindowHeight / 2), glm::vec2(1, 0)) {
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