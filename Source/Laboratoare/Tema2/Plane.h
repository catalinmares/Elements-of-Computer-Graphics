#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <math.h>

namespace Plane
{
	Mesh* CreateBody(std::string name, glm::vec3 color);
	Mesh* CreateLeftWing(std::string name, glm::vec3 color);
	Mesh* CreateRightWing(std::string name, glm::vec3 color);
	Mesh* CreateTail(std::string name, glm::vec3 color);
	Mesh* CreateHead(std::string name, glm::vec3 color);
	Mesh* CreatePropellerSupport(std::string name, glm::vec3 color);
	Mesh* CreatePropeller(std::string name, glm::vec3 color);

	Mesh* CreatePilotBody(std::string name, glm::vec3 color);
	Mesh* CreatePilotNeck(std::string name, glm::vec3 color);
	Mesh* CreatePilotHead(std::string name, glm::vec3 color);
	Mesh* CreatePilotArm(std::string name, glm::vec3 color);
	Mesh* CreatePilotHand(std::string name, glm::vec3 color);
	Mesh* CreatePilotHair(std::string name, glm::vec3 color);
	Mesh* CreatePilotGlasses(std::string name, glm::vec3 color);
}

