#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <vector>
#include <Core/Engine.h>
#include <Core/GPU/Mesh.h>
#include <include/glm.h>
#include "Camera.h"

#define MAX_FUEL 100
#define MAX_CLOUDS_IN_SCENE 10
#define MAX_OBSTACLES_IN_SCENE 5
#define MAX_CANS_IN_SCENE 5
#define MAX_SMOKE_CLOUDS 4

class Tema2 : public SimpleScene
{
	public:
		Tema2();
		~Tema2();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1));
		bool PlaneCollided(std::vector<glm::vec4> planePositions, glm::vec4 objectCenter, float objectRay);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		Camera::Camera* camera;
		glm::mat4 projectionMatrix;
		bool firstPerson;

		glm::vec4 firstPersonCameraPosition;
		glm::vec4 firstPersonCameraForward;
		glm::vec4 firstPersonCameraUp;
		glm::vec4 firstPersonCameraRight;

		glm::mat4 body;
		glm::mat4 leftWing;
		glm::mat4 rightWing;
		glm::mat4 tail;
		glm::mat4 head;
		glm::mat4 propellerSupport;
		glm::mat4 propeller;
		glm::mat4 planeSmoke;

		glm::mat4 pilotBody;
		glm::mat4 pilotNeck;
		glm::mat4 pilotHead;
		glm::mat4 pilotArm;
		glm::mat4 pilotHand;
		glm::mat4 pilotHair;
		glm::mat4 pilotGlasses;

		glm::mat4 obstacle;
		glm::mat4 fuelCan;
		glm::mat4 fuelM;
		glm::mat4 life;
		glm::mat4 sea;
		glm::mat4 cloud;

		glm::mat4 powerUp;
		bool regainLifeInScene;
		bool immunityInScene;

		float powerUpTranslationX;
		float powerUpTranslationY;
		float powerUpTranslationZ;
		float powerUpRotationOZ;
		glm::vec4 powerUpCenter;

		bool freefall;
		bool planeImmune;
		double immunityStart;

		int cloudCount;
		float cloudTranslationX[MAX_CLOUDS_IN_SCENE];
		float cloudTranslationY[MAX_CLOUDS_IN_SCENE];
		float cloudTranslationZ[MAX_CLOUDS_IN_SCENE];
		float cloudRotationOZ[MAX_CLOUDS_IN_SCENE];

		int obstacleCount;
		float obstacleTranslationX[MAX_OBSTACLES_IN_SCENE];
		float obstacleTranslationY[MAX_OBSTACLES_IN_SCENE];
		float obstacleTranslationZ[MAX_OBSTACLES_IN_SCENE];
		float obstacleRotationOZ[MAX_OBSTACLES_IN_SCENE];
		bool obstacleInScene[MAX_OBSTACLES_IN_SCENE];
		bool obstacleReset[MAX_OBSTACLES_IN_SCENE];
		glm::vec4 obstacleCenter[MAX_OBSTACLES_IN_SCENE];

		int fuelCanCount;
		float fuelCanTranslationX[MAX_CANS_IN_SCENE];
		float fuelCanTranslationY[MAX_CANS_IN_SCENE];
		float fuelCanTranslationZ[MAX_CANS_IN_SCENE];
		float fuelCanRotationOZ[MAX_CANS_IN_SCENE];
		bool fuelCanInScene[MAX_CANS_IN_SCENE];
		bool fuelCanReset[MAX_CANS_IN_SCENE];
		glm::vec4 fuelCanCenter[MAX_CANS_IN_SCENE];
		float fuelCanRotationOY;

		int smokeCloudCount;
		float smokeCloudTranslation[MAX_SMOKE_CLOUDS];
		float smokeCloudScale[MAX_SMOKE_CLOUDS];
		bool smokeCloudInScene[MAX_SMOKE_CLOUDS];

		float planeTranslationOY;
		float planeTranslationOZ;
		float pilotHairScale;
		int sign;
		float planeSmokeScale;

		float planeAngleOZ;
		float planeAngleOY;

		float planeAcceleration;

		float propellerAngle;
		
		float seaAngle;

		int lives;
		float fuel;

		double elapsedTime1;
		double elapsedTime2;

		glm::vec3 lightPosition;
		glm::vec3 lightDirection;
		unsigned int materialShininess;
		float materialKd;
		float materialKs;

		// COLORS
		glm::vec3 red = glm::vec3(1, 0, 0);
		glm::vec3 green = glm::vec3(0, 1, 0);
		glm::vec3 orange = glm::vec3(1, (float)165 / 255, 0);
		glm::vec3 white = glm::vec3(1, 1, 1);
		glm::vec3 black = glm::vec3(0, 0, 0);
		glm::vec3 light_blue = glm::vec3(0, (float)191 / 255, 1);
		glm::vec3 brown = glm::vec3((float)139 / 255, (float)69 / 255, (float)19 / 255);
		glm::vec3 creme = glm::vec3(1, (float)222 / 255, (float)173 / 255);
		glm::vec3 pink = glm::vec3(1, (float)153 / 255, 1);
		glm::vec3 blue = glm::vec3((float)30 / 255, (float)144 / 255, 1);
		glm::vec3 yellow = glm::vec3(1, 1, 0);
		glm::vec3 grey = glm::vec3(0.6f, 0.6f, 0.6f);
};
