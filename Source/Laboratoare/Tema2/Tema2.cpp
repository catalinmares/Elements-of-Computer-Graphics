#include "Tema2.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Scene.h"
#include "Plane.h"
#include "Transform3D.h"

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	camera = new Camera::Camera();
	camera->Set(glm::vec3(0, 1.85f, 4), glm::vec3(0, 1.85f, 3), glm::vec3(0, 1, 0));

	firstPerson = false;

	// MESH INITIALIZATIONS
	{
		Mesh* body = Plane::CreateBody("PlaneBody", red);
		AddMeshToList(body);

		Mesh* leftWing = Plane::CreateLeftWing("PlaneLeftWing", orange);
		AddMeshToList(leftWing);

		Mesh* rightWing = Plane::CreateRightWing("PlaneRightWing", orange);
		AddMeshToList(rightWing);

		Mesh* tail = Plane::CreateTail("PlaneTail", orange);
		AddMeshToList(tail);

		Mesh* head = Plane::CreateHead("PlaneHead", white);
		AddMeshToList(head);

		Mesh* propellerSupport = Plane::CreatePropellerSupport("PlanePropellerSupport", black);
		AddMeshToList(propellerSupport);

		Mesh* propeller = Plane::CreatePropeller("PlanePropeller", black);
		AddMeshToList(propeller);

		Mesh* obstacle = new Mesh("Obstacle");
		obstacle->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		AddMeshToList(obstacle);

		Mesh* fuelMax = Scene::CreateFuelMax("FuelMax", black);
		AddMeshToList(fuelMax);

		Mesh* fuelCurrent = Scene::CreateFuelCurrent("FuelCurrent", white);
		AddMeshToList(fuelCurrent);

		Mesh* life = Scene::CreateLifeBack("Life", red);
		AddMeshToList(life);

		Mesh* sea = Scene::CreateSea("Sea", light_blue);
		AddMeshToList(sea);

		Mesh* cloud = new Mesh("Cloud");
		cloud->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		AddMeshToList(cloud);

		Mesh* fuelCan = new Mesh("FuelCan");
		fuelCan->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		AddMeshToList(fuelCan);

		Mesh* pilotBody = Plane::CreatePilotBody("PilotBody", brown);
		AddMeshToList(pilotBody);

		Mesh* pilotNeck = Plane::CreatePilotNeck("PilotNeck", creme);
		AddMeshToList(pilotNeck);

		Mesh* pilotHead = Plane::CreatePilotHead("PilotHead", creme);
		AddMeshToList(pilotHead);

		Mesh* pilotArm = Plane::CreatePilotArm("PilotArm", brown);
		AddMeshToList(pilotArm);

		Mesh* pilotHand = Plane::CreatePilotHand("PilotHand", creme);
		AddMeshToList(pilotHand);

		Mesh* pilotHair = Plane::CreatePilotHair("PilotHair", brown);
		AddMeshToList(pilotHair);

		Mesh* pilotGlasses = Plane::CreatePilotGlasses("PilotGlasses", brown);
		AddMeshToList(pilotGlasses);
	}

	// Plane Translations
	planeTranslationOY = 1.75f;
	planeTranslationOZ = 0;

	// Plane Rotations
	planeAngleOY = 0;
	planeAngleOZ = 0;

	// Plane Propeller Rotation Angle
	propellerAngle = 0;

	// Plane Acceleration
	planeAcceleration = 1;

	pilotHairScale = 1;
	sign = 1;
	planeSmokeScale = 0;

	// Initially plane won't freefall until the player loses the game
	freefall = false;
	planeImmune = false;

	// Sea Rotation Angle
	seaAngle = 0;

	// Player lives and plane fuel
	lives = 3;
	fuel = MAX_FUEL;

	// Starting time - used for object generation in time
	elapsedTime1 = Engine::GetElapsedTime();
	elapsedTime2 = Engine::GetElapsedTime();
	
	// Initialize cloud transformations
	cloudCount = 0;

	for (int i = 0; i < MAX_CLOUDS_IN_SCENE; i++) {
		cloudTranslationX[i] = 0;
		cloudTranslationY[i] = (float) (-3 - (rand() % 10));
		cloudTranslationZ[i] = (float) pow(-1, rand() % 2) * 4;

		cloudRotationOZ[i] = 0;
	}

	// Initialize obstacle transformations
	obstacleCount = 0;

	for (int i = 0; i < MAX_OBSTACLES_IN_SCENE; i++) {
		obstacleInScene[i] = false;
		obstacleReset[i] = false;
	}

	fuelCanTranslationX[0] = 0;
	fuelCanTranslationY[0] = (float)(-3 - (rand() % 2));
	fuelCanTranslationZ[0] = (float)pow(-1, rand() % 2) * (rand() % 3);
	fuelCanRotationOZ[0] = 0;
	fuelCanInScene[0] = true;

	for (int i = 1; i < MAX_CANS_IN_SCENE; i++) {
		fuelCanTranslationX[i] = fuelCanTranslationX[i - 1] + 0.25f;
		fuelCanTranslationY[i] = fuelCanTranslationY[i - 1] + 0.25f * pow(-1, i);
		fuelCanTranslationZ[i] = fuelCanTranslationZ[i - 1];

		fuelCanRotationOZ[i] = 0;

		fuelCanInScene[i] = true;
	}

	fuelCanRotationOY = 0;

	// Initialize smoke cloud transformations
	smokeCloudCount = 0;

	for (int i = 0; i < MAX_SMOKE_CLOUDS; i++) {
		smokeCloudInScene[i] = false;
	}

	regainLifeInScene = false;
	immunityInScene = false;
	
	// Set projection matrix
	projectionMatrix = glm::perspective(RADIANS(90), window->props.aspectRatio, 0.1f, 100.f);

	// COLOR SHADER
	{
		Shader* shader = new Shader("ColorShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/ColorVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/ColorFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// SEA SHADER
	{
		Shader* shader = new Shader("SeaShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/SeaVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/SeaFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Tema2::FrameStart()
{

}

void Tema2::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(pink.r, pink.g, pink.b, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// Initialize plane positions vector;
	vector<glm::vec4> planePositions;

	// Initialize first person camera data
	firstPersonCameraPosition = glm::vec4(0.3f, 1.75f, 0, 1);
	firstPersonCameraForward = glm::vec4(1, 0, 0, 1);
	firstPersonCameraUp = glm::vec4(0, 1, 0, 1);
	firstPersonCameraRight = glm::vec4(0, 0, 1, 1);

	// Get current time
	double newElapsedTime = Engine::GetElapsedTime();

	if (planeImmune && newElapsedTime - immunityStart >= 10) {
		planeImmune = false;
	}

	// Generate new objects in time
	if (newElapsedTime - elapsedTime1 >= 2) {
		elapsedTime1 = newElapsedTime;
		// Increase cloud count
		if (cloudCount < MAX_CLOUDS_IN_SCENE) {
			cloudCount++;
		}

		// Generate new obstacle randomly
		if (obstacleCount < MAX_OBSTACLES_IN_SCENE) {
			for (int i = 0; i < MAX_OBSTACLES_IN_SCENE; i++) {
				if (!obstacleInScene[i]) {
					obstacleTranslationX[i] = 0;
					obstacleTranslationY[i] = (float) (-3 - (rand() % 2));
					obstacleTranslationZ[i] = (float) pow(-1, rand() % 2) * (rand() % 3);

					obstacleRotationOZ[i] = 0;

					obstacleInScene[i] = true;

					break;
				}
			}

			obstacleCount++;
		}

		// Generate new plane smoke cloud
		if (smokeCloudCount < MAX_SMOKE_CLOUDS) {
			for (int i = 0; i < MAX_SMOKE_CLOUDS; i++) {
				if (!smokeCloudInScene[i]) {
					smokeCloudTranslation[i] = smokeCloudCount * 0.25f;
					smokeCloudScale[i] = 0;

					smokeCloudInScene[i] = true;

					break;
				}
			}

			smokeCloudCount++;
		}
	}

	if (newElapsedTime - elapsedTime2 >= 30) {
		elapsedTime2 = newElapsedTime;

		if (!regainLifeInScene && !immunityInScene) {
			int random = rand() % 2;

			if (random == 0) {
				regainLifeInScene = true;
			}
			else {
				immunityInScene = true;
			}

			powerUpTranslationX = 0;
			powerUpTranslationY = (float)(-3 - (rand() % 2));
			powerUpTranslationZ = (float)pow(-1, rand() % 2) * (rand() % 3);
			powerUpRotationOZ = 0;
		}
	}

	// If plane is moving
	if (lives > 0 || freefall) {
		// If plane went up, the rotation angle must decrease in time
		if (planeAngleOZ > 0) {
			planeAngleOZ -= 0.25f * deltaTimeSeconds;
		}

		// If plane went down, the rotation angle must increase in time
		if (planeAngleOZ < 0) {
			planeAngleOZ += 0.25f * deltaTimeSeconds;
		}

		// Plane must slow down without acceleration impulse
		if (planeAcceleration > 1) {
			planeAcceleration -= 0.02f;
		}

		// If plane went left, the rotation angle must decrease in time
		if (planeAngleOY > 0) {
			planeAngleOY -= 0.25f * deltaTimeSeconds;
		}
		
		// If plane went right, the rotation angle must increase in time
		if (planeAngleOY < 0) {
			planeAngleOY += 0.25f * deltaTimeSeconds;
		}

		// Update pilot hair scale
		pilotHairScale = (float) (pilotHairScale + sign * 0.25 * planeAcceleration * deltaTimeSeconds);

		if (pilotHairScale > 1.5f || pilotHairScale < 1) {
			sign *= -1;
		}

		// A running plane consumes fuel in time
		if (fuel > 0) {
			fuel -= 0.5f * planeAcceleration * deltaTimeSeconds;
		}

		// If out of fuel lose 1 life and regain half fuel
		if (fuel <= 0) {
			lives--;

			// If out of lives, plane will freefall
			if (lives == 0) {
				freefall = true;
			}
			else {
				fuel = 50;
			}
		}

		// If plane is on freefall
		if (freefall) {
			// Decrease translation on OY axis
			planeTranslationOY -= 0.75f * deltaTimeSeconds;

			// Rotate plane facing the sea
			planeAngleOZ -= 1.25f * deltaTimeSeconds;

			// Max rotation angle is 90 degrees
			if (planeAngleOZ < -M_PI / 2) {
				planeAngleOZ = (float) -M_PI / 2;
			}

			// If plane is in the sea, it must remain there
			if (planeTranslationOY <= 0) {
				planeAcceleration = 0;
				planeTranslationOY = 0;
			}
		}

		// PILOT RENDERING
		{
			pilotBody = Transform3D::Translate(0, planeTranslationOY, planeTranslationOZ);
			pilotBody *= Transform3D::RotateOZ(planeAngleOZ);
			pilotBody *= Transform3D::RotateOY(planeAngleOY);

			for (VertexFormat pilotBodyVertex : meshes["PilotBody"]->vertices) {
				glm::vec3 position = pilotBodyVertex.position;
				planePositions.push_back(pilotBody * glm::vec4(position, 1));
			}

			RenderMesh(meshes["PilotBody"], shaders["VertexNormal"], pilotBody);

			pilotNeck = Transform3D::Translate(0, planeTranslationOY, planeTranslationOZ);
			pilotNeck *= Transform3D::RotateOZ(planeAngleOZ);
			pilotNeck *= Transform3D::RotateOY(planeAngleOY);

			for (VertexFormat pilotNeckVertex : meshes["PilotNeck"]->vertices) {
				glm::vec3 position = pilotNeckVertex.position;
				planePositions.push_back(pilotNeck * glm::vec4(position, 1));
			}

			RenderMesh(meshes["PilotNeck"], shaders["VertexNormal"], pilotNeck);

			pilotHead = Transform3D::Translate(0, planeTranslationOY, planeTranslationOZ);
			pilotHead *= Transform3D::RotateOZ(planeAngleOZ);
			pilotHead *= Transform3D::RotateOY(planeAngleOY);

			for (VertexFormat pilotHeadVertex : meshes["PilotHead"]->vertices) {
				glm::vec3 position = pilotHeadVertex.position;
				planePositions.push_back(pilotHead * glm::vec4(position, 1));
			}

			RenderMesh(meshes["PilotHead"], shaders["VertexNormal"], pilotHead);

			pilotArm = Transform3D::Translate(0, planeTranslationOY, planeTranslationOZ);
			pilotArm *= Transform3D::RotateOZ(planeAngleOZ);
			pilotArm *= Transform3D::RotateOY(planeAngleOY);

			for (VertexFormat pilotArmVertex : meshes["PilotArm"]->vertices) {
				glm::vec3 position = pilotArmVertex.position;
				planePositions.push_back(pilotArm * glm::vec4(position, 1));
			}

			RenderMesh(meshes["PilotArm"], shaders["VertexNormal"], pilotArm);

			pilotArm *= Transform3D::Translate(0, 0, -0.2f);

			RenderMesh(meshes["PilotArm"], shaders["VertexNormal"], pilotArm);

			pilotHand = Transform3D::Translate(0, planeTranslationOY, planeTranslationOZ);
			pilotHand *= Transform3D::RotateOZ(planeAngleOZ);
			pilotHand *= Transform3D::RotateOY(planeAngleOY);

			for (VertexFormat pilotHandVertex : meshes["PilotHand"]->vertices) {
				glm::vec3 position = pilotHandVertex.position;
				planePositions.push_back(pilotHand * glm::vec4(position, 1));
			}

			RenderMesh(meshes["PilotHand"], shaders["VertexNormal"], pilotHand);

			pilotHand *= Transform3D::Translate(0, 0, -0.2f);

			RenderMesh(meshes["PilotHand"], shaders["VertexNormal"], pilotHand);

			pilotHair = Transform3D::Translate(0, planeTranslationOY, planeTranslationOZ);
			pilotHair *= Transform3D::RotateOZ(planeAngleOZ);
			pilotHair *= Transform3D::RotateOY(planeAngleOY);
			pilotHair *= Transform3D::Scale(pilotHairScale, 1, 1);

			for (VertexFormat pilotHairVertex : meshes["PilotHair"]->vertices) {
				glm::vec3 position = pilotHairVertex.position;
				planePositions.push_back(pilotHair * glm::vec4(position, 1));
			}

			RenderMesh(meshes["PilotHair"], shaders["VertexNormal"], pilotHair);

			pilotGlasses = Transform3D::Translate(0, planeTranslationOY, planeTranslationOZ);
			pilotGlasses *= Transform3D::RotateOZ(planeAngleOZ);
			pilotGlasses *= Transform3D::RotateOY(planeAngleOY);

			for (VertexFormat pilotGlassesVertex : meshes["PilotGlasses"]->vertices) {
				glm::vec3 position = pilotGlassesVertex.position;
				planePositions.push_back(pilotGlasses * glm::vec4(position, 1));
			}

			RenderMesh(meshes["PilotGlasses"], shaders["VertexNormal"], pilotGlasses);
		}

		// PLANE RENDERING
		{
			body = Transform3D::Translate(0, planeTranslationOY, planeTranslationOZ);

			// Move first person camera along with the plane
			firstPersonCameraPosition = body * firstPersonCameraPosition;

			body *= Transform3D::RotateOZ(planeAngleOZ);
			body *= Transform3D::RotateOY(planeAngleOY);

			for (VertexFormat bodyVertex : meshes["PlaneBody"]->vertices) {
				glm::vec3 position = bodyVertex.position;
				planePositions.push_back(body * glm::vec4(position, 1));
			}

			RenderMesh(meshes["PlaneBody"], shaders["VertexNormal"], body);

			leftWing = Transform3D::Translate(0, planeTranslationOY, planeTranslationOZ);
			leftWing *= Transform3D::RotateOZ(planeAngleOZ);
			leftWing *= Transform3D::RotateOY(planeAngleOY);

			for (VertexFormat leftWingVertex : meshes["PlaneLeftWing"]->vertices) {
				glm::vec3 position = leftWingVertex.position;
				planePositions.push_back(leftWing * glm::vec4(position, 1));
			}

			RenderMesh(meshes["PlaneLeftWing"], shaders["VertexNormal"], leftWing);

			rightWing = Transform3D::Translate(0, planeTranslationOY, planeTranslationOZ);
			rightWing *= Transform3D::RotateOZ(planeAngleOZ);
			rightWing *= Transform3D::RotateOY(planeAngleOY);

			for (VertexFormat rightWingVertex : meshes["PlaneRightWing"]->vertices) {
				glm::vec3 position = rightWingVertex.position;
				planePositions.push_back(rightWing * glm::vec4(position, 1));
			}

			RenderMesh(meshes["PlaneRightWing"], shaders["VertexNormal"], rightWing);

			tail = Transform3D::Translate(0, planeTranslationOY, planeTranslationOZ);
			tail *= Transform3D::RotateOZ(planeAngleOZ);
			tail *= Transform3D::RotateOY(planeAngleOY);

			for (VertexFormat tailVertex : meshes["PlaneTail"]->vertices) {
				glm::vec3 position = tailVertex.position;
				planePositions.push_back(tail * glm::vec4(position, 1));
			}

			RenderMesh(meshes["PlaneTail"], shaders["VertexNormal"], tail);

			head = Transform3D::Translate(0, planeTranslationOY, planeTranslationOZ);
			head *= Transform3D::RotateOZ(planeAngleOZ);
			head *= Transform3D::RotateOY(planeAngleOY);

			for (VertexFormat headVertex : meshes["PlaneHead"]->vertices) {
				glm::vec3 position = headVertex.position;
				planePositions.push_back(head * glm::vec4(position, 1));
			}

			RenderMesh(meshes["PlaneHead"], shaders["VertexNormal"], head);

			propellerSupport = Transform3D::Translate(0, planeTranslationOY, planeTranslationOZ);
			propellerSupport *= Transform3D::RotateOZ(planeAngleOZ);
			propellerSupport *= Transform3D::RotateOY(planeAngleOY);

			for (VertexFormat propellerSupportVertex : meshes["PlanePropellerSupport"]->vertices) {
				glm::vec3 position = propellerSupportVertex.position;
				planePositions.push_back(propellerSupport * glm::vec4(position, 1));
			}

			RenderMesh(meshes["PlanePropellerSupport"], shaders["VertexNormal"], propellerSupport);

			propellerAngle += 10 * planeAcceleration * deltaTimeSeconds;

			propeller = Transform3D::Translate(0, planeTranslationOY, planeTranslationOZ);
			propeller *= Transform3D::RotateOZ(planeAngleOZ);
			propeller *= Transform3D::RotateOY(planeAngleOY);
			propeller *= Transform3D::Translate(0.825f, 1.25f, 0);
			propeller *= Transform3D::RotateOX(propellerAngle);
			propeller *= Transform3D::Translate(-0.825f, -1.25f, 0);

			for (VertexFormat propellerVertex : meshes["PlanePropeller"]->vertices) {
				glm::vec3 position = propellerVertex.position;
				planePositions.push_back(propeller * glm::vec4(position, 1));
			}

			RenderMesh(meshes["PlanePropeller"], shaders["VertexNormal"], propeller);

			// Update plane smoke clouds scale and translation factors in time
			for (int i = 0; i < MAX_SMOKE_CLOUDS; i++) {
				if (smokeCloudInScene[i]) {
					smokeCloudTranslation[i] += (float) 0.5 * deltaTimeSeconds;

					if (smokeCloudTranslation[i] > 1.5f) {
						smokeCloudTranslation[i] = 0;
						smokeCloudScale[i] = 0;
					}

					if (planeAcceleration > 1) {
						smokeCloudScale[i] += (float) 0.75 * deltaTimeSeconds;

						if (smokeCloudScale[i] >= 1.5f) {
							smokeCloudScale[i] = 1.5f;
						}
					}
					else {
						smokeCloudScale[i] -= deltaTimeSeconds;

						if (smokeCloudScale[i] <= 0) {
							smokeCloudScale[i] = 0;
						}
					}

					planeSmoke = Transform3D::Translate(0, planeTranslationOY, planeTranslationOZ);
					planeSmoke *= Transform3D::RotateOZ(planeAngleOZ);
					planeSmoke *= Transform3D::RotateOY(planeAngleOY);
					planeSmoke *= Transform3D::Translate(-0.5f, 1.2f, 0);
					planeSmoke *= Transform3D::Scale((float)1 / 8, (float)1 / 8, (float)1 / 8);
					planeSmoke *= Transform3D::Scale(smokeCloudScale[i], smokeCloudScale[i], smokeCloudScale[i]);
					planeSmoke *= Transform3D::Translate(-smokeCloudTranslation[i], 0, 0);

					RenderSimpleMesh(meshes["Cloud"], shaders["ColorShader"], planeSmoke, glm::vec3(0.6f, 0.6f, 0.6f));
				}
			}
		}
	}

	// SEA RENDERING
	{
		sea = Transform3D::RotateOZ(seaAngle);

		RenderSimpleMesh(meshes["Sea"], shaders["SeaShader"], sea, light_blue);
	}

	// POWERUP RENDERING
	if (regainLifeInScene || immunityInScene) {
		powerUpRotationOZ += 0.25f * planeAcceleration * deltaTimeSeconds;

		powerUp = Transform3D::RotateOZ(powerUpRotationOZ);
		powerUp *= Transform3D::Translate(powerUpTranslationX, powerUpTranslationY, powerUpTranslationZ);
		powerUp *= Transform3D::RotateOZ(powerUpRotationOZ);
		powerUp *= Transform3D::Scale(0.25f, 0.25f, 0.25f);

		powerUpCenter = powerUp * glm::vec4(0, 0, 0, 1);

		if (regainLifeInScene) {
			RenderSimpleMesh(meshes["Obstacle"], shaders["ColorShader"], powerUp, yellow);
		}
		else {
			RenderSimpleMesh(meshes["Obstacle"], shaders["ColorShader"], powerUp, green);
		}
	}

	// OBSTACLE RENDERING
	for (int i = 0; i < MAX_OBSTACLES_IN_SCENE; i++) {
		if (obstacleInScene[i]) {
			obstacleRotationOZ[i] += 0.25f * planeAcceleration * deltaTimeSeconds;
			
			obstacle = Transform3D::RotateOZ(obstacleRotationOZ[i]);
			obstacle *= Transform3D::Translate(obstacleTranslationX[i], obstacleTranslationY[i], obstacleTranslationZ[i]);
			obstacle *= Transform3D::RotateOZ(obstacleRotationOZ[i]);
			obstacle *= Transform3D::Scale(0.5f, 0.5f, 0.5f);

			// Update obstacle center position - used for collision detection
			obstacleCenter[i] = obstacle * glm::vec4(0, 0, 0, 1);

			if (obstacleCenter[i].y > 0) {
				obstacleReset[i] = false;
			}

			// Each obstacle will generate new model transformations randomly when is out of the screen
			if (obstacleCenter[i].y < 0 && obstacleCenter[i].x > -1 && obstacleCenter[i].x < 1) {
				if (!obstacleReset[i]) {
					obstacleReset[i] = true;

					obstacleTranslationX[i] = 0;
					obstacleTranslationY[i] = (float) (-3 - (rand() % 2));
					obstacleTranslationZ[i] = (float) pow(-1, rand() % 2) * (rand() % 3);

					obstacleRotationOZ[i] = 0;
				}
			}

			RenderSimpleMesh(meshes["Obstacle"], shaders["ColorShader"], obstacle, red);
		}
	}

	// FUEL CAN RENDERING
	for (int i = 0; i < MAX_CANS_IN_SCENE; i++) {
		fuelCanRotationOZ[i] += 0.25f * planeAcceleration * deltaTimeSeconds;

		fuelCanRotationOY += 0.5f * deltaTimeSeconds;

		fuelCan = Transform3D::RotateOZ(fuelCanRotationOZ[i]);
		fuelCan *= Transform3D::Translate(fuelCanTranslationX[i], fuelCanTranslationY[i], fuelCanTranslationZ[i]);
		fuelCan *= Transform3D::RotateOY(fuelCanRotationOY);
		fuelCan *= Transform3D::Scale(0.25f, -0.25f, 0.25f);

		// Update fuel can center position - used for collision detection
		fuelCanCenter[i] = fuelCan * glm::vec4(0, 0, 0, 1);

		if (fuelCanInScene[i]) {
			RenderSimpleMesh(meshes["FuelCan"], shaders["ColorShader"], fuelCan, blue);
		}
	}

	if (fuelCanCenter[0].y < 0 && fuelCanCenter[0].x > -1 && fuelCanCenter[0].x < 1) {
		for (int i = 0; i < MAX_CANS_IN_SCENE; i++) {
			if (i == 0) {
				fuelCanTranslationX[i] = 0;
				fuelCanTranslationY[i] = (float)(-3 - (rand() % 2));
				fuelCanTranslationZ[i] = (float)pow(-1, rand() % 2) * (rand() % 3);
			}
			else {
				fuelCanTranslationX[i] = fuelCanTranslationX[i - 1] + 0.25f;
				fuelCanTranslationY[i] = fuelCanTranslationY[i - 1] + 0.25f * pow(-1, i);
				fuelCanTranslationZ[i] = fuelCanTranslationZ[i - 1];
			}

			fuelCanInScene[i] = true;
		}
	}

	// CLOUD RENDERING
	for (int i = 0; i < cloudCount; i++) {
		cloudRotationOZ[i] += 0.25f * planeAcceleration * deltaTimeSeconds;

		cloud = Transform3D::RotateOZ(cloudRotationOZ[i]);
		cloud *= Transform3D::Translate(cloudTranslationX[i], cloudTranslationY[i], cloudTranslationZ[i]);
		cloud *= Transform3D::Scale(0.8f, 0.8f, 0.8f);

		RenderSimpleMesh(meshes["Cloud"], shaders["ColorShader"], cloud, white);

		cloud = Transform3D::RotateOZ(cloudRotationOZ[i]);
		cloud *= Transform3D::Translate(cloudTranslationX[i] - 0.5f, cloudTranslationY[i] -0.25f, cloudTranslationZ[i]);
		cloud *= Transform3D::Scale(0.8f, 0.8f, 0.8f);

		RenderSimpleMesh(meshes["Cloud"], shaders["ColorShader"], cloud, white);

		cloud = Transform3D::RotateOZ(cloudRotationOZ[i]);
		cloud *= Transform3D::Translate(cloudTranslationX[i] - 1.f, cloudTranslationY[i], cloudTranslationZ[i]);
		cloud *= Transform3D::Scale(0.8f, 0.8f, 0.8f);

		RenderSimpleMesh(meshes["Cloud"], shaders["ColorShader"], cloud, white);

		cloud = Transform3D::RotateOZ(cloudRotationOZ[i]);
		cloud *= Transform3D::Translate(cloudTranslationX[i] - 1.5f, cloudTranslationY[i] - 0.25f, cloudTranslationZ[i]);
		cloud *= Transform3D::Scale(0.8f, 0.8f, 0.8f);

		RenderSimpleMesh(meshes["Cloud"], shaders["ColorShader"], cloud, white);
	}

	// LIFE RENDERING
	life = glm::mat4(1);
	
	// First person camera on screen positioning
	if (firstPerson) {
		life *= Transform3D::RotateOY(-RADIANS(90));
		life *= Transform3D::Translate(firstPersonCameraPosition.z - 12, 
									   firstPersonCameraPosition.y + 6, 
									   firstPersonCameraPosition.x - 7.75f);
	}
	else {
		life *= Transform3D::Translate(-3.3f, 3.5f, 2);
	}

	// Render each life at a time
	for (int i = 0; i < lives; i++) {
		if (i == 0) {
			if (firstPerson) {
				life *= Transform3D::Scale((float)1 / 10, (float)1 / 10, 1);
			}
			else {
				life *= Transform3D::Scale((float)1 / 32, (float)1 / 32, 1);
			}
		}
		else {
			life *= Transform3D::Translate(10, 0, 0);
		}

		RenderMesh(meshes["Life"], shaders["VertexNormal"], life);
	}

	// FUEL RENDERING
	{
		fuelM = glm::mat4(1);

		if (firstPerson) {
			fuelM *= Transform3D::RotateOY(-RADIANS(90));
			fuelM *= Transform3D::Translate(firstPersonCameraPosition.z + 9.25f, 
											firstPersonCameraPosition.y + 5.75f,
											firstPersonCameraPosition.x - 7.75f);

			fuelM *= Transform3D::Scale(3, 3, 1);
		}
		else {
			fuelM *= Transform3D::Translate(2.5f, 3.4f, 2);
		}

		RenderMesh(meshes["FuelMax"], shaders["VertexNormal"], fuelM);

		float fuelScale = fuel / MAX_FUEL;

		fuelM *= Transform3D::Scale(fuelScale, 1, 1);
		RenderMesh(meshes["FuelCurrent"], shaders["VertexNormal"], fuelM);
	}

	// Check collisions with obstacles
	for (int i = 0; i < MAX_OBSTACLES_IN_SCENE; i++) {
		// Plane collided with an obstacle
		if (obstacleInScene[i] && PlaneCollided(planePositions, obstacleCenter[i], 0.25f)) {
			// Remove the obstacle from the scene
			obstacleInScene[i] = false;
			obstacleCount--;

			// Lose a life
			if (!planeImmune && lives > 0) {
				lives--;
			}

			// If out of lives, plane must freefall
			if (lives == 0) {
				freefall = true;
			}

			break;
		}
	}

	// Check collisions with fuel cans
	for (int i = 0; i < MAX_CANS_IN_SCENE; i++) {
		// Plane collided with a fuel can
		if (fuelCanInScene[i] && PlaneCollided(planePositions, fuelCanCenter[i], 0.25f)) {
			// Remove the fuel can from the scene
			fuelCanInScene[i] = false;
			
			// If game is still on regain fuel
			if (lives > 0) {
				fuel += 10;

				if (fuel > 100) {
					fuel = 100;
				}
			}

			break;
		}
	}

	if (regainLifeInScene && PlaneCollided(planePositions, powerUpCenter, 0.25f)) {
		regainLifeInScene = false;

		if (!freefall) {
			lives++;
		}

		elapsedTime2 = Engine::GetElapsedTime();
	}

	if (immunityInScene && PlaneCollided(planePositions, powerUpCenter, 0.25f)) {
		immunityInScene = false;

		planeImmune = true;

		immunityStart = Engine::GetElapsedTime();
		elapsedTime2 = Engine::GetElapsedTime();
	}

	// Update first person camera data
	if (firstPerson) {
		glm::vec3 position = glm::vec3(firstPersonCameraPosition.x,
			firstPersonCameraPosition.y,
			firstPersonCameraPosition.z);

		glm::vec3 forward = glm::vec3(firstPersonCameraForward.x,
			firstPersonCameraForward.y,
			firstPersonCameraForward.z);

		glm::vec3 up = glm::vec3(firstPersonCameraUp.x,
			firstPersonCameraUp.y,
			firstPersonCameraUp.z);

		glm::vec3 right = glm::vec3(firstPersonCameraRight.x,
			firstPersonCameraRight.y,
			firstPersonCameraRight.z);

		camera->Set(position, forward, up, right);
	}
}

void Tema2::FrameEnd()
{

}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	int location = glGetUniformLocation(shader->GetProgramID(), "Model");

	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// TODO : get shader location for uniform mat4 "View"
	location = glGetUniformLocation(shader->GetProgramID(), "View");

	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	location = glGetUniformLocation(shader->GetProgramID(), "Projection");

	// TODO : set shader uniform "Projection" to projectionMatrix;
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	location = glGetUniformLocation(shader->GetProgramID(), "ElapsedTime");
	glUniform1f(location, (float) Engine::GetElapsedTime());

	location = glGetUniformLocation(shader->GetProgramID(), "object_color");
	glUniform3f(location, color.r, color.g, color.b);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

bool Tema2::PlaneCollided(std::vector<glm::vec4> planePositions, glm::vec4 objectCenter, float objectRay)
{
	// For each vertex of the plane check the distance between it and the object (obstacle / fuel can) center
	for (glm::vec4 vertex : planePositions) {
		glm::vec4 diff = glm::abs(vertex - objectCenter);

		// If the distance is smaller than object's ray there is a collision
		if (diff.x < objectRay && diff.y < objectRay && diff.z < objectRay) {
			return true;
		}
	}

	return false;
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	// Increase plane acceleration
	if (window->KeyHold(GLFW_KEY_W) && planeAcceleration < 15 && lives > 0) {
		planeAcceleration += 0.04f;
	}

	// Decrease plane acceleration
	if (window->KeyHold(GLFW_KEY_S) && planeAcceleration > 1 && lives > 0) {
		planeAcceleration -= 0.04f;
	}

	// Go left
	if (window->KeyHold(GLFW_KEY_A) && planeTranslationOZ > -2 && lives > 0) {
		planeTranslationOZ -= 0.05f;

		if (planeAngleOY < M_PI / 6) {
			planeAngleOY += 0.02f;
		}
	}

	// Go right
	if (window->KeyHold(GLFW_KEY_D) && planeTranslationOZ < 2 && lives > 0) {
		planeTranslationOZ += 0.05f;

		if (planeAngleOY > -M_PI / 6) {
			planeAngleOY -= 0.02f;
		}
	}
};

void Tema2::OnKeyPress(int key, int mods)
{
	// Switch between first person and third person
	if (key == GLFW_KEY_C) {
		if (firstPerson) {
			firstPerson = false;
			camera->Set(glm::vec3(0, 1.85f, 4), glm::vec3(0, 1.85f, 3), glm::vec3(0, 1, 0));
		}
		else {
			firstPerson = true;
			glm::vec3 position = glm::vec3(firstPersonCameraPosition.x, firstPersonCameraPosition.y, firstPersonCameraPosition.z);
			glm::vec3 forward = glm::vec3(firstPersonCameraForward.x, firstPersonCameraForward.y, firstPersonCameraForward.z);
			glm::vec3 up = glm::vec3(firstPersonCameraUp.x, firstPersonCameraUp.y, firstPersonCameraUp.z);
			glm::vec3 right = glm::vec3(firstPersonCameraRight.x, firstPersonCameraUp.y, firstPersonCameraUp.z);
			camera->Set(position, forward, up, right);
		}
	}

	// Reset the game - start over
	if (key == GLFW_KEY_R) {
		planeTranslationOY = 1.5f;
		planeTranslationOZ = 0;
		pilotHairScale = 1;
		sign = 1;
		planeSmokeScale = 0;

		planeAngleOY = 0;
		planeAngleOZ = 0;

		planeAcceleration = 1;

		propellerAngle = 0;

		seaAngle = 0;

		freefall = false;
		planeImmune = false;

		lives = 3;
		fuel = MAX_FUEL;

		cloudCount = 0;

		for (int i = 0; i < MAX_CLOUDS_IN_SCENE; i++) {
			cloudTranslationX[i] = 0;
			cloudTranslationY[i] = (float) (-3 - (rand() % 10));
			cloudTranslationZ[i] = (float) pow(-1, rand() % 2) * 4;

			cloudRotationOZ[i] = 0;
		}

		obstacleCount = 0;

		for (int i = 0; i < MAX_OBSTACLES_IN_SCENE; i++) {
			obstacleInScene[i] = false;
		}

		fuelCanTranslationX[0] = 0;
		fuelCanTranslationY[0] = (float)(-3 - (rand() % 2));
		fuelCanTranslationZ[0] = (float)pow(-1, rand() % 2) * (rand() % 3);
		fuelCanRotationOZ[0] = 0;

		fuelCanInScene[0] = true;

		for (int i = 1; i < MAX_CANS_IN_SCENE; i++) {
			fuelCanTranslationX[i] = fuelCanTranslationX[i - 1] + 0.25f;
			fuelCanTranslationY[i] = fuelCanTranslationY[i - 1] + 0.25f * pow(-1, i);
			fuelCanTranslationZ[i] = fuelCanTranslationZ[i - 1];

			fuelCanRotationOZ[i] = 0;

			fuelCanInScene[i] = true;
		}

		fuelCanRotationOY = 0;

		smokeCloudCount = 0;

		for (int i = 0; i < MAX_SMOKE_CLOUDS; i++) {
			smokeCloudInScene[i] = false;
		}

		regainLifeInScene = false;
		immunityInScene = false;

		elapsedTime1 = Engine::GetElapsedTime();
		elapsedTime2 = Engine::GetElapsedTime();
	}
};

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Move plane up and down
	if (lives > 0) {
		planeTranslationOY -= 0.005f * deltaY;

		if (planeTranslationOY < 1) {
			planeTranslationOY = 1;
		}

		if (planeTranslationOY > 3) {
			planeTranslationOY = 3;
		}

		planeAngleOZ -= 0.002f * deltaY;
	}
};

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Tema2::OnWindowResize(int width, int height)
{
	// treat window resize event
}
