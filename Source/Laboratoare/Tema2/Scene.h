#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <math.h>

namespace Scene
{
	Mesh* CreateSea(std::string name, glm::vec3 color);\
	Mesh* CreateCloud(std::string name, glm::vec3 color);
	Mesh* CreateLifeBack(std::string name, glm::vec3 color);
	Mesh* CreateFuelMax(std::string name, glm::vec3 color);
	Mesh* CreateFuelCurrent(std::string name, glm::vec3 color);
}

