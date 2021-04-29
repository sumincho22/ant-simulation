#pragma once

namespace antsim {

/**
 * This struct represents markable points of the world grid.
 */
struct MarkablePoint {
  glm::vec2 position;
  size_t count = 0;
};

}