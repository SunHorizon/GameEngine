#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <memory>
#include "3D/GameObject.h"

class SceneGraph
{
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator=(const SceneGraph&) = delete;
	SceneGraph& operator=(SceneGraph&&) = delete;

	// get engine instance
	static SceneGraph* getInstance();

	void addGameObject(GameObject* gameobject_, std::string name_ = "");
	void addModel(Model* model_);
	GameObject* GetGameObject(std::string name_);

	void Update(const float deltafloat_);
	void Render(Camera* camera_);
	void OnDestroy();


private:

	static  std::unique_ptr<SceneGraph> SceneGraphInstance;
	friend  std::default_delete<SceneGraph>;

	static std::map<std::string, GameObject*> sceneGameObject;
	static std::map<GLuint, std::vector<Model*>> sceneModels;


	SceneGraph();
	~SceneGraph();
};
#endif //!SCENEGRAPH_H

