#ifndef TextureHandler_H
#define TextureHandler_H

#include <memory>
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <glew.h>

#include "../Core/Debug.h"

struct  Texture
{
	GLuint textureID = 0;
	float width = 0.0f;
	float height = 0.0;

};

class TextureHandler
{
public:

	TextureHandler(const TextureHandler&) = delete;
	TextureHandler(TextureHandler&&) = delete;
	TextureHandler& operator=(const TextureHandler&) = delete;
	TextureHandler& operator=(TextureHandler&&) = delete;

	
	static TextureHandler* getInstance();
	void OnDestory();
	bool CreateTexture(const std::string& textureName_, const std::string& textureFileName_);
	static const GLuint GetTexture(const std::string& textureName_);
	static const Texture* GetTextureData(const std::string& textureName_);

private:

	TextureHandler();
	~TextureHandler();

	static  std::unique_ptr<TextureHandler> textureInstance;
	friend  std::default_delete<TextureHandler>;
	static std::map<std::string, Texture*> textures;

};

#endif // !TextureHandler_H