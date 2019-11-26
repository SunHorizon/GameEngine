#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"


std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();
OctSpatrialPartiton* CollisionHandler::scenePartition = nullptr;


CollisionHandler::CollisionHandler()
{
}


CollisionHandler* CollisionHandler::GetInstance()
{
	if(collisionInstance.get() == nullptr)
	{
		collisionInstance.reset(new CollisionHandler);
	}
	return  collisionInstance.get();
}

void CollisionHandler::onCreate(float worldSize_)
{
	prevCollisions.clear();
	scenePartition = new OctSpatrialPartiton(worldSize_);

}

void CollisionHandler::AddObject(GameObject* gameObject)
{
	scenePartition->AddObject(gameObject);
}

void CollisionHandler::update(glm::vec2 mousePosition, int buttonType_)
{
	Ray mouseRay = CollisionDetection::ScreenPosToWorldRay(mousePosition, CoreEngine::getInstance()->GetScreenSize(), CoreEngine::getInstance()->GetCamera());
	
	if(scenePartition != nullptr)
	{
		GameObject* hitResult = scenePartition->GetCollision(mouseRay);

		if(hitResult)
		{
			hitResult->SetHit(true, buttonType_);

			for(auto c : prevCollisions)
			{
				if(hitResult != c && c!= nullptr)
				{
					c->SetHit(false, buttonType_);
				}
			}
			prevCollisions.clear();

			if (hitResult)
			{
				prevCollisions.push_back(hitResult);
			}
		}
	}
}

void CollisionHandler::OnDestroy()
{
	delete scenePartition;
	scenePartition = nullptr;

	if (!prevCollisions.empty())
	{
		for (auto go : prevCollisions)
		{
			go = nullptr;
		}
		prevCollisions.clear();
	}
}

CollisionHandler::~CollisionHandler()
{
	OnDestroy();
}
