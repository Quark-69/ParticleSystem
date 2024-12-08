#include "Utilities.h"

std::vector<float> Utility::generateCircleVertices(int nSeg, float radius)
{
	std::vector<float> vertices;

	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	for (int i = 0; i < nSeg; ++i)
	{
		float angle = 2.0f * glm::pi<float>() * i / nSeg;
		vertices.push_back(radius * glm::cos(angle));
		vertices.push_back(radius * glm::sin(angle));
	}

	return vertices;
}
