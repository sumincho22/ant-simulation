#include "ant_simulation_app.h"

namespace antsim {

AntSimApp::AntSimApp() : ant_(ci::Color("red"), glm::vec2(kWindowSize / 2, kWindowSize / 2), glm::vec2(5, 5)) {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
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