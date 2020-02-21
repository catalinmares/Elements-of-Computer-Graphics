#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <math.h>

namespace Object2DBuilder
{
	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, bool fill);
	Mesh* CreateBird(std::string name);

}

