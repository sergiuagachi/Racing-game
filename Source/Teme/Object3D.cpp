#include "Object3D.h"
#include <Core/Engine.h>
#include <iostream>

Mesh* Object3D::CreateRoad(std::string name, glm::vec3 corner, float roadWidth, float roadLength)
{
	glm::vec3 colorDunga = glm::vec3(1, 1, 1);
	glm::vec3 colorAsfalt = glm::vec3(0.2f, 0.2f, 0.2f);
	glm::vec3 colorBordura = glm::vec3(0.411f, 0.556f, 0.815f);

	glm::vec3 bandaC = corner + glm::vec3(1 + roadWidth / 2, 0.01f, -roadLength / 4);

	glm::vec3 leftRC1 = corner;
	glm::vec3 leftRC2 = leftRC1 + glm::vec3(0, 0, -roadLength);

	glm::vec3 rightRC1 = leftRC1 + glm::vec3(1 + roadWidth, 0, 0);
	glm::vec3 rightRC2 = rightRC1 + glm::vec3(0, 0, -roadLength);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(leftRC1, colorBordura),
		VertexFormat(leftRC1 + glm::vec3(1, 0, 0), colorBordura),
		VertexFormat(leftRC1 + glm::vec3(1, 1, 0), colorBordura),
		VertexFormat(leftRC1 + glm::vec3(0, 1, 0), colorBordura),
	
		VertexFormat(leftRC2, colorBordura),
		VertexFormat(leftRC2 + glm::vec3(1, 0, 0), colorBordura),
		VertexFormat(leftRC2 + glm::vec3(1, 1, 0), colorBordura),
		VertexFormat(leftRC2 + glm::vec3(0, 1, 0), colorBordura),	

		VertexFormat(rightRC1, colorBordura),
		VertexFormat(rightRC1 + glm::vec3(1, 0, 0), colorBordura),		
		VertexFormat(rightRC1 + glm::vec3(1, 1, 0), colorBordura),
		VertexFormat(rightRC1 + glm::vec3(0, 1, 0), colorBordura),

		VertexFormat(rightRC2, colorBordura),
		VertexFormat(rightRC2 + glm::vec3(1, 0, 0), colorBordura),
		VertexFormat(rightRC2 + glm::vec3(1, 1, 0), colorBordura),
		VertexFormat(rightRC2 + glm::vec3(0, 1, 0), colorBordura),

		VertexFormat(leftRC1 + glm::vec3(1, 0, 0), colorAsfalt),
		VertexFormat(rightRC1, colorAsfalt),
		VertexFormat(rightRC2 + glm::vec3(0, 0, -1), colorAsfalt),
		VertexFormat(leftRC2 + glm::vec3(1, 0, -1), colorAsfalt),

		VertexFormat(bandaC, colorDunga),
		VertexFormat(bandaC + glm::vec3(0.1f, 0, 0), colorDunga),
		VertexFormat(bandaC + glm::vec3(0.1f, 0, -roadLength / 2), colorDunga),
		VertexFormat(bandaC + glm::vec3(0, 0, -roadLength / 2), colorDunga),
	};

	Mesh* road = new Mesh(name);
	std::vector<unsigned short> indices = { 
											//square face 1
											0, 1, 2,
											2, 3, 0,

											//square face 2
											4, 5, 6,
											6, 7, 4,

											//rectangle side 1
											1, 5, 6,
											6, 2, 1,
			
											//rectangle side 2
											0, 4, 7,
											7, 3, 0,

											//rectangle top 
											3, 2, 6,
											6, 7, 3,

											//rectangle bottom
											0, 1, 5,
											5, 4, 0,

											//road
											//1, 8, 12,
											//12, 5, 1,
											16, 17, 18,
											18, 19, 16,
											
											//square face 1
											8, 9, 10,
											10, 11, 8,

											//square face 2
											12, 13, 14,
											14, 15, 12,

											//rectangle side 1
											9, 13, 14,
											14, 10, 9,

											//rectangle side 2
											8, 12, 15,
											15, 11, 8,

											//rectangle top
											11, 10, 14,
											14, 15, 11,

											//rectangle bottom
											8, 9, 13,
											13, 12, 8,

											//banda
											20, 21, 22,
											22, 23, 20,
											
	};

	road->InitFromData(vertices, indices);
	return road;
}

Mesh* Object3D::CreateCar(std::string name, glm::vec3 corner, float bodyWidth, float bodyLength)
{

	glm::vec3 bodyC1 = corner;
	glm::vec3 bodyC2 = corner + glm::vec3(0, 0, -bodyLength);
	glm::vec3 colorB = glm::vec3(1, 0, 0);
	float carHeight = 1;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(bodyC1 , colorB),
		VertexFormat(bodyC1 + glm::vec3(bodyWidth, 0, 0), colorB),
		VertexFormat(bodyC1 + glm::vec3(bodyWidth, carHeight, 0), colorB),
		VertexFormat(bodyC1 + glm::vec3(0, carHeight, 0), colorB),

		VertexFormat(bodyC2 , colorB),
		VertexFormat(bodyC2 + glm::vec3(bodyWidth, 0, 0), colorB),
		VertexFormat(bodyC2 + glm::vec3(bodyWidth, carHeight, 0), colorB),
		VertexFormat(bodyC2 + glm::vec3(0, carHeight, 0), colorB),
	};

	Mesh* car = new Mesh(name);
	std::vector<unsigned short> indices = {
		//square face 1
		0, 1, 2,
		2, 3, 0,

		//square face 2
		4, 5, 6,
		6, 7, 4,

		//rectangle side 1
		1, 5, 6,
		6, 2, 1,

		//rectangle side 2
		0, 4, 7,
		7, 3, 0,

		//rectangle top 
		3, 2, 6,
		6, 7, 3,

		//rectangle bottom
		0, 1, 5,
		5, 4, 0,
	};

	car->InitFromData(vertices, indices);
	return car;
}

Mesh* Object3D::CreateWheel(std::string name, glm::vec3 center, float length)
{

	float half = length / 2;
	glm::vec3 color = glm::vec3(0.1f, 0.1f, 0.1f);
	glm::vec3 center1 = center - glm::vec3(0.3f, 0, 0);
	glm::vec3 center2 = center + glm::vec3(0.3f, 0, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center1, color),
		VertexFormat(center1 + glm::vec3(0, -half - half * sqrt(2), -half), color),
		VertexFormat(center1 + glm::vec3(0, -half - half * sqrt(2), half), color),
		VertexFormat(center1 + glm::vec3(0, -half, half + half * sqrt(2)), color),
		VertexFormat(center1 + glm::vec3(0, half, half + half * sqrt(2)), color),
		VertexFormat(center1 + glm::vec3(0, half + half * sqrt(2), half), color),
		VertexFormat(center1 + glm::vec3(0, half + half * sqrt(2), -half), color),
		VertexFormat(center1 + glm::vec3(0, half, -half - half * sqrt(2)), color),
		VertexFormat(center1 + glm::vec3(0, -half, -half - half * sqrt(2)), color),

		VertexFormat(center2, color),
		VertexFormat(center2 + glm::vec3(0, -half - half * sqrt(2), -half), color),
		VertexFormat(center2 + glm::vec3(0, -half - half * sqrt(2), half), color),
		VertexFormat(center2 + glm::vec3(0, -half, half + half * sqrt(2)), color),
		VertexFormat(center2 + glm::vec3(0, half, half + half * sqrt(2)), color),
		VertexFormat(center2 + glm::vec3(0, half + half * sqrt(2), half), color),
		VertexFormat(center2 + glm::vec3(0, half + half * sqrt(2), -half), color),
		VertexFormat(center2 + glm::vec3(0, half, -half - half * sqrt(2)), color),
		VertexFormat(center2 + glm::vec3(0, -half, -half - half * sqrt(2)), color),
	};

	Mesh* wheel = new Mesh(name);
	std::vector<unsigned short> indices = { 
		//side1
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		0, 5, 6,
		0, 6, 7,
		0, 7, 8,
		0, 8, 1,

		//side2
		9, 10, 11,
		9, 11, 12,
		9, 12, 13,
		9, 13, 14,
		9, 14, 15,
		9, 15, 16,
		9, 16, 17,
		9, 17, 10,

		//faces
		1, 10, 11,
		11, 2, 1,

		2, 11, 12,
		12, 3, 2,

		3, 12, 13,
		13, 4, 3,

		4, 13, 14,
		14, 5, 4,

		5, 14, 15,
		15, 6, 5,

		6, 15, 16,
		16, 7, 6,

		7, 16, 17,
		17, 8, 7,

		8, 17, 10,
		10, 1, 8,
	};

	wheel->InitFromData(vertices, indices);
	return wheel;
}

Mesh* Object3D::CreatePiramid(std::string name, glm::vec3 center, float length)
{

	float half = length / 2;
	glm::vec3 color = glm::vec3(0.96f, 0.5f, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center, color),
		VertexFormat(center + glm::vec3(0, length, 0), color),

		VertexFormat(center + glm::vec3(-half, 0, half), color),
		VertexFormat(center + glm::vec3(half, 0, half), color),
		VertexFormat(center + glm::vec3(half, 0, -half), color),
		VertexFormat(center + glm::vec3(-half, 0, -half), color),
	};

	Mesh* piramid = new Mesh(name);
	std::vector<unsigned short> indices = {
		5, 2, 3,
		3, 4, 5,

		3, 4, 1,
		4, 1, 5,
		5, 2, 1,
		2, 3, 1,
	};

	piramid->InitFromData(vertices, indices);
	return piramid;
}

Mesh* Object3D::CreateGround(std::string name, glm::vec3 center)
{
	glm::vec3 color = glm::vec3(0.572f, 0.815f, 0.313f);
	int length = 1000;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center + glm::vec3(-length, 0, -length), color),
		VertexFormat(center + glm::vec3(length, 0, -length), color),
		VertexFormat(center + glm::vec3(length, 0, length), color),
		VertexFormat(center + glm::vec3(-length, 0, length), color),
	};

	Mesh* ground = new Mesh(name);
	std::vector<unsigned short> indices = {
		0, 1, 2,
		2, 3, 0,
	};

	ground->InitFromData(vertices, indices);
	return ground;
}

Mesh* Object3D::CreateSkybox(std::string name, glm::vec3 center)
{
	int length = 1;
	glm::vec3 color = glm::vec3(0.25f, 0.1f, 0.9f);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center + glm::vec3(-length, -length, -length), color),
		VertexFormat(center + glm::vec3(length, -length, -length), color),
		VertexFormat(center + glm::vec3(length, -length, length), color),
		VertexFormat(center + glm::vec3(-length, -length, length), color),

		VertexFormat(center + glm::vec3(-length, length, -length), color),
		VertexFormat(center + glm::vec3(length, length, -length), color),
		VertexFormat(center + glm::vec3(length, length, length), color),
		VertexFormat(center + glm::vec3(-length, length, length), color),
	};

	Mesh* skybox = new Mesh(name);
	std::vector<unsigned short> indices = {
		//square face 1
		0, 1, 2,
		2, 3, 0,

		//square face 2
		4, 5, 6,
		6, 7, 4,

		//rectangle side 1
		6, 5, 1,
		1, 2, 6,

		//rectangle side 2
		7, 4, 0,
		0, 3, 7,

		//rectangle top 
		3, 2, 6,
		6, 7, 3,

		//rectangle bottom
		0, 1, 5,
		5, 4, 0,
	};

	skybox->InitFromData(vertices, indices);
	return skybox;
}