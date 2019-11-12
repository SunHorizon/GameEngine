#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"

class GameObject
{
public:

	GameObject(Model* model);
	GameObject(Model* model, glm::vec3 position_);
	~GameObject();
	void Render(Camera* camera);
	void OnDestory();

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	float GetAngle() const;

	void SetPosition(glm::vec3 position_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetAngle(float angle_);

	BoundingBox getBoundingBox();
	void Update(const float deltaTime_);
	void setTag(std::string tag_);
	std::string getTag();

private:
	Model* model;
	glm::vec3 position, rotation, scale;
	float angle;
	int modelInstance;
	BoundingBox boundingBox;
	std::string tag;
};

#endif // !GAMEOBJECT_H
