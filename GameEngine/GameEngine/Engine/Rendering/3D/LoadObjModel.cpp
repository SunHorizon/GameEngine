#include "LoadObjModel.h"



LoadObjModel::LoadObjModel() : vertices(std::vector<glm::vec3>()), normals(std::vector<glm::vec3>()), textCoords(std::vector<glm::vec2>()), normalIndices(std::vector<int>()), textureIndices(std::vector<int>()), meshVertices(std::vector<Vertex>()), meshes(std::vector<SubMesh>()), currentMaterial(Material())
{
	
}


LoadObjModel::~LoadObjModel()
{
	OnDestroy();
}

//void LoadObjModel::LoadModel(const std::string& fileName_)
//{
//	std::ifstream in(fileName_.c_str(), std::ios::in);
//	if(!in)
//	{
//		Debug::Error("Cannot load OBJ file " + fileName_, __FILE__, __LINE__);
//		return;
//	}
//	std::string line;
//	while (std::getline(in, line))
//	{
//		// VERTEX DATA
//		if (line.substr(0, 2) == "v ")
//		{
//			std::istringstream v(line.substr(2));
//			glm::vec3 vert;
//			double x, y, z;
//			v >> x >> y >> z;
//			vert = glm::vec3(x, y, z);
//			vertices.push_back(vert);
//		}
//
//		// NORMAL DATA
//		else if (line.substr(0, 3) == "vn ")
//		{
//			std::istringstream vn(line.substr(2));
//			glm::vec3 vert;
//			double x, y, z;
//			vn >> x >> y >> z;
//			vert = glm::vec3(x, y, z);
//			normals.push_back(vert);
//		}
//
//		// TEXTURE COORDINAITE DATA
//		else if (line.substr(0, 3) == "vt ")
//		{
//			std::istringstream vt(line.substr(2));
//			glm::vec2 vert;
//			double x, y;
//			vt >> x >> y;
//			vert = glm::vec2(x, y);
//			textCoords.push_back(vert);
//		}
//		// FACE DATA
//		// Vertex indicies/texture indices/normal indices
//		else if (line.substr(0, 2) == "f ")
//		{
//			std::istringstream f(line.substr(2));
//			unsigned int vertexIndex[3], textureIndex[3], normalIndex[3];
//
//			char c;
//			f >> vertexIndex[0] >> c >> textureIndex[0] >> c >> normalIndex[0] >> vertexIndex[1] >> c >> textureIndex[1] >> c >> normalIndex[1] >> vertexIndex[2] >> c >> textureIndex[2] >> c >> normalIndex[2];
//
//			std::cout << vertexIndex[0] << textureIndex[0] << normalIndex[0] << vertexIndex[1] << textureIndex[1] << normalIndex[1] << vertexIndex[2] << textureIndex[2] << normalIndex[2] << std::endl;
//
//			indices.push_back(vertexIndex[0] - 1);
//			indices.push_back(vertexIndex[1] - 1);
//			indices.push_back(vertexIndex[2] - 1);
//			textureIndices.push_back(textureIndex[0] - 1);
//			textureIndices.push_back(textureIndex[1] - 1);
//			textureIndices.push_back(textureIndex[2] - 1);
//			normalIndices.push_back(normalIndex[0] - 1);
//			normalIndices.push_back(normalIndex[1] - 1);
//			normalIndices.push_back(normalIndex[2] - 1);;
//		}
//
//
//		// NEW MATERAL (new mesh)
//		else if (line.substr(0, 7) == "usemtl ")
//		{
//			if (indices.size() > 0)
//			{
//				PostProcessing();
//			}
//			LoadModel(line.substr(7));
//		}
//	}
//	PostProcessing();
//}


void LoadObjModel::LoadModel(const std::string& filename_)
{
	double minX, minY, minZ, maxX, maxY, maxZ;
	minX = std::numeric_limits<float>::max(); minY = std::numeric_limits<float>::max();  minZ = std::numeric_limits<float>::max(); maxX = std::numeric_limits<float>::min();  maxY = std::numeric_limits<float>::min(); maxZ = std::numeric_limits<float>::min();
	
	std::ifstream in(filename_.c_str(), std::ios::in);
	if (!in)
	{
		Debug::Error("Cannot open OBJ file: " + filename_, __FILE__, __LINE__);
		return;
	}
	std::string line;
	while (std::getline(in, line))
	{
		//Vertex data
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream v(line.substr(2));
			glm::vec3 vert;
			double x, y, z;
			v >> x >> y >> z;
			vert = glm::vec3(x, y, z);
			vertices.push_back(vert);
			if(minX > x)
			{
				minX  = x;
			}
			if (minY > y)
			{
				minY = y;
			}
			if (minZ > z)
			{
				minZ = z;
			}
			if (maxX < x)
			{
				maxX = x;
			}
			if (maxY < y)
			{
				maxY = y;
			}
			if (maxZ < z)
			{
				maxZ = z;
			}
		}

		if (line.substr(0, 3) == "vn ")
		{
			std::istringstream v(line.substr(3));
			glm::vec3 normal;
			double x, y, z;
			v >> x >> y >> z;
			normal = glm::vec3(x, y, z);
			normals.push_back(normal);
		}
		
		if (line.substr(0, 3) == "vt ")
		{
			std::istringstream v(line.substr(3));
			glm::vec2 textureCoord;
			double x, y;
			v >> x >> y;
			textureCoord = glm::vec2(x, y);
			textCoords.push_back(textureCoord);
		}
		//TODO: Face data
		//vertex indices/texture indices/normal indices
		if (line.substr(0, 2) == "f ")
		{
			unsigned int vertexIndex[3], textureIndex[3], normalIndex[3];
			char c;
			std::istringstream v(line.substr(2));
			
			v >> vertexIndex[0] >> c >> textureIndex[0] >> c >> normalIndex[0] >> vertexIndex[1] >> c >> textureIndex[1] >> c >> normalIndex[1] >> vertexIndex[2] >> c >> textureIndex[2] >> c >> normalIndex[2];
			
			indices.push_back(vertexIndex[0] - 1);
			indices.push_back(vertexIndex[1] - 1);
			indices.push_back(vertexIndex[2] - 1);
			textureIndices.push_back(textureIndex[0] - 1);
			textureIndices.push_back(textureIndex[1] - 1);
			textureIndices.push_back(textureIndex[2] - 1);
			normalIndices.push_back(normalIndex[0] - 1);
			normalIndices.push_back(normalIndex[1] - 1);
			normalIndices.push_back(normalIndex[2] - 1);
		}

		//new material
		else if (line.substr(0, 7) == "usemtl ")
		{
			if (indices.size() > 0)
			{
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}

	}
	boundingBox.minVert = glm::vec3(minX, minY, minZ);
	boundingBox.maxVert = glm::vec3(maxX, maxY, maxZ);

	std::cout << "Min Vert: (" << minX << ",   " << minY << ",   " << minZ << ")" <<std::endl;
	std::cout << "Max Vert: (" << maxX << ",   " << maxY << ",   " << maxZ << ")" << std::endl;

	PostProcessing();
}

void LoadObjModel::LoadModel(const std::string& fileName_, const std::string& matName)
{
	LoadMaterialLibrary(matName);
	LoadModel(fileName_);
}

std::vector<Vertex> LoadObjModel::GetVertex()
{
	return meshVertices;
}

std::vector<int> LoadObjModel::GetIndices()
{
	return indices;
}

std::vector<SubMesh> LoadObjModel::GetSubMeshes()
{
	return  meshes;
}

void LoadObjModel::OnDestroy()
{
	vertices.clear();
	normals.clear();
	textCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	meshes.clear();
}

void LoadObjModel::PostProcessing()
{
	for(int i = 0; i < indices.size(); i++)
	{
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.texCoords = textCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;
	meshes.push_back(mesh);
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	currentMaterial = Material();
}

void LoadObjModel::LoadMaterial(const std::string& fileName_)
{
	currentMaterial = Materialhandler::getInstance()->GetMaterial(fileName_);
}

void LoadObjModel::LoadMaterialLibrary(const std::string& matName)
{
	MaterialLoader::LoadMaterial(matName);
}


BoundingBox LoadObjModel::getBoundingBox()
{
	return  boundingBox;
}

