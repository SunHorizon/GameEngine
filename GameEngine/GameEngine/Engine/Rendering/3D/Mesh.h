#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "../../Camera/Camera.h"
#include "../../Graphics/Materialhandler.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 colour;
};

struct SubMesh
{
	std::vector<Vertex> vertexList;
	std::vector<int> meshIndices;
	Material material;
};

class Mesh
{
public:

	Mesh(SubMesh subMesh_, GLuint shaderProgram_);
	~Mesh();
	void Render(Camera* camera, std::vector<glm::mat4> &instance_);
	void OnDestroy();
	

private:
	void GenerateBuffers();
	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint modelLoc;
	GLuint viewLoc;
	GLuint projLoc, TextureLoc;
	SubMesh subMesh;

	GLuint viewPosition, lighPosition, lighAmbient, lighDiffuse, lighColor;
	GLuint diffuseMapLoc, shinninesLoc, transparencyLoc, ambientLoc, diffuseLoc, specLoc;
	
};
#endif // !MESH_H

