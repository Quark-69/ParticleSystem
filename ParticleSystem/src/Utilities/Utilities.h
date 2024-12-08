#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>

class Utility
{
public:
	static std::vector<float> generateCircleVertices(int nSeg, float radius);
};