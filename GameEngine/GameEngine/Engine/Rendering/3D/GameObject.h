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
	bool GetHit() const;

	BoundingBox getBoundingBox();
	void Update(const float deltaTime_);
	void setTag(std::string tag_);
	std::string getTag();
	void SetHit(bool hit_, int button_type);

private:
	Model* model;
	glm::vec3 position, rotation, scale;
	float angle;
	int modelInstance;
	BoundingBox boundingBox;
	std::string tag;
	bool hit;
};

#endif // !GAMEOBJECT_H
