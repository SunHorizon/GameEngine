#ifndef LOADOBJMODEL_H
#define LOADOBJMODEL_H

#include "Mesh.h."
#include "../../Graphics/TextureHandler.h"
#include <sstream>
#include "../../Math/BoundingBox.h"
#include "../../FX/MaterialLoader.h"

class LoadObjModel
{
public:
	LoadObjModel();
	~LoadObjModel();
	void LoadModel(const std::string& fileName_);
	void LoadModel(const std::string& fileName_, const std::string& matName);
	std::vector<Vertex> GetVertex();
	std::vector<int> GetIndices();
	std::vector<SubMesh> GetSubMeshes();
	void OnDestroy();

	BoundingBox getBoundingBox();

private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textCoords;

	std::vector<int> normalIndices;
	std::vector<int> textureIndices;
	std::vector<int> indices;

	std::vector<Vertex> meshVertices;
	std::vector<SubMesh> meshes;

	void PostProcessing();
	void LoadMaterial(const std::string& fileName_);
	void LoadMaterialLibrary(const std::string& matName);

	BoundingBox boundingBox;
	Material currentMaterial;
};

#endif //!LOADOBJMODEL_H
