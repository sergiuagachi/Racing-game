#pragma once

#include <Component/SimpleScene.h>
#include <Component/CameraInput.h>
#include <string>
#include <Core/Engine.h>
#include "TemaCamera.h"

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	//void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;

	void OnKeyPress(int key, int mods);

	Mesh * CreateMesh(const char * name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);

	void RenderSimpleMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix);

protected:
	glm::mat4 modelMatrix;
	GLenum polygonMode;

	// road params
	std::string name = "road";
	//int roadStart = 0;
	int roadCount = 0;
	int type = 1;
	float angle = 0;
	std::vector<float> angleVector;
	std::vector<float> xs;
	std::vector<float> zs;
	std::vector<int> types;
	int cornerTurn = 40;
	std::vector<glm::vec2> roadGen;
	float roadWidth = 10;
	float roadLength = 1;

	// car params
	float carBodyWidth = 3;
	float carBodyLength = 4;
	float carX = 3;
	float carY = 0.3f;
	float carZ = 0;
	float speed = 0;
	float carAngle = 0;
	float defX = 0, defZ = 2;
	float moveX = defX, moveZ = defZ;
	float lastAngle;
	float carTurn = 3;

	// wheel params
	float wheelAngle = 0;	

	// obstacle params
	std::string obsName = "obstacle";
	int obstaclesCount = 0;

	// 0 = ground; 1 = skybox;
	int whatToSend = 0;

	// camera
	EngineComponents::Camera *myCamera;
	glm::mat4 projectionMatrix;
	glm::vec3 carCenter;
	float defposX = 0;
	float defposZ = 9;
	float posX = defposX;
	float posZ = defposZ;
	float zp = 4;
	int cameraType = 3;

	//obstacle params
	float dynx = -25, dynz, dyn = 0.5f;
};
