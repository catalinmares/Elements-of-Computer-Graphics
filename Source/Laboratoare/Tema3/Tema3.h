#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <vector>
#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>
#include <include/glm.h>
#include <stb/stb_image.h>
#include "Camera.h"

class Tema3 : public SimpleScene
{
public:
	Tema3();
	~Tema3();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture = NULL);

	bool OutOfMap(glm::vec4 bullet);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	std::unordered_map<std::string, Texture2D*> mapTextures;
	unsigned char* heightPixels;
	int width;
	int height;
	int channels;
	int size;

	Cam::Camera* camera;
	bool cameraOnPlayer;
	glm::mat4 projectionMatrix;

	glm::vec3 position1, position2, position_aux;
	glm::vec3 forward1, forward2, forward_aux;
	glm::vec3 right1, right2, right_aux;
	glm::vec3 up1, up2, up_aux;

	glm::mat4 player1;
	glm::mat4 player2;
	int currentPlayer;

	float player1TranslationOX, player2TranslationOX;
	float player1RotationAngleOX, player2RotationAngleOX;
	float player1RotationAngleOY, player2RotationAngleOY;

	bool shotsFired;
	bool modified;

	glm::mat4 bullet1;
	glm::mat4 bullet2;

	glm::vec4 bullet1Position;
	glm::vec4 bullet2Position;

	glm::vec3 dir1, dir2;

	float bullet1TranslationOX;
	float bullet1TranslationOY;
	float bullet1TranslationOZ;
	float bullet1Gravity;

	float bullet2TranslationOX;
	float bullet2TranslationOY;
	float bullet2TranslationOZ;
	float bullet2Gravity;

	glm::vec3 light1Position;
	glm::vec3 light1Direction;

	glm::vec3 light2Position;
	glm::vec3 light2Direction;

	unsigned int materialShininess;
	float materialKd;
	float materialKs;
};
