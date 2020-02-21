#include "Plane.h"

#include <Core/Engine.h>

Mesh* Plane::CreateBody(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-0.5f, 1.1f, 0.15f), normal, color),
		VertexFormat(glm::vec3(-0.5f, 1.1f, -0.15f), normal, color),
		VertexFormat(glm::vec3(-0.5f, 1.4f, 0.15f), normal, color),
		VertexFormat(glm::vec3(-0.5f, 1.4f, -0.15f), normal, color),
		VertexFormat(glm::vec3(0.5f, 1, 0.25f), normal, color),
		VertexFormat(glm::vec3(0.5f, 1, -0.25f), normal, color),
		VertexFormat(glm::vec3(0.5f, 1.5f, 0.25f), normal, color),
		VertexFormat(glm::vec3(0.5f, 1.5f, -0.25f), normal, color)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 2, 3,
		4, 5, 6,
		5, 6, 7,
		0, 1, 4,
		1, 4, 5,
		2, 3, 6,
		3, 6, 7,
		1, 5, 3,
		5, 3, 7,
		4, 0, 6,
		0, 6, 2
	};

	Mesh* body = new Mesh(name);

	body->InitFromData(vertices, indices);

	return body;
}

Mesh* Plane::CreateLeftWing(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-0.1f, 1.25f, 0.65f), normal, color),
		VertexFormat(glm::vec3(-0.1f, 1.25f, 0.15f), normal, color),
		VertexFormat(glm::vec3(0.1f, 1.25f, 0.15f), normal, color),
		VertexFormat(glm::vec3(0.1f, 1.25f, 0.65f), normal, color),
		VertexFormat(glm::vec3(-0.1f, 1.3f, 0.65f), normal, color),
		VertexFormat(glm::vec3(-0.1f, 1.3f, 0.15f), normal, color),
		VertexFormat(glm::vec3(0.1f, 1.3f, 0.15f), normal, color),
		VertexFormat(glm::vec3(0.1f, 1.3f, 0.65f), normal, color)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		0, 1, 5,
		5, 4, 0,
		3, 2, 6,
		6, 7, 3,
		1, 2, 6,
		6, 5, 1,
		0, 3, 7,
		7, 4, 0
	};

	Mesh* leftWing = new Mesh(name);

	leftWing->InitFromData(vertices, indices);

	return leftWing;
}

Mesh* Plane::CreateRightWing(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-0.1f, 1.25f, -0.15f), normal, color),
		VertexFormat(glm::vec3(-0.1f, 1.25f, -0.65f), normal, color),
		VertexFormat(glm::vec3(0.1f, 1.25f, -0.65f), normal, color),
		VertexFormat(glm::vec3(0.1f, 1.25f, -0.15f), normal, color),
		VertexFormat(glm::vec3(-0.1f, 1.3f, -0.15f), normal, color),
		VertexFormat(glm::vec3(-0.1f, 1.3f, -0.65f), normal, color),
		VertexFormat(glm::vec3(0.1f, 1.3f, -0.65f), normal, color),
		VertexFormat(glm::vec3(0.1f, 1.3f, -0.15f), normal, color)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		0, 1, 5,
		5, 4, 0,
		3, 2, 6,
		6, 7, 3,
		1, 2, 6,
		6, 5, 1,
		0, 3, 7,
		7, 4, 0
	};

	Mesh* rightWing = new Mesh(name);

	rightWing->InitFromData(vertices, indices);

	return rightWing;
}
Mesh* Plane::CreateTail(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-0.6f, 1.3f, 0.05f), normal, color),
		VertexFormat(glm::vec3(-0.6f, 1.3f, -0.05f), normal, color),
		VertexFormat(glm::vec3(-0.4f, 1.3f, -0.05f), normal, color),
		VertexFormat(glm::vec3(-0.4f, 1.3f, 0.05f), normal, color),
		VertexFormat(glm::vec3(-0.6f, 1.5f, 0.05f), normal, color),
		VertexFormat(glm::vec3(-0.6f, 1.5f, -0.05f), normal, color),
		VertexFormat(glm::vec3(-0.4f, 1.5f, -0.05f), normal, color),
		VertexFormat(glm::vec3(-0.4f, 1.5f, 0.05f), normal, color)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		0, 1, 5,
		5, 4, 0,
		3, 2, 6,
		6, 7, 3,
		1, 2, 6,
		6, 5, 1,
		0, 3, 7,
		7, 4, 0
	};

	Mesh* tail = new Mesh(name);

	tail->InitFromData(vertices, indices);

	return tail;
}

Mesh* Plane::CreateHead(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0.5f, 1, 0.25f), normal, color),
		VertexFormat(glm::vec3(0.5f, 1, -0.25f), normal, color),
		VertexFormat(glm::vec3(0.7f, 1, -0.25f), normal, color),
		VertexFormat(glm::vec3(0.7f, 1, 0.25f), normal, color),
		VertexFormat(glm::vec3(0.5f, 1.5f, 0.25f), normal, color),
		VertexFormat(glm::vec3(0.5f, 1.5f, -0.25f), normal, color),
		VertexFormat(glm::vec3(0.7f, 1.5f, -0.25f), normal, color),
		VertexFormat(glm::vec3(0.7f, 1.5f, 0.25f), normal, color)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		0, 1, 5,
		5, 4, 0,
		3, 2, 6,
		6, 7, 3,
		1, 2, 6,
		6, 5, 1,
		0, 3, 7,
		7, 4, 0
	};

	Mesh* head = new Mesh(name);

	head->InitFromData(vertices, indices);

	return head;
}

Mesh* Plane::CreatePropellerSupport(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0.7f, 1.2f, 0.05f), normal, color),
		VertexFormat(glm::vec3(0.7f, 1.2f, -0.05f), normal, color),
		VertexFormat(glm::vec3(0.8f, 1.2f, -0.05f), normal, color),
		VertexFormat(glm::vec3(0.8f, 1.2f, 0.05f), normal, color),
		VertexFormat(glm::vec3(0.7f, 1.3f, 0.05f), normal, color),
		VertexFormat(glm::vec3(0.7f, 1.3f, -0.05f), normal, color),
		VertexFormat(glm::vec3(0.8f, 1.3f, -0.05f), normal, color),
		VertexFormat(glm::vec3(0.8f, 1.3f, 0.05f), normal, color)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		0, 1, 5,
		5, 4, 0,
		3, 2, 6,
		6, 7, 3,
		1, 2, 6,
		6, 5, 1,
		0, 3, 7,
		7, 4, 0
	};

	Mesh* propellerSupport = new Mesh(name);

	propellerSupport->InitFromData(vertices, indices);

	return propellerSupport;
}

Mesh* Plane::CreatePropeller(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0.8f, 0.95f, 0.025f), normal, color),
		VertexFormat(glm::vec3(0.8f, 0.95f, -0.025f), normal, color),
		VertexFormat(glm::vec3(0.825f, 0.95f, -0.025f), normal, color),
		VertexFormat(glm::vec3(0.825f, 0.95f, 0.025f), normal, color),
		VertexFormat(glm::vec3(0.8f, 1.55f, 0.025f), normal, color),
		VertexFormat(glm::vec3(0.8f, 1.55f, -0.025f), normal, color),
		VertexFormat(glm::vec3(0.825f, 1.55f, -0.025f), normal, color),
		VertexFormat(glm::vec3(0.825f, 1.55f, 0.025f), normal, color)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		0, 1, 5,
		5, 4, 0,
		3, 2, 6,
		6, 7, 3,
		1, 2, 6,
		6, 5, 1,
		0, 3, 7,
		7, 4, 0
	};

	Mesh* propeller = new Mesh(name);

	propeller->InitFromData(vertices, indices);

	return propeller;
}

Mesh* Plane::CreatePilotBody(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-0.1f, 1.35f, 0.1f), normal, color),
		VertexFormat(glm::vec3(0.1f, 1.35f, 0.1f), normal, color),
		VertexFormat(glm::vec3(0.1f, 1.35f, -0.1f), normal, color),
		VertexFormat(glm::vec3(-0.1f, 1.35f, -0.1f), normal, color),
		VertexFormat(glm::vec3(-0.1f, 1.55f, 0.1f), normal, color),
		VertexFormat(glm::vec3(0.1f, 1.55f, 0.1f), normal, color),
		VertexFormat(glm::vec3(0.1f, 1.55f, -0.1f), normal, color),
		VertexFormat(glm::vec3(-0.1f, 1.55f, -0.1f), normal, color)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		0, 1, 5,
		5, 4, 0,
		3, 2, 6,
		6, 7, 3,
		1, 2, 6,
		6, 5, 1,
		0, 3, 7,
		7, 4, 0
	};

	Mesh* pilotBody = new Mesh(name);

	pilotBody->InitFromData(vertices, indices);

	return pilotBody;
}

Mesh* Plane::CreatePilotNeck(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-0.05f, 1.55f, 0.05f), normal, color),
		VertexFormat(glm::vec3(0.05f, 1.55f, 0.05f), normal, color),
		VertexFormat(glm::vec3(0.05f, 1.55f, -0.05f), normal, color),
		VertexFormat(glm::vec3(-0.05f, 1.55f, -0.05f), normal, color),
		VertexFormat(glm::vec3(-0.05f, 1.6f, 0.05f), normal, color),
		VertexFormat(glm::vec3(0.05f, 1.6f, 0.05f), normal, color),
		VertexFormat(glm::vec3(0.05f, 1.6f, -0.05f), normal, color),
		VertexFormat(glm::vec3(-0.05f, 1.6f, -0.05f), normal, color)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		0, 1, 5,
		5, 4, 0,
		3, 2, 6,
		6, 7, 3,
		1, 2, 6,
		6, 5, 1,
		0, 3, 7,
		7, 4, 0
	};

	Mesh* pilotNeck = new Mesh(name);

	pilotNeck->InitFromData(vertices, indices);

	return pilotNeck;
}

Mesh* Plane::CreatePilotHead(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-0.075f, 1.6f, 0.075f), normal, color),
		VertexFormat(glm::vec3(0.075f, 1.6f, 0.075f), normal, color),
		VertexFormat(glm::vec3(0.075f, 1.6f, -0.075f), normal, color),
		VertexFormat(glm::vec3(-0.075f, 1.6f, -0.075f), normal, color),
		VertexFormat(glm::vec3(-0.075f, 1.7f, 0.075f), normal, color),
		VertexFormat(glm::vec3(0.075f, 1.7f, 0.075f), normal, color),
		VertexFormat(glm::vec3(0.075f, 1.7f, -0.075f), normal, color),
		VertexFormat(glm::vec3(-0.075f, 1.7f, -0.075f), normal, color)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		0, 1, 5,
		5, 4, 0,
		3, 2, 6,
		6, 7, 3,
		1, 2, 6,
		6, 5, 1,
		0, 3, 7,
		7, 4, 0
	};

	Mesh* pilotHead = new Mesh(name);

	pilotHead->InitFromData(vertices, indices);

	return pilotHead;
}

Mesh* Plane::CreatePilotArm(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-0.025f, 1.4f, 0.15f), normal, color),
		VertexFormat(glm::vec3(0.025f, 1.4f, 0.15f), normal, color),
		VertexFormat(glm::vec3(0.125f, 1.4f, 0.15f), normal, color),
		VertexFormat(glm::vec3(0.125f, 1.4f, 0.1f), normal, color),
		VertexFormat(glm::vec3(0.025f, 1.4f, 0.1f), normal, color),
		VertexFormat(glm::vec3(-0.025f, 1.4f, 0.1f), normal, color),
		VertexFormat(glm::vec3(0.025f, 1.425f, 0.15f), normal, color),
		VertexFormat(glm::vec3(0.125f, 1.425f, 0.15f), normal, color),
		VertexFormat(glm::vec3(0.125f, 1.425f, 0.1f), normal, color),
		VertexFormat(glm::vec3(0.025f, 1.425f, 0.1f), normal, color),
		VertexFormat(glm::vec3(-0.025f, 1.475f, 0.15f), normal, color),
		VertexFormat(glm::vec3(0.025f, 1.475f, 0.15f), normal, color),
		VertexFormat(glm::vec3(0.025f, 1.475f, 0.1f), normal, color),
		VertexFormat(glm::vec3(-0.025f, 1.475f, 0.1f), normal, color)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 11,
		11, 10, 0,
		1, 4, 12,
		12, 11, 1,
		4, 5, 13,
		13, 12, 4,
		5, 0, 10,
		10, 13, 5,
		0, 1, 4,
		4, 5, 0,
		10, 11, 12,
		12, 13, 10,
		1, 2, 7,
		7, 6, 1,
		2, 3, 8,
		8, 7, 2,
		3, 4, 9,
		9, 8, 3,
		4, 1, 6,
		6, 9, 4,
		1, 2, 3,
		3, 4, 1,
		6, 7, 8,
		8, 9, 6
	};

	Mesh* pilotArm = new Mesh(name);

	pilotArm->InitFromData(vertices, indices);

	return pilotArm;
}

Mesh* Plane::CreatePilotHand(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0.125f, 1.4f, 0.15f), normal, color),
		VertexFormat(glm::vec3(0.15f, 1.4f, 0.15f), normal, color),
		VertexFormat(glm::vec3(0.15f, 1.4f, 0.1f), normal, color),
		VertexFormat(glm::vec3(0.125f, 1.4f, 0.1f), normal, color),
		VertexFormat(glm::vec3(0.125f, 1.425f, 0.15f), normal, color),
		VertexFormat(glm::vec3(0.15f, 1.425f, 0.15f), normal, color),
		VertexFormat(glm::vec3(0.15f, 1.425f, 0.1f), normal, color),
		VertexFormat(glm::vec3(0.125f, 1.425f, 0.1f), normal, color)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		0, 1, 5,
		5, 4, 0,
		3, 2, 6,
		6, 7, 3,
		1, 2, 6,
		6, 5, 1,
		0, 3, 7,
		7, 4, 0
	};

	Mesh* pilotHand = new Mesh(name);

	pilotHand->InitFromData(vertices, indices);

	return pilotHand;
}

Mesh* Plane::CreatePilotHair(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-0.1f, 1.6f, 0.08f), normal, color),
		VertexFormat(glm::vec3(0, 1.6f, 0.08f), normal, color),
		VertexFormat(glm::vec3(0, 1.6f, -0.08f), normal, color),
		VertexFormat(glm::vec3(-0.1f, 1.6f, -0.08f), normal, color),
		VertexFormat(glm::vec3(-0.1f, 1.69f, 0.08f), normal, color),
		VertexFormat(glm::vec3(0, 1.69f, 0.08f), normal, color),
		VertexFormat(glm::vec3(0, 1.69f, -0.08f), normal, color),
		VertexFormat(glm::vec3(-0.1f, 1.69f, -0.08f), normal, color),

		VertexFormat(glm::vec3(-0.15f, 1.69f, 0.08f), normal, color),
		VertexFormat(glm::vec3(0.09f, 1.69f, 0.08f), normal, color),
		VertexFormat(glm::vec3(0.09, 1.69f, -0.08f), normal, color),
		VertexFormat(glm::vec3(-0.15f, 1.69f, -0.08f), normal, color),
		VertexFormat(glm::vec3(-0.15f, 1.725f, 0.08f), normal, color),
		VertexFormat(glm::vec3(0.09f, 1.725f, 0.08f), normal, color),
		VertexFormat(glm::vec3(0.09f, 1.725f, -0.08f), normal, color),
		VertexFormat(glm::vec3(-0.15f, 1.725f, -0.08f), normal, color),

		VertexFormat(glm::vec3(-0.2f, 1.725f, 0.08f), normal, color),
		VertexFormat(glm::vec3(0.075f, 1.725f, 0.08f), normal, color),
		VertexFormat(glm::vec3(0.075, 1.725f, -0.08f), normal, color),
		VertexFormat(glm::vec3(-0.2f, 1.725f, -0.08f), normal, color),
		VertexFormat(glm::vec3(-0.2f, 1.75f, 0.08f), normal, color),
		VertexFormat(glm::vec3(0.075f, 1.75f, 0.08f), normal, color),
		VertexFormat(glm::vec3(0.075f, 1.75f, -0.08f), normal, color),
		VertexFormat(glm::vec3(-0.2f, 1.75f, -0.08f), normal, color),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		0, 1, 5,
		5, 4, 0,
		3, 2, 6,
		6, 7, 3,
		1, 2, 6,
		6, 5, 1,
		0, 3, 7,
		7, 4, 0,

		8, 9, 10,
		10, 11, 8,
		12, 13, 14,
		14, 15, 12,
		8, 9, 13,
		13, 12, 8,
		11, 10, 14,
		14, 15, 11,
		9, 10, 14,
		14, 13, 9,
		8, 11, 15,
		15, 12, 8,

		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20,
		16, 17, 21,
		21, 20, 16,
		19, 18, 22,
		22, 23, 19,
		17, 18, 22,
		22, 21, 17,
		16, 19, 23,
		23, 20, 16
	};

	Mesh* pilotHair = new Mesh(name);

	pilotHair->InitFromData(vertices, indices);

	return pilotHair;
}

Mesh* Plane::CreatePilotGlasses(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);
	glm::vec3 pink = glm::vec3(1, (float)222 / 255, (float)173 / 255);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0.075f, 1.62f, 0.075f), normal, color),
		VertexFormat(glm::vec3(0.115f, 1.62f, 0.075f), normal, color),
		VertexFormat(glm::vec3(0.115f, 1.62f, -0.075f), normal, color),
		VertexFormat(glm::vec3(0.075f, 1.62f, -0.075f), normal, color),
		VertexFormat(glm::vec3(0.075f, 1.66f, 0.075f), normal, color),
		VertexFormat(glm::vec3(0.115f, 1.66f, 0.075f), normal, color),
		VertexFormat(glm::vec3(0.115f, 1.66f, -0.075f), normal, color),
		VertexFormat(glm::vec3(0.075f, 1.66f, -0.075f), normal, color),

		VertexFormat(glm::vec3(0.075f, 1.625f, 0.07f), normal, pink),
		VertexFormat(glm::vec3(0.115f, 1.625f, 0.07f), normal, pink),
		VertexFormat(glm::vec3(0.115f, 1.625f, 0.005f), normal, pink),
		VertexFormat(glm::vec3(0.075f, 1.625f, 0.005f), normal, pink),
		VertexFormat(glm::vec3(0.075f, 1.655f, 0.07f), normal, pink),
		VertexFormat(glm::vec3(0.115f, 1.655f, 0.07f), normal, pink),
		VertexFormat(glm::vec3(0.115f, 1.655f, 0.005f), normal, pink),
		VertexFormat(glm::vec3(0.075f, 1.655f, 0.005f), normal, pink),

		VertexFormat(glm::vec3(0.075f, 1.625f, -0.005f), normal, pink),
		VertexFormat(glm::vec3(0.115f, 1.625f, -0.005f), normal, pink),
		VertexFormat(glm::vec3(0.115f, 1.625f, -0.07f), normal, pink),
		VertexFormat(glm::vec3(0.075f, 1.625f, -0.07f), normal, pink),
		VertexFormat(glm::vec3(0.075f, 1.655f, -0.005f), normal, pink),
		VertexFormat(glm::vec3(0.115f, 1.655f, -0.005f), normal, pink),
		VertexFormat(glm::vec3(0.115f, 1.655f, -0.07f), normal, pink),
		VertexFormat(glm::vec3(0.075f, 1.655f, -0.07f), normal, pink)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		0, 1, 5,
		5, 4, 0,
		3, 2, 6,
		6, 7, 3,
		1, 2, 6,
		6, 5, 1,
		0, 3, 7,
		7, 4, 0,

		8, 9, 10,
		10, 11, 8,
		12, 13, 14,
		14, 15, 12,
		8, 9, 13,
		13, 12, 8,
		11, 10, 14,
		14, 15, 11,
		9, 10, 14,
		14, 13, 9,
		8, 11, 15,
		15, 12, 8,

		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20,
		16, 17, 21,
		21, 20, 16,
		19, 18, 22,
		22, 23, 19,
		17, 18, 22,
		22, 21, 17,
		16, 19, 23,
		23, 20, 16
	};

	Mesh* pilotHead = new Mesh(name);

	pilotHead->InitFromData(vertices, indices);

	return pilotHead;
}