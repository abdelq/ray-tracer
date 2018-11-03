#pragma once

#include <vector>

#define GLM_FORCE_RADIANS
#define GLM_PRECISION_HIGHP_FLOAT
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

typedef glm::float64 decimal;

#define PI (glm::pi<decimal>())
#define INFINITY (std::numeric_limits<decimal>::infinity())
#define EPSILON (std::numeric_limits<glm::float32>::epsilon())
