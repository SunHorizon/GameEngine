#ifndef MATERIALLOADER_H
#define MATERIALLOADER_H

#include "../Graphics/Materialhandler.h"
#include "../Graphics/TextureHandler.h"
#include <sstream>

class MaterialLoader
{
public:
	MaterialLoader(const MaterialLoader&) = delete;
	MaterialLoader(MaterialLoader&&) = delete;
	MaterialLoader& operator=(const MaterialLoader&) = delete;
	MaterialLoader& operator=(MaterialLoader&&) = delete;

	static void LoadMaterial(std::string file_);
	static GLuint LoadTexture(std::string file_);

	 MaterialLoader() = delete;
	 ~MaterialLoader();
	
};
#endif //!MATERIALLOADER_H
