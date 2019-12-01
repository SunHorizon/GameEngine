#include "GameScene.h"
#include "../../Engine/Rendering/SceneGraph.h"


GameScene::GameScene() : Scene()
{
	
}


GameScene::~GameScene()
{
	OnDestroy();
}

bool GameScene::OnCreate()
{
	CoreEngine::getInstance()->SetCamera(new Camera);
	CoreEngine::getInstance()->GetCamera()->setPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	CoreEngine::getInstance()->GetCamera()->addLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));
	CollisionHandler::GetInstance()->onCreate(100.0f);

	Model* model = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("BasicShader"));
	Model* model1 = new Model("Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("BasicShader"));
	
	SceneGraph::getInstance()->addModel(model);
	SceneGraph::getInstance()->addModel(model1);

	SceneGraph::getInstance()->addGameObject(new GameObject(model), "Apple");
	SceneGraph::getInstance()->addGameObject(new GameObject(model1), "Dice");

	if(!SceneGraph::getInstance()->GetGameObject("Apple") || !model)
	{
		return false;
	}
	if (!SceneGraph::getInstance()->GetGameObject("Dice") || !model1)
	{
		return false;
	}

	std::cout << "Creating Game Scene" << std::endl;
	std::vector<Vertex> vertexList;
	Vertex v;
	{
		/*	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
			v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
			v.texCoords = glm::vec2(0.0f, 0.0f);
			v.colour = glm::vec3(0.583f, 0.771f, 0.014f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, -0.5f, -0.5f);
			v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
			v.texCoords = glm::vec2(1.0f, 0.0f);
			v.colour = glm::vec3(0.609f, 0.115f, 0.436f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, 0.5f, -0.5f);
			v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
			v.texCoords = glm::vec2(1.0f, 1.0f);
			v.colour = glm::vec3(0.327f, 0.483f, 0.844f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, 0.5f, -0.5f);
			v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
			v.texCoords = glm::vec2(1.0f, 1.0f);
			v.colour = glm::vec3(0.822f, 0.569f, 0.201f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
			v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
			v.texCoords = glm::vec2(0.0f, 1.0f);
			v.colour = glm::vec3(0.435f, 0.602f, 0.223f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
			v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
			v.texCoords = glm::vec2(0.0f, 0.0f);
			v.colour = glm::vec3(0.310f, 0.747f, 0.185f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
			v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
			v.texCoords = glm::vec2(0.0f, 0.0f);
			v.colour = glm::vec3(0.597f, 0.770f, 0.761f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, -0.5f, 0.5f);
			v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
			v.texCoords = glm::vec2(1.0f, 0.0f);
			v.colour = glm::vec3(0.559f, 0.436f, 0.730f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, 0.5f, 0.5f);
			v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
			v.texCoords = glm::vec2(1.0f, 1.0f);
			v.colour = glm::vec3(0.359f, 0.583f, 0.152f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, 0.5f, 0.5f);
			v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
			v.texCoords = glm::vec2(1.0f, 1.0f);
			v.colour = glm::vec3(0.483f, 0.596f, 0.789f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
			v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
			v.texCoords = glm::vec2(0.0f, 1.0f);
			v.colour = glm::vec3(0.559f, 0.861f, 0.639f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
			v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
			v.texCoords = glm::vec2(0.0f, 0.0f);
			v.colour = glm::vec3(0.195f, 0.548f, 0.859f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
			v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
			v.texCoords = glm::vec2(0.0f, 0.0f);
			v.colour = glm::vec3(0.014f, 0.184f, 0.576f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
			v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
			v.texCoords = glm::vec2(1.0f, 0.0f);
			v.colour = glm::vec3(0.771f, 0.328f, 0.970f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
			v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
			v.texCoords = glm::vec2(1.0f, 1.0f);
			v.colour = glm::vec3(0.406f, 0.615f, 0.116f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
			v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
			v.texCoords = glm::vec2(1.0f, 1.0f);
			v.colour = glm::vec3(0.676f, 0.977f, 0.133f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
			v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
			v.texCoords = glm::vec2(0.0f, 1.0f);
			v.colour = glm::vec3(0.971f, 0.572f, 0.833f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
			v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
			v.texCoords = glm::vec2(0.0f, 0.0f);
			v.colour = glm::vec3(0.140f, 0.616f, 0.489f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, 0.5f, 0.5f);
			v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
			v.texCoords = glm::vec2(0.0f, 0.0f);
			v.colour = glm::vec3(0.997f, 0.513f, 0.064f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, 0.5f, -0.5f);
			v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
			v.texCoords = glm::vec2(1.0f, 0.0f);
			v.colour = glm::vec3(0.945f, 0.719f, 0.592f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, -0.5f, -0.5f);
			v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
			v.texCoords = glm::vec2(1.0f, 1.0f);
			v.colour = glm::vec3(0.543f, 0.021f, 0.978f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, -0.5f, -0.5f);
			v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
			v.texCoords = glm::vec2(1.0f, 1.0f);
			v.colour = glm::vec3(0.279f, 0.317f, 0.505f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, -0.5f, 0.5f);
			v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
			v.texCoords = glm::vec2(0.0f, 1.0f);
			v.colour = glm::vec3(0.167f, 0.620f, 0.077f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, 0.5f, 0.5f);
			v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
			v.texCoords = glm::vec2(0.0f, 0.0f);
			v.colour = glm::vec3(0.347f, 0.857f, 0.137f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
			v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
			v.texCoords = glm::vec2(0.0f, 0.0f);
			v.colour = glm::vec3(0.055f, 0.953f, 0.042f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, -0.5f, -0.5f);
			v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
			v.texCoords = glm::vec2(1.0f, 0.0f);
			v.colour = glm::vec3(0.714f, 0.505f, 0.345f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, -0.5f, 0.5f);
			v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
			v.texCoords = glm::vec2(1.0f, 1.0f);
			v.colour = glm::vec3(0.783f, 0.290f, 0.734f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, -0.5f, 0.5f);
			v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
			v.texCoords = glm::vec2(1.0f, 1.0f);
			v.colour = glm::vec3(0.722f, 0.645f, 0.174f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
			v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
			v.texCoords = glm::vec2(0.0f, 1.0f);
			v.colour = glm::vec3(0.302f, 0.455f, 0.848f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
			v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
			v.texCoords = glm::vec2(0.0f, 0.0f);
			v.colour = glm::vec3(0.225f, 0.587f, 0.040f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
			v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
			v.texCoords = glm::vec2(0.0f, 0.0f);
			v.colour = glm::vec3(0.517f, 0.713f, 0.338f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, 0.5f, -0.5f);
			v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
			v.texCoords = glm::vec2(1.0f, 0.0f);
			v.colour = glm::vec3(0.053f, 0.959f, 0.120f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, 0.5f, 0.5f);
			v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
			v.texCoords = glm::vec2(1.0f, 1.0f);
			v.colour = glm::vec3(0.393f, 0.621f, 0.362f);
			vertexList.push_back(v);

			v.position = glm::vec3(0.5f, 0.5f, 0.5f);
			v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
			v.texCoords = glm::vec2(1.0f, 1.0f);
			v.colour = glm::vec3(0.673f, 0.211f, 0.457f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
			v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
			v.texCoords = glm::vec2(0.0f, 1.0f);
			v.colour = glm::vec3(0.820f, 0.883f, 0.371f);
			vertexList.push_back(v);

			v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
			v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
			v.texCoords = glm::vec2(0.0f, 0.0f);
			v.colour = glm::vec3(0.982f, 0.099f, 0.879f);
			vertexList.push_back(v);*/

			//triangleModel_ = new Model(ShaderHandler::GetInstance()->GetShader("BasicShader"));
			//TextureHandler::getInstance()->CreateTexture("Checkerboard", "./Resources/Texture/CheckerboardTexture.png");
			//triangleModel_->AddMesh(new Mesh(&vertexList, ShaderHandler::GetInstance()->GetShader("BasicShader"), TextureHandler::getInstance()->GetTexture("Checkerboard")));

			//triangleModel_->SetScale(glm::vec3(1.0));

			//triangle = new GameObject(triangleModel_);

			//if(!triangle)
			//{
			//	Debug::Error("Triangle Failed to Create", __FILE__, __LINE__);
			//	OnDestroy();
			//	return  false;
			//}
	}

	//SceneGraph::getInstance()->GetGameObject("Apple")->SetPosition(glm::vec3(-3.0f, -1.0f, -6.0f));
	//SceneGraph::getInstance()->GetGameObject("Apple")->SetPosition(glm::vec3(-10.0f, -1.0f, -6.0f));
	//SceneGraph::getInstance()->GetGameObject("Apple")->SetScale(glm::vec3(0.5));

	//SceneGraph::getInstance()->GetGameObject("Dice")->SetPosition(glm::vec3(2.0f, -2.0f, -1.0f));
	//SceneGraph::getInstance()->GetGameObject("Dice")->SetScale(glm::vec3(0.5));


	SceneGraph::getInstance()->GetGameObject("Apple")->SetPosition(glm::vec3(-5.0f, -0.0f, -8.0f));
	SceneGraph::getInstance()->GetGameObject("Dice")->SetPosition(glm::vec3(4.0f, 0.0f, -2.0f));


	return true;
}

void GameScene::Update(const float deltaTime_)
{
	SceneGraph::getInstance()->Update(deltaTime_);
	if(!CheckFrustum())
	{
		//std::cout << "Apple is not visible" << std::endl;
	}
	else
	{
		//std::cout << "Apple is visible" << std::endl;;
	}
}

void GameScene::Render()
{
	SceneGraph::getInstance()->Render(CoreEngine::getInstance()->GetCamera());
}

bool GameScene::CheckFrustum()
{
	glm::vec3 objectTransform = SceneGraph::getInstance()->GetGameObject("Apple")->GetPosition();
	std::vector<glm::vec4> Planes = CoreEngine::getInstance()->GetCamera()->FrustumCulling();

	for (int i = 0; i < 6; i++) {
		if (Planes[i].x * objectTransform.x + Planes[i].y * objectTransform.y + Planes[i].z * objectTransform.z + Planes[i].w <= 0)
		{
			return false;
		}
	}
	return true;
}


void GameScene::OnDestroy()
{

}
