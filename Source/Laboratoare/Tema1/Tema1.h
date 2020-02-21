#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <vector>
#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>
#include <include/glm.h>
#include <glm/gtx/string_cast.hpp>

#define MAX_OBSTACLES_IN_SCENE 8
#define OBSTACLE_WIDTH 100
#define OBSTACLES_OFFSET 300
#define OBSTACLES_DISTANCE 215

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	bool InRange(glm::vec3 birdVertex, std::vector<VertexFormat> obstacleVertices);

	bool CheckCollision(std::vector<VertexFormat> birdVertices,
						std::vector<std::vector<VertexFormat>> upperObstaclesVertices,
						std::vector<std::vector<VertexFormat>> lowerObstaclesVertices);

	bool CheckOutOfMap(std::vector<VertexFormat> birdVertices, int sceneHeight);

	int UpdateScore(std::vector<VertexFormat> birdVertices,
					std::vector<std::vector<VertexFormat>> obstaclesVertices,
					std::vector<bool>& scored);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	int obstaclesInScene;
	glm::mat3 birdMatrix;
	glm::mat3 lowerObstacleMatrix[MAX_OBSTACLES_IN_SCENE];
	glm::mat3 upperObstacleMatrix[MAX_OBSTACLES_IN_SCENE];

	int finalScore;
	bool scorePrinted;
	std::vector<bool> scored;

	float translateY;
	float obstacleTranslations[MAX_OBSTACLES_IN_SCENE];

	float angularStep;
	
	bool gameOn = false;
	bool gameOver = false;
	int birdDirection = -1;
	float g = 9.81f;

	float maxUpperObstaclesScales[MAX_OBSTACLES_IN_SCENE];
	float maxLowerObstaclesScales[MAX_OBSTACLES_IN_SCENE];

	float upperObstaclesScales[MAX_OBSTACLES_IN_SCENE];
	float lowerObstaclesScales[MAX_OBSTACLES_IN_SCENE];

	int signLower[MAX_OBSTACLES_IN_SCENE];
	int signUpper[MAX_OBSTACLES_IN_SCENE];

	float obstaclesSpeedOx = 1.f;
	float obstaclesSpeedOy = 1.f;
};
