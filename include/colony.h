#pragma once

#include "ant.h"

namespace antsim {

class Colony {
 public:
  Colony(const size_t population, const glm::vec2& position, const float radius);

  void AdvanceOneFrame();

  void Draw();

 private:
  const float kAntSpeed = 2;

  glm::vec2 position_;
  float radius_;

  std::vector<Ant> ants_;

  void GenerateAnts(const size_t population);

};

}
