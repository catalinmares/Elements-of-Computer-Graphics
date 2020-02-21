#include "Tema3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform3D.h"

using namespace std;

Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{
	camera = new Cam::Camera();

	position1 = glm::vec3(1, 0.15f, 0);
	forward1 = glm::vec3(-1, 0, 0);
	right1 = glm::vec3(0, 0, -1);
	up1 = glm::vec3(0, 1, 0);

	position2 = glm::vec3(-1, 0.15f, 0);
	forward2 = glm::vec3(1, 0, 0);
	right2 = glm::vec3(0, 0, 1);
	up2 = glm::vec3(0, 1, 0);

	// Set projection matrix
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.1f, 100.f);
	cameraOnPlayer = true;

	const string textureLoc = "Source/Laboratoare/Tema3/Textures/";

	// Load textures
	{
		{
			Texture2D* texture = new Texture2D();
			texture->Load2D((textureLoc + "heightmap.png").c_str(), GL_REPEAT);
			mapTextures["Terrain"] = texture;
		}
	}

	// MESH INITIALIZATION
	{
		{
			Mesh* worm = new Mesh("Worm");
			worm->LoadMesh(RESOURCE_PATH::MODELS + "Characters/Worm", "worm.obj");
			AddMeshToList(worm);
		}

		{
			Mesh* terrain = new Mesh("Terrain");
			terrain->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "plane50.obj");
			AddMeshToList(terrain);
		}

		{
			Mesh* bullet = new Mesh("Bullet");
			bullet->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
			AddMeshToList(bullet);
		}
	}

	// SHADERS INITIALIZATION
	{
		// Create a shader program for drawing face polygon with the color of the normal
		{
			Shader* shader = new Shader("ShaderTema3");
			shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
			shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
			shader->CreateAndLink();
			shaders[shader->GetName()] = shader;
		}

		{
			Shader* shader = new Shader("ColorShader");
			shader->AddShader("Source/Laboratoare/Tema3/Shaders/ColorVertexShader.glsl", GL_VERTEX_SHADER);
			shader->AddShader("Source/Laboratoare/Tema3/Shaders/ColorFragmentShader.glsl", GL_FRAGMENT_SHADER);
			shader->CreateAndLink();
			shaders[shader->GetName()] = shader;
		}
	}

	heightPixels = stbi_load((textureLoc + "heightmap.png").c_str(), &width, &height, &channels, STBI_grey);
	size = width * height * channels;

	int player1Row = (6.f + 25.f) * height / 50.f;
	int player1Col = (-7.75f + 25.f) * width / 50.f;

	int player1Height = (int)heightPixels[player1Row * width + player1Col];

	int player2Row = (-5.9f + 25.f) * height / 50.f;
	int player2Col = (10.15f + 25.f) * width / 50.f;

	int player2Height = (int)heightPixels[player2Row * width + player2Col];

	player1RotationAngleOX = 0;
	player2RotationAngleOX = 0;
	player1RotationAngleOY = 0;
	player2RotationAngleOY = 0;

	currentPlayer = 1;

	shotsFired = false;
	modified = false;

	bullet1Position = glm::vec4(-7.75f, 5.f * player1Height / 256.f, 6, 1);
	bullet2Position = glm::vec4(10.15f, 5.f * player2Height / 256.f, -5.9f, 1);

	bullet1TranslationOX = 0;
	bullet1TranslationOY = 0;
	bullet1TranslationOZ = 0;
	bullet1Gravity = 0;

	bullet2TranslationOX = 0;
	bullet2TranslationOY = 0;
	bullet2TranslationOZ = 0;
	bullet2Gravity = 0;

	light1Position = glm::vec3(-7.75f, 5.f * player1Height / 256.f + 3.f, 6);
	light1Direction = glm::vec3(0, -1, 0);

	light2Position = glm::vec3(10.15f, 5.f * player2Height / 256.f + 3.f, -5.9f);
	light2Direction = glm::vec3(0, -1, 0);

	materialShininess = 30;
	materialKd = 0.5;
	materialKs = 0.5;
}

void Tema3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.5f, 0.5f, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::Update(float deltaTimeSeconds)
{
	int player1Row = (6.f + 25.f) * height / 50.f;
	int player1Col = (-7.75f + 25.f) * width / 50.f;

	int player1Height = (int)heightPixels[player1Row * width + player1Col];

	int player2Row = (-5.9f + 25.f) * height / 50.f;
	int player2Col = (10.15f + 25.f) * width / 50.f;

	int player2Height = (int)heightPixels[player2Row * width + player2Col];

	if (!shotsFired) {
		if (currentPlayer == 1) {
			camera->Set(position1, forward1, up1, right1);
			camera->TranslateForward(7.75f);
			camera->TranslateUpword(5.f * player1Height / 256.f);
			camera->TranslateRight(-6);
			camera->RotateThirdPerson_OX(player1RotationAngleOX);
			camera->RotateThirdPerson_OY(player1RotationAngleOY);
		}
		else {
			camera->Set(position2, forward2, up2, right2);
			camera->TranslateForward(10.15f);
			camera->TranslateUpword(5.f * player2Height / 256.f);
			camera->TranslateRight(-5.9f);
			camera->RotateThirdPerson_OX(player2RotationAngleOX);
			camera->RotateThirdPerson_OY(player2RotationAngleOY);
		}
	}

	player1 = glm::mat4(1);
	player1 *= Transform3D::Translate(-7.75f, 5.f * player1Height / 256.f, 6);
	player1 *= Transform3D::RotateOY(RADIANS(-130));
	player1 *= Transform3D::RotateOY(player1RotationAngleOY);
	player1 *= Transform3D::Scale(0.15f, 0.15f, 0.15f);

	RenderMesh(meshes["Worm"], shaders["VertexNormal"], player1);

	player2 = glm::mat4(1);
	player2 *= Transform3D::Translate(10.15f, 5.f * player2Height / 256.f, -5.9f);
	player2 *= Transform3D::RotateOY(RADIANS(60));
	player2 *= Transform3D::RotateOY(player2RotationAngleOY);
	player2 *= Transform3D::Scale(0.15f, 0.15f, 0.15f);
	
	RenderMesh(meshes["Worm"], shaders["VertexNormal"], player2);

	RenderSimpleMesh(meshes["Terrain"], shaders["ShaderTema3"], glm::mat4(1), mapTextures["Terrain"]);

	bullet1 = glm::mat4(1);
	bullet1 *= Transform3D::Translate(-7.75f, 5.f * player1Height / 256.f, 6);
	bullet1 *= Transform3D::Scale(0.25f, 0.25f, 0.25f);

	bullet2 = glm::mat4(1);
	bullet2 *= Transform3D::Translate(10.15f, 5.f * player2Height / 256.f, -5.9f);
	bullet2 *= Transform3D::Scale(0.25f, 0.25f, 0.25f);

	if (shotsFired) {
		if (currentPlayer == 1) {
			float translationOX = 20 * dir1.x * deltaTimeSeconds;
			float translationOY = 20 * dir1.y * deltaTimeSeconds;
			float translationOZ = 20 * dir1.z * deltaTimeSeconds;
			float gravity = 5 * deltaTimeSeconds;
			
			bullet1TranslationOX += translationOX;
			bullet1TranslationOY += translationOY;
			bullet1TranslationOZ += translationOZ;
			bullet1Gravity += gravity;

			bullet1 *= Transform3D::Translate(bullet1TranslationOX,
											  bullet1TranslationOY - bullet1Gravity,
											  bullet1TranslationOZ);

			bullet1Position = glm::vec4(bullet1 * glm::vec4(0, 0, 0, 1));

			int currentRow = (bullet1Position.z + 25.f) * height / 50.f;
			int currentCol = (bullet1Position.x + 25.f) * width / 50.f;

			unsigned char terrainH = heightPixels[currentRow * width + currentCol];
			float terrainHeight = 5.f * terrainH / 256.f;

			cout << "Projectile height: " << bullet1Position.y << "\n" << "Terrain height: " << terrainHeight << "\n";

			if (OutOfMap(bullet1Position) || terrainHeight >= bullet1Position.y) {
				shotsFired = false;
				currentPlayer = 2;

				if (terrainHeight >= bullet1Position.y) {
					int startRow = max(0, currentRow - 5);
					int endRow = min(height - 1, currentRow + 5);

					int startCol = max(0, currentCol - 5);
					int endCol = min(width - 1, currentCol + 5);

					int amplRow = 0;
					for (int i = startRow; i <= endRow; i++) {
						if (i < currentRow) {
							amplRow++;
						}

						if (i > currentRow) {
							amplRow--;
						}

						int amplCol = 0;
						for (int j = startCol; j <= endCol; j++) {
							if (j < currentCol) {
								amplCol++;
							}

							if (j > currentCol) {
								amplCol--;
							}

							int val = (int)heightPixels[i * width + j];

							if (val > 5 * amplRow * amplCol) {
								val -= 5 * amplRow * amplCol;
							}
							else {
								val = 0;
							}

							heightPixels[i * height + j] = (unsigned char)val;
						}
					}

					modified = true;
				}
			}

			glm::vec3 cam_position = camera->position;
			glm::vec3 cam_forward = camera->forward;
			glm::vec3 cam_up = camera->up;
			glm::vec3 cam_right = camera->right;

			cam_position.x += 0.25f * translationOX;
			cam_position.y += 0.25f * (translationOY - gravity);
			cam_position.z += 0.25f * translationOZ;

			camera->Set(cam_position, cam_forward, cam_up, cam_right);

			RenderSimpleMesh(meshes["Bullet"], shaders["ColorShader"], bullet1, glm::vec3(0));
		}
		else {
			float translationOX = 20 * dir2.x * deltaTimeSeconds;
			float translationOY = 20 * dir2.y * deltaTimeSeconds;
			float translationOZ = 20 * dir2.z * deltaTimeSeconds;
			float gravity = 5 * deltaTimeSeconds;

			bullet2TranslationOX += translationOX;
			bullet2TranslationOY += translationOY;
			bullet2TranslationOZ += translationOZ;
			bullet2Gravity += gravity;

			bullet2 *= Transform3D::Translate(bullet2TranslationOX,
											  bullet2TranslationOY - bullet2Gravity,
											  bullet2TranslationOZ);

			bullet2Position = glm::vec4(bullet2 * glm::vec4(0, 0, 0, 1));

			int currentRow = (bullet2Position.z + 25.f) * height / 50.f;
			int currentCol = (bullet2Position.x + 25.f) * width / 50.f;

			unsigned char terrainH = heightPixels[currentRow * width + currentCol];
			float terrainHeight = 5.f * terrainH / 256.f;

			cout << "Projectile height: " << bullet2Position.y << "\n" << "Terrain height: " << terrainHeight << "\n";

			if (OutOfMap(bullet2Position) || terrainHeight >= bullet2Position.y) {
				shotsFired = false;
				currentPlayer = 1;

				if (terrainHeight >= bullet2Position.y) {
					int startRow = max(0, currentRow - 5);
					int endRow = min(height - 1, currentRow + 5);

					int startCol = max(0, currentCol - 5);
					int endCol = min(width - 1, currentCol + 5);

					int amplRow = 0;
					for (int i = startRow; i <= endRow; i++) {
						if (i < currentRow) {
							amplRow++;
						}

						if (i > currentRow) {
							amplRow--;
						}

						int amplCol = 0;
						for (int j = startCol; j <= endCol; j++) {
							if (j < currentCol) {
								amplCol++;
							}

							if (j > currentCol) {
								amplCol--;
							}

							int val = (int)heightPixels[i * width + j];

							if (val > 5 * amplRow * amplCol) {
								val -= 5 * amplRow * amplCol;
							}
							else {
								val = 0;
							}

							heightPixels[i * height + j] = (unsigned char)val;
						}
					}

					modified = true;
				}
			}

			glm::vec3 cam_position = camera->position;
			glm::vec3 cam_forward = camera->forward;
			glm::vec3 cam_up = camera->up;
			glm::vec3 cam_right = camera->right;

			cam_position.x += 0.25f * translationOX;
			cam_position.y += 0.25f * (translationOY - gravity);
			cam_position.z += 0.25f * translationOZ;

			camera->Set(cam_position, cam_forward, cam_up, cam_right);
			
			RenderSimpleMesh(meshes["Bullet"], shaders["ColorShader"], bullet2, glm::vec3(0));
		}

		if (modified) {
			modified = false;

			glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, (void*)heightPixels);
		}
	}
}

void Tema3::FrameEnd()
{

}

void Tema3::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
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

void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
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

	location = glGetUniformLocation(shader->GetProgramID(), "object_color");
	glUniform3f(location, color.r, color.g, color.b);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	int light1_position = glGetUniformLocation(shader->program, "light1_position");
	glUniform3f(light1_position, light1Position.x, light1Position.y, light1Position.z);

	int light1_direction = glGetUniformLocation(shader->program, "light1_direction");
	glUniform3f(light1_direction, light1Direction.x, light1Direction.y, light1Direction.z);

	int light2_position = glGetUniformLocation(shader->program, "light2_position");
	glUniform3f(light2_position, light2Position.x, light2Position.y, light2Position.z);

	int light2_direction = glGetUniformLocation(shader->program, "light2_direction");
	glUniform3f(light2_direction, light2Direction.x, light2Direction.y, light2Direction.z);

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = camera->position;
	int eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(material_shininess, materialShininess);

	int material_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(material_kd, materialKd);

	int material_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(material_ks, materialKs);

	if (texture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

bool Tema3::OutOfMap(glm::vec4 bullet)
{
	float x = bullet.x;
	float y = bullet.y;
	float z = bullet.z;

	if (x < -25 || x > 25) {
		return true;
	}

	if (y < 0 || y > 25) {
		return true;
	}

	if (z < -25 || z > 25) {
		return true;
	}

	return false;
}

void Tema3::OnInputUpdate(float deltaTime, int mods)
{
	
};

void Tema3::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE && !shotsFired) {
		shotsFired = true;

		if (currentPlayer == 1) {
			dir1 = camera->forward;

			bullet1TranslationOX = 20 * dir1.x;
			bullet1TranslationOY = 20 * dir1.y;
			bullet1TranslationOZ = 20 * dir1.z;
			bullet1Gravity = 0;
		}
		else {
			dir2 = camera->forward;

			bullet2TranslationOX = 20 * dir2.x;
			bullet2TranslationOY = 20 * dir2.y;
			bullet2TranslationOZ = 20 * dir2.z;
			bullet2Gravity = 0;
		}
	}
};

void Tema3::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (!shotsFired) {
		if (currentPlayer == 1) {
			player1RotationAngleOX -= 0.0035 * deltaY;
			player1RotationAngleOY -= 0.0035 * deltaX;
		}
		else {
			player2RotationAngleOX -= 0.0035 * deltaY;
			player2RotationAngleOY -= 0.0035 * deltaX;
		}
	}
};

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Tema3::OnWindowResize(int width, int height)
{
	// treat window resize event
}
