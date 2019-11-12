#include "GameObject.h"



GameObject::GameObject(Model* model_) : model(nullptr), tag("")
{
	model = model_;
	position = glm::vec3();
	angle = 0.0f;
	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	scale = glm::vec3(1.0f);
	if(model)
	{
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		boundingBox = model->getBoundingBox();
		boundingBox.transform = model->GetTranfrom(modelInstance);
	}
}

GameObject::GameObject(Model* model_, glm::vec3 position__) : model(nullptr)
{
	model = model_;
	position = position__;
	angle = 0.0f;
	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	scale = glm::vec3(1.0f);
	if (model)
	{
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		boundingBox = model->getBoundingBox();
		boundingBox.transform = model->GetTranfrom(modelInstance);
	}
}


GameObject::~GameObject()
{
	OnDestory();
}

void GameObject::Render(Camera* camera)
{
	if(model)
	{
		model->Render(camera);
	}
}

glm::vec3 GameObject::GetPosition() const
{
	return position;
}

glm::vec3 GameObject::GetRotation() const
{
	return rotation;
}

glm::vec3 GameObject::GetScale() const
{
	return scale;
}

float GameObject::GetAngle() const
{
	return angle;

}

void GameObject::SetPosition(glm::vec3 position_)
{
	position = position_;
	if(model)
	{
		model->updateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTranfrom(modelInstance);
	}
}

void GameObject::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
	if (model)
	{
		model->updateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTranfrom(modelInstance);
	}
}

void GameObject::SetScale(glm::vec3 scale_)
{
	scale = scale_;
	if (model)
	{
		model->updateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTranfrom(modelInstance);
		boundingBox.minVert *= scale.x > 1.0f ? scale : (scale / 2.0f);
		boundingBox.maxVert *= scale.x > 1.0f ? scale : (scale / 2.0f);
	} 
}

void GameObject::SetAngle(float angle_)
{
	angle = angle_;
	if (model)
	{
		model->updateInstance(modelInstance, position, angle, rotation, scale);
	}
}


void GameObject::OnDestory()
{
	if (model)
	{
		delete model;
	}
	model = nullptr;
}


BoundingBox GameObject::getBoundingBox()
{
	return boundingBox;
}

void GameObject::Update(const float deltaTime_)
{
	SetAngle(GetAngle() + 0.005f);
}

void GameObject::setTag(std::string tag_)
{
	tag = tag_;
}

std::string GameObject::getTag()
{
	return tag;
}
