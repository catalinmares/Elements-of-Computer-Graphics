#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh1 = new Mesh("box");
		mesh1->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh1->GetMeshID()] = mesh1;

		Mesh* mesh2 = new Mesh("teapot");
		mesh2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh2->GetMeshID()] = mesh2;

		Mesh* mesh3 = new Mesh("sphere");
		mesh3->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh3->GetMeshID()] = mesh3;

		Mesh* mesh4 = new Mesh("goku");
		mesh4->LoadMesh(RESOURCE_PATH::MODELS + "Characters/Goku", "goku-ssj-blue.obj");
		meshes[mesh4->GetMeshID()] = mesh4;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(colors2.r, colors2.g, colors2.b, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

	if (!strcmp(name, "goku")) {
		RenderMesh(meshes[name], positions, glm::vec3(8.0f));
	}
	else {
		RenderMesh(meshes[name], positions);
	}

}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
	if (window->KeyHold(GLFW_KEY_W)) {
		positions.z -= deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		positions.z += deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		positions.x -= deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		positions.x += deltaTime;
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		// do something
		colors2.r = (rand() % 100) * 0.01f;
		colors2.g = (rand() % 100) * 0.01f;
		colors2.b = (rand() % 100) * 0.01f;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	char* objs[3] = { "goku", "teapot", "sphere" };
	if (key == GLFW_KEY_L) {
		name =  objs[rand() % 3];
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
