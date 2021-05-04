#pragma once

#include "ant.h"

namespace antsim {

/**
 * This class holds properties of an ant colony and visualizes the colony.
 */
class Colony {
 public:
  /**
   * Creates a colony with the provided population, position, and radius.
   *
   * @param population  the number of ants in the colony
   * @param position    the position of the colony
   * @param radius      the radius of the colony circle
   */
  Colony(const size_t population,
         const glm::vec2& position, const float radius);

  void AdvanceOneFrame();
  void Render() const;

  std::vector<Ant>& GetAnts();
  const glm::vec2& GetPosition() const;
  float GetRadius() const;

 private:
  const ci::Color kColor = ci::Color("purple");
  const float kAntSpeed = 2;

  glm::vec2 position_;
  float radius_;
  std::vector<Ant> ants_;

  void GenerateAnts(const size_t population);
  void RenderAnts() const;
};

}  // namespace antsim
