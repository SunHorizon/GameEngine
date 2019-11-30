#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "CollisionDetection.h"
#include "Ray.h"
#include "../Rendering/3D/GameObject.h"
#include "../Core/OctSpatrialPartiton.h"


class CollisionHandler
{
public:
	CollisionHandler(const CollisionHandler&) = delete;
	CollisionHandler(CollisionHandler&&) = delete;
	CollisionHandler& operator=(const CollisionHandler&) = delete;
	CollisionHandler& operator=(CollisionHandler&&) = delete;

	static CollisionHandler* GetInstance();

	void onCreate(float worldSize_);
	void AddObject(GameObject* gameObject);
	void update(glm::vec2 mousePosition, int buttonType_);
	void OnDestroy();


private:
	CollisionHandler();
	~CollisionHandler();

	static std::unique_ptr<CollisionHandler> collisionInstance;
	friend std::default_delete<CollisionHandler>;
	static std::vector<GameObject*> prevCollisions;
	static OctSpatrialPartiton* scenePartition;

};

#endif // !COLLISIONHANDLER_H