#include "ant_simulation_app.h"

namespace antsim {

AntSimApp::AntSimApp() : world_(kSimSpeed, kNumColonies, kNumFoodSources) {
  ci::app::setFullScreen();
}

void AntSimApp::setup() {
  ci::audio::SourceFileRef source_file =
      ci::audio::load(ci::app::loadAsset("Jungle Mission.wav"));
  m_voice_ = ci::audio::Voice::create(source_file);
  m_voice_->start();
}

void AntSimApp::draw() {
  ci::gl::clear(kBackgroundColor);

  world_.Render();
}

void AntSimApp::update() {
  world_.AdvanceOneFrame();
}

}  // namespace antsim