#include "Tema2.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform3D.h"
#include "Object3D.h"

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	polygonMode = GL_FILL;
	{
		// car generating
		{
			glm::vec3 carCorner = glm::vec3(0, 0, 0);
			Mesh* car = Object3D::CreateCar("car", carCorner, carBodyWidth, carBodyLength);
			AddMeshToList(car);

			Mesh* wheel1 = Object3D::CreateWheel("wheel1", glm::vec3(0, 0, 0), 0.5f);
			AddMeshToList(wheel1);

			Mesh* wheel2 = Object3D::CreateWheel("wheel2", glm::vec3(carBodyWidth, 0, carZ), 0.5f);
			AddMeshToList(wheel2);

			Mesh* wheel3 = Object3D::CreateWheel("wheel3", glm::vec3(0, 0, carZ - carBodyLength), 0.5f);
			AddMeshToList(wheel3);

			Mesh* wheel4 = Object3D::CreateWheel("wheel4", glm::vec3(carBodyWidth, 0, carZ - carBodyLength), 0.5f);
			AddMeshToList(wheel4);
		}

		// road & obstacles generating
		{
			roadGen.push_back(glm::vec2(1, 10 * 8));
			roadGen.push_back(glm::vec2(2, 5 * 8));
			roadGen.push_back(glm::vec2(1, 10 * 8));
			roadGen.push_back(glm::vec2(3, 4 * 8));

			roadGen.push_back(glm::vec2(2, /*7 * 8*/ 52));
			roadGen.push_back(glm::vec2(1, 92));
			roadGen.push_back(glm::vec2(2, 52));
			roadGen.push_back(glm::vec2(3, 4 * 8));

			Mesh* dynamicObstacle = Object3D::CreatePiramid("dyn", glm::vec3(0, 0, 0), 2);
			AddMeshToList(dynamicObstacle);

			for (int i = 0; i < roadGen.size(); i++) {

				glm::vec2 roadNow = roadGen[i];
				type = roadNow.x;

				for (int j = 0; j < roadNow.y; j++)
				{
					if (type == 2) {
						angle += M_PI / cornerTurn;
					}

					if (type == 3) {
						angle += 2 * M_PI - M_PI / cornerTurn;
					}

					angleVector.push_back(angle);
					std::string nowName = name + std::to_string(roadCount);
					glm::vec3 leftBotCorner;
					float x, z;

					if (roadCount == 0) {
						x = 0;
						z = 30;
					}
					else {
						x = xs[roadCount - 1] - roadLength * sin(angleVector[roadCount - 1]);
						z = zs[roadCount - 1] - roadLength * cos(angleVector[roadCount - 1]);
					}

					xs.push_back(x);
					zs.push_back(z);

					types.push_back(type);

					leftBotCorner = glm::vec3(x, 0, z);
					Mesh* road = Object3D::CreateRoad(nowName, leftBotCorner, roadWidth, roadLength);
					AddMeshToList(road);

					if (j == 2) {
						nowName = obsName + std::to_string(obstaclesCount);
						if (obstaclesCount % 2 == 1)
							leftBotCorner += glm::vec3(roadWidth / 2 + 2, 0, -2);
						else
							leftBotCorner += glm::vec3(4.8f, 0, 3);
						Mesh* obstacle = Object3D::CreatePiramid(nowName, leftBotCorner, 2);
						AddMeshToList(obstacle);
						obstaclesCount++;
					}

					roadCount++;
				}
			}
		}

		// environoment generating
		{
			Mesh* ground = Object3D::CreateGround("ground", glm::vec3(0, -0.1f, 0));
			AddMeshToList(ground);

			Mesh* skybox = Object3D::CreateSkybox("skybox", glm::vec3(0, 0, 0));
			AddMeshToList(skybox);
		}
	}

	GetSceneCamera()->SetPositionAndRotation(carCenter + glm::vec3(-posX, 4, posZ), glm::vec3(-M_PI / 10, carAngle, 0));

	{
		Shader *shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Teme/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Teme/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Tema2::FrameStart()
{

}

void Tema2::Update(float deltaTimeSeconds)
{
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(0, 0, 0, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	//road rendering
	for (int i = 0; i < roadCount; i++) {
		std::string nowName = name + std::to_string(i);
		float x = xs[i];
		float z = zs[i];
		modelMatrix = glm::mat4(1);

		modelMatrix =
			Transform3D::Translate(x + 2 + roadWidth / 2, 0, z + 1.5f) *
			Transform3D::RotateOY(angleVector[i]) *
			Transform3D::Translate(-(x + 2 + roadWidth / 2), 0, -(z + 1.5f));
		RenderMesh(meshes[nowName], shaders["VertexColor"], modelMatrix);
	}

	//obstacles rendering
	{
		for (int i = 0; i < obstaclesCount; i++) {
			std::string nowName = obsName + std::to_string(i);
			modelMatrix = glm::mat4(1);
			RenderMesh(meshes[nowName], shaders["VertexColor"], modelMatrix);
		}

		modelMatrix = glm::mat4(1);
		modelMatrix *=
			Transform3D::Translate(dynx, 0.1f, dynz) *
			Transform3D::Scale(5, 5, 5);
		RenderMesh(meshes["dyn"], shaders["VertexColor"], modelMatrix);
	}

	//body movement
	{
		modelMatrix = glm::mat4(1);
		modelMatrix *=
			Transform3D::Translate(carX + carBodyWidth / 2, carY, carZ - carBodyLength / 2) *
			Transform3D::RotateOY(carAngle) *
			Transform3D::Translate(-carBodyWidth / 2, carY, carBodyLength / 2);
		RenderMesh(meshes["car"], shaders["VertexColor"], modelMatrix);

		//wheels movement
		modelMatrix = glm::mat4(1);
		modelMatrix *=
			Transform3D::Translate(carX + carBodyWidth / 2, carY, carZ - carBodyLength / 2) *
			Transform3D::RotateOY(carAngle) *
			Transform3D::Translate(-carBodyWidth / 2, carY, carBodyLength / 2) *

			Transform3D::RotateOX(wheelAngle);
		RenderMesh(meshes["wheel1"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *=
			Transform3D::Translate(carX + carBodyWidth / 2, carY, carZ - carBodyLength / 2) *
			Transform3D::RotateOY(carAngle) *
			Transform3D::Translate(-carBodyWidth / 2, carY, carBodyLength / 2) *

			Transform3D::RotateOX(wheelAngle);
		RenderMesh(meshes["wheel2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *=
			Transform3D::Translate(carX + carBodyWidth / 2, carY, carZ - carBodyLength / 2) *
			Transform3D::RotateOY(carAngle) *
			Transform3D::Translate(-carBodyWidth / 2, carY, carBodyLength / 2) *

			Transform3D::Translate(0, 0, -carBodyLength) *
			Transform3D::RotateOX(wheelAngle) *
			Transform3D::Translate(0, 0, carBodyLength);
		RenderMesh(meshes["wheel3"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat4(1);
		modelMatrix *=
			Transform3D::Translate(carX + carBodyWidth / 2, carY, carZ - carBodyLength / 2) *
			Transform3D::RotateOY(carAngle) *
			Transform3D::Translate(-carBodyWidth / 2, carY, carBodyLength / 2) *

			Transform3D::Translate(carBodyWidth, 0, -carBodyLength) *
			Transform3D::RotateOX(wheelAngle) *
			Transform3D::Translate(-carBodyWidth, 0, carBodyLength);
		RenderMesh(meshes["wheel4"], shaders["VertexColor"], modelMatrix);
	}

	// directional vector computing
	{
		moveX = defX * cos(carAngle) - defZ * sin(carAngle);
		moveZ = defX * sin(carAngle) + defZ * cos(carAngle);

		posX = defposX * cos(carAngle) - defposZ * sin(carAngle);
		posZ = defposX * sin(carAngle) + defposZ * cos(carAngle);
	}

	// update params
	lastAngle = carAngle;

	// render environoment
	{
		whatToSend = 0;
		modelMatrix = glm::mat4(1);
		RenderSimpleMesh(meshes["ground"], shaders["ShaderTema2"], modelMatrix);

		whatToSend = 1;
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Scale(100, 100, 100);
		RenderSimpleMesh(meshes["skybox"], shaders["ShaderTema2"], modelMatrix);
	}

	if (speed >= 0.1f)
		speed -= 0.05f;
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	dynx += dyn;

	if (dynx >= 20)
		dyn = -0.5f;
	else
		if (dynx <= -30)
			dyn = 0.5f;

	carZ -= moveZ * deltaTime * speed;
	carX += moveX * deltaTime * speed;

	if (speed > 0.2)
		wheelAngle--;

	carCenter = glm::vec3(carX + carBodyWidth / 2, carY + 0.5f, carZ - carBodyLength / 2);

	if (cameraType == 3)
		GetSceneCamera()->SetPositionAndRotation(carCenter + glm::vec3(-posX, 4, posZ), glm::vec3(-M_PI / 10, carAngle, 0));

	if (cameraType == 1)
		GetSceneCamera()->SetPositionAndRotation(carCenter + glm::vec3(-posX, 0, posZ), glm::vec3(-M_PI / 10, carAngle, 0));

	if (window->KeyHold(GLFW_KEY_W)) {
		if (speed < 10)
			speed += 0.3f;
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		if (speed <= 0) {
			carZ += moveZ * deltaTime;
			carX -= moveX * deltaTime;
		}
		else
			speed -= 0.3f;
		wheelAngle += 0.125f;
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		carAngle += M_PI / carTurn * deltaTime;
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		carAngle -= M_PI / carTurn * deltaTime;
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_Z) {
		if (cameraType == 3) {
			cameraType = 1;
			defposZ = -carBodyLength;
		}
		else {
			cameraType = 3;
			defposZ = 9;
		}
	}

	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}
}

Mesh* Tema2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object

	Mesh* mesh = new Mesh(name);
	mesh->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	mesh->vertices = vertices;
	mesh->indices = indices;
	return mesh;
}

void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	int model_location = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	int view_location = glGetUniformLocation(shader->program, "View");
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	int proj_location = glGetUniformLocation(shader->program, "Projection");
	glm::mat4 projMatrix = GetSceneCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(projMatrix));

	int timeshader = glGetUniformLocation(shader->program, "Time");
	glUniform1f(timeshader, Engine::GetElapsedTime());

	int type_send = glGetUniformLocation(shader->program, "Type");
	glUniform1i(type_send, whatToSend);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}
;