#include "Object2DBuilder.h"

#include <Core/Engine.h>

Mesh* Object2DBuilder::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, glm::vec3(0, 1, 0)),
		VertexFormat(corner + glm::vec3(length, 0, 0), glm::vec3(0, 0.25f, 0)),
		VertexFormat(corner + glm::vec3(length, length, 0), glm::vec3(0, 0.25f, 0)),
		VertexFormat(corner + glm::vec3(0, length, 0), glm::vec3(0, 1, 0))
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2DBuilder::CreateBird(std::string name)
{
	glm::vec3 yellow = glm::vec3(1, 1, 0);
	glm::vec3 light_yellow = glm::vec3(1, 1, 102 / 255);
	glm::vec3 orange = glm::vec3(1, 165 / 255, 0);
	glm::vec3 gray = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 black = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(7.5f, 10, 1), yellow),
		VertexFormat(glm::vec3(17.5f, 12.5f, 1), yellow),
		VertexFormat(glm::vec3(25, 7.5f, 1), yellow),
		VertexFormat(glm::vec3(41.25f, 7.5f, 1), light_yellow),
		VertexFormat(glm::vec3(47.5f, 12.5f, 1), orange),
		VertexFormat(glm::vec3(57.5f, 10, 1), yellow),
		VertexFormat(glm::vec3(67.5f, 5, 1), gray),
		VertexFormat(glm::vec3(60, 12.5f, 1), gray),
		VertexFormat(glm::vec3(62.5f, 17.5f, 1), yellow),
		VertexFormat(glm::vec3(50, 20, 1), light_yellow),
		VertexFormat(glm::vec3(57.5f, 35, 1), orange),
		VertexFormat(glm::vec3(42.5f, 25, 1), light_yellow),
		VertexFormat(glm::vec3(45, 45, 1), orange),
		VertexFormat(glm::vec3(30, 26.75f, 1), light_yellow),
		VertexFormat(glm::vec3(30, 17.5, 1), yellow),
		VertexFormat(glm::vec3(22.5f, 27.5f, 1), light_yellow),
		VertexFormat(glm::vec3(17.5f, 20, 1), yellow),
		VertexFormat(glm::vec3(12.5f, 22.5f, 1), orange),
		VertexFormat(glm::vec3(10, 17.5f, 1), orange),
		VertexFormat(glm::vec3(5, 17.5f, 1), yellow),
		VertexFormat(glm::vec3(42.5f, 12.5f, 1), orange),
		VertexFormat(glm::vec3(58.3f, 14.55f, 1), black),
		VertexFormat(glm::vec3(59.2f, 14.55f, 1), black),
		VertexFormat(glm::vec3(59.2f, 15.45f, 1), black),
		VertexFormat(glm::vec3(58.3f, 15.45f, 1), black)
	};

	Mesh* bird = new Mesh(name);

	std::vector<unsigned short> indices =
	{
		0, 1, 19,
		1, 14, 19,
		1, 2, 14,
		2, 20, 14,
		2, 3, 20,
		3, 4, 20,
		3, 5, 4,
		5, 6, 7,
		4, 5, 8,
		4, 8, 9,
		20, 4, 9,
		14, 20, 10,
		13, 11, 12,
		14, 11, 13,
		15, 14, 13,
		16, 14, 15,
		18, 14, 16,
		18, 16, 17,
		21, 22, 23,
		21, 23, 24
	};

	bird->InitFromData(vertices, indices);
	return bird;
}