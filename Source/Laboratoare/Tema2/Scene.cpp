#include "Scene.h"

#include <Core/Engine.h>
#include <math.h>

Mesh* Scene::CreateSea(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	float r = 1.75f;
	short k = 0;
	short center;

	for (float len = -10; len < 10; len += 0.25f) {
		vertices.push_back(VertexFormat(glm::vec3(0, 0, len), normal, color));
		center = k++;

		for (int i = 0; i < 359; i += 2) {
			indices.push_back(center);

			vertices.push_back(VertexFormat(glm::vec3(r * cos(RADIANS(i)), r * sin(RADIANS(i)), len), normal, color));
			indices.push_back(k++);

			vertices.push_back(VertexFormat(glm::vec3(r * cos(RADIANS(i + 1)), r * sin(RADIANS(i + 1)), len), normal, color));
			indices.push_back(k++);

			indices.push_back(center);
		}
	}

	Mesh* sea = new Mesh(name);
	sea->InitFromData(vertices, indices);
	sea->SetDrawMode(GL_TRIANGLE_FAN);
	
	return sea;
}

Mesh* Scene::CreateCloud(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-0.1f, -0.1f, -0.1f), normal, color),
		VertexFormat(glm::vec3(0.1f, -0.1f, -0.1f), normal, color),
		VertexFormat(glm::vec3(0.1f, -0.1f, 0.1f), normal, color),
		VertexFormat(glm::vec3(-0.1f, -0.1f, 0.1f), normal, color),
		VertexFormat(glm::vec3(-0.1f, 0.1f, -0.1f), normal, color),
		VertexFormat(glm::vec3(0.1f, 0.1f, -0.1f), normal, color),
		VertexFormat(glm::vec3(0.1f, 0.1f, 0.1f), normal, color),
		VertexFormat(glm::vec3(-0.1f, 0.1f, 0.1f), normal, color)
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		0, 1, 5,
		5, 4, 0,
		1, 2, 6,
		6, 5, 1,
		2, 3, 7,
		7, 6, 2,
		3, 0, 4,
		4, 7, 3
	};

	Mesh* cloud = new Mesh(name);

	cloud->InitFromData(vertices, indices);

	return cloud;
}

Mesh* Scene::CreateLifeBack(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-4, 2, 0), normal, color),
		VertexFormat(glm::vec3(-1, 2, 0), normal, color),
		VertexFormat(glm::vec3(0, 5, 0), normal, color),
		VertexFormat(glm::vec3(1, 2, 0), normal, color),
		VertexFormat(glm::vec3(4, 2, 0), normal, color),
		VertexFormat(glm::vec3(2, 0, 0), normal, color),
		VertexFormat(glm::vec3(3, -3, 0), normal, color),
		VertexFormat(glm::vec3(0, -1, 0), normal, color),
		VertexFormat(glm::vec3(-3, -3, 0), normal, color),
		VertexFormat(glm::vec3(-2, 0, 0), normal, color)
	};

	std::vector<unsigned short> indices =
	{
		0, 4, 7,
		2, 6, 9,
		4, 8, 1,
		6, 0, 3
	};

	Mesh* life = new Mesh(name);

	life->InitFromData(vertices, indices);

	return life;
}

Mesh* Scene::CreateFuelMax(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), normal, color),
		VertexFormat(glm::vec3(1, 0, 0), normal, color),
		VertexFormat(glm::vec3(1, 0.25f, 0), normal, color),
		VertexFormat(glm::vec3(0, 0.25f, 0), normal, color),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 3, 0
	};

	Mesh* fuelMax = new Mesh(name);

	fuelMax->InitFromData(vertices, indices);

	return fuelMax;
}

Mesh* Scene::CreateFuelCurrent(std::string name, glm::vec3 color)
{
	glm::vec3 normal = glm::vec3(0, 1, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0.025f, 0.025f, 0.01f), normal, color),
		VertexFormat(glm::vec3(0.975f, 0.025f, 0.01f), normal, color),
		VertexFormat(glm::vec3(0.975f, 0.225f, 0.01f), normal, color),
		VertexFormat(glm::vec3(0.025f, 0.225f, 0.01f), normal, color),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		2, 3, 0
	};

	Mesh* fuelMax = new Mesh(name);

	fuelMax->InitFromData(vertices, indices);

	return fuelMax;
}