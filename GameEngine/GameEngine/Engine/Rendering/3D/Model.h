#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include  "LoadObjModel.h"

class Model
{
public:

	Model(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_);
	~Model();
	void AddMesh(Mesh* mesh_);
	void Render(Camera* camera);
	void OnDestory();
	int CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	void updateInstance(int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	glm::mat4 GetTranfrom(int index_) const;

	BoundingBox getBoundingBox();
	GLuint GetShaderProgram() const;
private:
	std::vector<Mesh*> subMeshes;
	GLuint shaderProgram;
	glm::mat4 GetTranfrom(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const;
	void LoadModel();
	std::vector<glm::mat4> modelInstances;
	LoadObjModel* obj;
	BoundingBox boundingBox;
};
#endif // !MODEL_H



