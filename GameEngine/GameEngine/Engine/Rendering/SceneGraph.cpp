#include "SceneGraph.h"


std::unique_ptr<SceneGraph> SceneGraph::SceneGraphInstance = nullptr;
std::map<std::string, GameObject*> SceneGraph::sceneGameObject = std::map<std::string, GameObject*>();
std::map<GLuint, std::vector<Model*>> SceneGraph::sceneModels = std::map<GLuint, std::vector<Model*>>();


SceneGraph::SceneGraph()
{
}


SceneGraph* SceneGraph::getInstance()
{
	if (SceneGraphInstance.get() == nullptr)
	{
		SceneGraphInstance.reset(new SceneGraph);
	}
	return SceneGraphInstance.get();
}

void SceneGraph::addGameObject(GameObject* gameobject_, std::string name_)
{
	if(name_ == "")
	{
		std::string newName = "GameObject" + std::to_string(sceneGameObject.size() + 1);
		gameobject_->setTag(newName);
		sceneGameObject[newName] = gameobject_;
	}
	else if(sceneGameObject.find(name_) == sceneGameObject.end())
	{
		gameobject_->setTag(name_);
		sceneGameObject[name_] = gameobject_;
	}
	else
	{
		Debug::Error("Trying to add a GameObject with the name " + name_ +
			" the already exist", __FILE__, __LINE__);

		std::string newName = "GameObject" + std::to_string(sceneGameObject.size() + 1);
		gameobject_->setTag(newName);
		sceneGameObject[newName] = gameobject_;
	}
}

void SceneGraph::addModel(Model* model_)
{
	if(sceneModels.find(model_->GetShaderProgram()) == sceneModels.end())
	{
		sceneModels.insert(std::pair<GLuint, std::vector<Model*>>
			(model_->GetShaderProgram(), std::vector<Model*>{model_}));
	}
	else
	{
		sceneModels[model_->GetShaderProgram()].push_back(model_);
	}
}

GameObject* SceneGraph::GetGameObject(std::string name_)
{
	if(sceneGameObject.find(name_) != sceneGameObject.end())
	{
		return sceneGameObject[name_];
	}
	return nullptr;
}

void SceneGraph::Update(const float deltafloat_)
{
	for(auto go : sceneGameObject)
	{
		go.second->Update(deltafloat_);
	}
}

void SceneGraph::Render(Camera* camera_)
{
	for(auto entry : sceneModels)
	{
		glUseProgram(entry.first);
		for(auto m : entry.second)
		{
			m->Render(camera_);
		}
	}
}

void SceneGraph::OnDestroy()
{
	if(sceneGameObject.size() > 0)
	{
		for(auto go : sceneGameObject)
		{
			delete go.second;
			go.second =  nullptr;
		}
		sceneGameObject.clear();
	}

	if (sceneModels.size() > 0)
	{
		for (auto entry : sceneModels)
		{
			if(entry.second.size() > 0)
			{
				for(auto m : entry.second)
				{
					delete m;
					m = nullptr;
				}
				entry.second.clear();
			}
		
		}
		sceneModels.clear();
	}
}


SceneGraph::~SceneGraph()
{
	OnDestroy();
}
