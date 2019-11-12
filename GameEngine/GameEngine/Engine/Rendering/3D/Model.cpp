#include "Model.h"



Model::Model(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_) : shaderProgram(0), subMeshes(std::vector<Mesh*>()), modelInstances(std::vector<glm::mat4>())
{
	shaderProgram = shaderProgram_;
	obj = new LoadObjModel();
	
	obj->LoadModel(objPath_, matPath_);
	this->LoadModel();
}


Model::~Model()
{
	OnDestory();
}

void Model::AddMesh(Mesh* mesh_)
{
	// add the mesh to the vector
	subMeshes.push_back(mesh_);
}

void Model::Render(Camera* camera)
{
	//glUseProgram(shaderProgram);
	// call mesh render
	if (subMeshes.size() > 0)
	{
		for (Mesh* mesh : subMeshes)
		{
			mesh->Render(camera, modelInstances);
		}
	}
}

void Model::OnDestory()
{
	if (subMeshes.size() > 0)
	{
		for (auto mesh : subMeshes)
		{
			delete mesh;
			mesh = nullptr;
		}
		subMeshes.clear();
	}
	modelInstances.clear();
}

int Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances.push_back(GetTranfrom(position_, angle_, rotation_, scale_));
	return modelInstances.size() - 1;
}

void Model::updateInstance(int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances[index_] = GetTranfrom(position_, angle_, rotation_, scale_);
}

glm::mat4 Model::GetTranfrom(int index_) const
{
	return modelInstances[index_];
}

void Model::LoadModel()
{
	for(int i = 0; i < obj->GetSubMeshes().size(); i++)
	{
		subMeshes.push_back(new Mesh(obj->GetSubMeshes()[i], shaderProgram));
	}
	boundingBox = obj->getBoundingBox();
	delete obj;
	obj = nullptr;
}

glm::mat4 Model::GetTranfrom(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const
{
	glm::mat4 model;
	model = glm::translate(model, position_);
	model = glm::rotate(model, angle_, rotation_);
	model = glm::scale(model, scale_);
		
	return model;
}

BoundingBox Model::getBoundingBox()
{
	return boundingBox;
}

GLuint Model::GetShaderProgram() const
{
	return shaderProgram;
}

