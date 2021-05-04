#pragma once

namespace antsim {

/**
 * This struct represents a markable point on the world grid.
 */
struct MarkablePoint {
  glm::vec2 position;
  size_t count = 0;
};

}  // namespace antsim