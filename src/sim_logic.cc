#include "sim_logic.h"

namespace antsim {

SimLogic::SimLogic() {
}

const float SimLogic::GetRandomValue(const float min, const float max) {
  return min + (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) *
                (max - min));
}

}  // namespace antsim