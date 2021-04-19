#include "ant_simulation_app.h"

using antsim::AntSimApp;

void prepareSettings(AntSimApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(AntSimApp, ci::app::RendererGl, prepareSettings);