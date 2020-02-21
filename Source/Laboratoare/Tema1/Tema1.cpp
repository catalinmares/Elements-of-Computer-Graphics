#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2DBuilder.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 1);

	/* Calculate the number of obstacles we can spawn in scene */
	obstaclesInScene = resolution.x / (OBSTACLE_WIDTH + OBSTACLES_OFFSET);

	/* Initialize final score */
	finalScore = 0;
	scorePrinted = false;
	
	/* Scored vector is used for counting if an obstacle which we 
	   passed has already been counted in the score - 
	   initially, all obstacles are not scored (false) */
	for (int i = 0; i < obstaclesInScene; i++) {
		scored.push_back(false);
		signLower[i] = 1;
		signUpper[i] = 1;
	}

	/* Initializing translation steps ty */
	translateY = 0;

	/* Initializing translations tx for each obstacle */
	for (int i = 0; i < obstaclesInScene; i++) {
		obstacleTranslations[i] = 0;
	}

	/* Initializing angularStep */
	angularStep = 0;

	/* Calculating initial obstacle scales for Oy - 
	   the lower obstacles are scaled randomly while
	   the upper obstacles are scaled such way that the
	   distance between them and the lower ones is always the same*/
	for (int i = 0; i < obstaclesInScene; i++) {
		maxLowerObstaclesScales[i] = (float) (1 + rand() % 5);
		maxUpperObstaclesScales[i] = ((float)(resolution.y - 
								  OBSTACLE_WIDTH * maxLowerObstaclesScales[i] - 
								  OBSTACLES_DISTANCE)) / OBSTACLE_WIDTH;

		lowerObstaclesScales[i] = min(maxLowerObstaclesScales[i], maxUpperObstaclesScales[i]) / 2;
		upperObstaclesScales[i] = min(maxLowerObstaclesScales[i], maxUpperObstaclesScales[i]) / 2;
	}


	Mesh* bird = Object2DBuilder::CreateBird("bird");
	AddMeshToList(bird);

	Mesh* obstacle = Object2DBuilder::CreateSquare("obstacle", corner, OBSTACLE_WIDTH, true);
	AddMeshToList(obstacle);
}

void Tema1::FrameStart()
{
	/* Clears the color buffer (using the previously set color) and depth buffer */
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	/* Sets the screen area where to draw */
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	/* Place the bird in the middle on the scene on Oy
	   and move it from the margin of the scen on Ox */
	birdMatrix = Transform2D::Translate(300, (float) resolution.y / 2);
	birdMatrix *= Transform2D::Scale(1.5f, 1.5f);

	/* Initialize vectors of vertices for bird and obstacles */
	vector<VertexFormat> birdVertices = meshes["bird"]->vertices;
	vector<vector<VertexFormat>> upperObstaclesVertices;
	vector<vector<VertexFormat>> lowerObstaclesVertices;

	for (int i = 0; i < obstaclesInScene; i++) {
		upperObstaclesVertices.push_back(meshes["obstacle"]->vertices);
		lowerObstaclesVertices.push_back(meshes["obstacle"]->vertices);
	}

	/* Place the obstacles out of the scene on the
	   right by translation and scale them randomly */
	for (int i = 0; i < obstaclesInScene; i++) {

		lowerObstacleMatrix[i] = Transform2D::Translate((float) (resolution.x + 
														i * OBSTACLE_WIDTH + 
														i * OBSTACLES_OFFSET), 0);
		lowerObstacleMatrix[i] *= Transform2D::Scale(1, lowerObstaclesScales[i]);

		upperObstacleMatrix[i] = Transform2D::Translate((float) (resolution.x + 
			                                            i * OBSTACLE_WIDTH + 
														i * OBSTACLES_OFFSET),
														(float) (resolution.y - 
														OBSTACLE_WIDTH * upperObstaclesScales[i]));
		upperObstacleMatrix[i] *= Transform2D::Scale(1, upperObstaclesScales[i]);
	}

	/* Actions to do while the game is running */
	if (gameOn) {
		/* For each obstacle (upper and lower) increment 
		   the translation factors on Ox - make them move
		   towards the bird */
		for (int i = 0; i < obstaclesInScene; i++) {
			obstacleTranslations[i] += 200 * obstaclesSpeedOx * deltaTimeSeconds;

			/* If an obstacle has left the scene from the left side,
			   place it back on the right side to start over, resize
			   it randomly and the scored value to false (it will need
			   to be scored again, eventually) */
			if (obstacleTranslations[i] >= resolution.x + 
				(i + 1) * OBSTACLE_WIDTH + i * OBSTACLES_OFFSET) 
			{
				obstacleTranslations[i] = (float) (i * OBSTACLE_WIDTH + i * OBSTACLES_OFFSET);

				maxLowerObstaclesScales[i] = (float) (1 + rand() % 5);
				maxUpperObstaclesScales[i] = ((float)(resolution.y - 
										  OBSTACLE_WIDTH * maxLowerObstaclesScales[i] - 
										  OBSTACLES_DISTANCE)) / OBSTACLE_WIDTH;

				/* Initially, the obstacles are small; the distance between 
				   the upper and the lower obstacles will decrease in time */
				lowerObstaclesScales[i] = min(maxLowerObstaclesScales[i], maxUpperObstaclesScales[i]) / 2;
				upperObstaclesScales[i] = min(maxLowerObstaclesScales[i], maxUpperObstaclesScales[i]) / 2;

				scored[i] = false;
			}

			/* Update scale factor for upper obstacles */
			upperObstaclesScales[i] = upperObstaclesScales[i] + signUpper[i] * obstaclesSpeedOy * deltaTimeSeconds;

			if (upperObstaclesScales[i] >= maxUpperObstaclesScales[i]) {
				signUpper[i] = -1;
			}

			if (upperObstaclesScales[i] <= 1.f) {
				signUpper[i] = 1;
			}

			/* Update scale factor for lower obstacles */
			lowerObstaclesScales[i] += signLower[i] * obstaclesSpeedOy * deltaTimeSeconds;

			if (lowerObstaclesScales[i] >= maxLowerObstaclesScales[i]) {
				signLower[i] = -1;
			}

			if (lowerObstaclesScales[i] <= 1.f) {
				signLower[i] = 1;
			}

			/* Obstacles must keep a minimum distance between them */
			if (lowerObstaclesScales[i] * OBSTACLE_WIDTH + upperObstaclesScales[i] * OBSTACLE_WIDTH >= 
				resolution.y - OBSTACLES_DISTANCE) 
			{
				signUpper[i] = -1;
				signLower[i] = -1;
			}
		}

		/* If space was clicked, the bird needs to go up */
		if (birdDirection > 0) {
			/* Translate the bird higher */
			translateY += 5000 * deltaTimeSeconds;
			
			/* Make sure it doesn't rotate more than 30 degrees */
			if (angularStep < M_PI / 6) {
				angularStep += 25 * deltaTimeSeconds;
			}

			/* Bird needs to face down next, unless space is pressed again */
			birdDirection = -1;
		}
		/* Otherwise, the bird needs to go down */
		else {
			/* Translate the bird lower and slower */
			translateY -= 200 * deltaTimeSeconds;

			/* Make sure it doesn't rotate more than 30 degrees */
			if (angularStep > -M_PI / 6) {
				angularStep -= deltaTimeSeconds;
			}
		}

		/* Apply the 2 transformations to bird's model matrix */
		birdMatrix *= Transform2D::Translate(0, translateY);
		birdMatrix *= Transform2D::Rotate(angularStep);
	}

	/* Move the obstacles towards the bird */
	for (int i = 0; i < obstaclesInScene; i++) {
		lowerObstacleMatrix[i] *= Transform2D::Translate(-obstacleTranslations[i], 0);
		upperObstacleMatrix[i] *= Transform2D::Translate(-obstacleTranslations[i], 0);
	}

	/* Update bird vertices */
	for (int i = 0; i < birdVertices.size(); i++) {
		glm::vec3 aux = birdVertices[i].position;
		aux = glm::vec3(birdMatrix * aux);
		birdVertices[i].position = aux;
	}

	/* Update obstacle vertices */
	for (int i = 0; i < obstaclesInScene; i++) {
		vector<VertexFormat> upperObstacleVertices = upperObstaclesVertices[i];
		vector<VertexFormat> lowerObstacleVertices = lowerObstaclesVertices[i];

		for (int j = 0; j < upperObstacleVertices.size(); j++) {
			glm::vec3 aux = upperObstacleVertices[j].position;
			aux = glm::vec3(upperObstacleMatrix[i] * aux);
			upperObstacleVertices[j].position = aux;
		}

		upperObstaclesVertices[i] = upperObstacleVertices;

		for (int j = 0; j < lowerObstacleVertices.size(); j++) {
			glm::vec3 aux = lowerObstacleVertices[j].position;
			aux = glm::vec3(lowerObstacleMatrix[i] * aux);
			lowerObstacleVertices[j].position = aux;
		}

		lowerObstaclesVertices[i] = lowerObstacleVertices;
	}

	/* If the game is not over yet*/
	if (!gameOver && gameOn) {
		/* Check collision between bird and obstacles or if bird got out of map */
		if ((CheckCollision(birdVertices, upperObstaclesVertices, lowerObstaclesVertices) ||
			CheckOutOfMap(birdVertices, resolution.y)))
		{
			/* In this case, it's game over */
			cout << "GAME OVER!\nFinal score: " << finalScore << "\n";
			gameOn = false;
			gameOver = true;
		}

		/* Update the score */
		int updateScore = UpdateScore(birdVertices, lowerObstaclesVertices, scored);
		finalScore += updateScore;

		/* If score changed, we need to print it again */
		if (updateScore != 0) {
			scorePrinted = false;
		}

		/* Print the score only if it's not 0 and multiple of 5 */
		if (finalScore != 0 && finalScore % 10 == 0 && !scorePrinted) {
			cout << "Current score: " << finalScore << "\n";
			scorePrinted = true;

			/* Increase game difficulty after each 10 points */
			obstaclesSpeedOx += 0.5f;
			obstaclesSpeedOy += 0.25f;
		}
	}

	/* Finally render bird and obstacles meshes on the screen */
	RenderMesh2D(meshes["bird"], shaders["VertexColor"], birdMatrix);

	for (int i = 0; i < obstaclesInScene; i++) {
		RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], lowerObstacleMatrix[i]);
		RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], upperObstacleMatrix[i]);
	}

}

void Tema1::FrameEnd()
{

}

/* This function checks if a vertex of the bird is inside the rectangle of an obstacle */
bool Tema1::InRange(glm::vec3 birdVertex, vector<VertexFormat> obstacleVertices)
{
	glm::vec3 botLeft = obstacleVertices[0].position;
	glm::vec3 topRight = obstacleVertices[2].position;

	return (birdVertex.x >= botLeft.x && birdVertex.x <= topRight.x &&
		    birdVertex.y >= botLeft.y && birdVertex.y <= topRight.y);
}

/* This function iterates through all obstacles and for each one of them 
   checks if any vertex of the bird is inside it */
bool Tema1::CheckCollision(vector<VertexFormat> birdVertices, 
						   vector<vector<VertexFormat>> upperObstaclesVertices, 
						   vector<vector<VertexFormat>> lowerObstaclesVertices)
{	
	for (int i = 0; i < obstaclesInScene; i++) {
		vector<VertexFormat> upperObstacleVertices = upperObstaclesVertices[i];
		vector<VertexFormat> lowerObstacleVertices = lowerObstaclesVertices[i];

		for (int j = 0; j < birdVertices.size(); j++) {
			if (InRange(birdVertices[i].position, upperObstacleVertices) || 
				InRange(birdVertices[i].position, lowerObstacleVertices)) 
			{
				return true;
			}
		}
	}

	return false;
}

/* This function checks if any vertex of the bird is out of the map */
bool Tema1::CheckOutOfMap(std::vector<VertexFormat> birdVertices, int sceneHeight)
{
	for (int i = 0; i < birdVertices.size(); i++) {
		glm::vec3 birdVertex = birdVertices[i].position;

		if (birdVertex.y < 0 || birdVertex.y > sceneHeight) {
			return true;
		}
	}

	return false;
}

/* This function checks if the bird has passed an obstacle */
int Tema1::UpdateScore(vector<VertexFormat> birdVertices,
					   vector<vector<VertexFormat>> obstaclesVertices,
					   vector<bool>& scored)
{
	/* Extract the leftest vertex of the bird */
	glm::vec3 leftMarginBird = birdVertices[0].position;

	for (int i = 1; i < birdVertices.size(); i++) {
		glm::vec3 aux = birdVertices[i].position;

		if (aux.x < leftMarginBird.x) {
			leftMarginBird = aux;
		}
	}

	/* For each obstacle, extract the rightest vertex and check
	   if it's x value is lower than bird's leftest vertex x value - 
	   this means that the bird has passed that obstacle */
	for (int i = 0; i < obstaclesInScene; i++) {
		vector<VertexFormat> obstacleVertices = obstaclesVertices[i];
		glm::vec3 rightMarginObstacle = obstacleVertices[1].position;

		/* Very important is not to score the same passed obstacle twice - 
		   for this we use and update the scored vector */
		if (rightMarginObstacle.x < leftMarginBird.x && !scored[i]) {
			scored[i] = true;
			return 1;
		}
	}

	return 0;
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}

void Tema1::OnKeyPress(int key, int mods)
{
	/* If SPACE is pressed and it's not game over */
	if (key == GLFW_KEY_SPACE && !gameOver) {
		/* The birds needs to go up */
		birdDirection = 1;

		/* If this is the first SPACE key press, 
		   we need to start the game */
		if (!gameOn) {
			gameOn = true;
		}
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
