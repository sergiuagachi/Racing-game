#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object3D
{
	Mesh * CreateRoad(std::string name, glm::vec3 corner, float roadWidth, float roadLength);
	Mesh * CreateCar(std::string name, glm::vec3 corner, float bodyWidth, float bodyLength);
	Mesh * CreateWheel(std::string name, glm::vec3 center, float length);
	Mesh * CreatePiramid(std::string name, glm::vec3 center, float length);
	Mesh * CreateGround(std::string name, glm::vec3 center);
	Mesh * CreateSkybox(std::string name, glm::vec3 center);
}

