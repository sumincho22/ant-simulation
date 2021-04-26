#include "ant_simulation_app.h"

namespace antsim {

AntSimApp::AntSimApp() :
      colony_(50, glm::vec2(kColonyPosX, kColonyPosY), 50) {
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