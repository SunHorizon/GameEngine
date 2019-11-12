#include "MaterialLoader.h"





void MaterialLoader::LoadMaterial(std::string file_)
{

	std::ifstream in(file_.c_str(), std::ios::in);
	if (!in)
	{
		Debug::Error("Cannot open MTL file" + file_, __FILE__, __LINE__);
	}
	Material m = Material();
	std::string matname = "";
	std::string line;
	while (std::getline(in, line))
	{
		if (line.substr(0, 7) == "newmtl ")
		{
			if(m.diffuceMap != 0)
			{
				Materialhandler::getInstance()->AddMaterial(matname, m);
				m = Material();
			}
			matname = line.substr(7);
			m.diffuceMap = LoadTexture(matname);
		}
		if (line.substr(0, 3) == "/tNs")
		{
			std::istringstream v(line.substr(3));
			float ns;
			v >> ns;
			m.shininess = ns;
		}
		if (line.substr(0, 3) == "/td")
		{
			std::istringstream v(line.substr(3));
			float d;
			v >> d;
			m.diffuse = d;
		}
	}
	if(m.diffuceMap != 0)
	{
		Materialhandler::getInstance()->AddMaterial(matname, m);
	}
}

GLuint MaterialLoader::LoadTexture(std::string file_)
{
	GLuint currentTexture = TextureHandler::getInstance()->GetTexture(file_);
	if (currentTexture == 0)
	{
		TextureHandler::getInstance()->CreateTexture(file_, "Resources/Texture/" + file_ + ".jpg");
		currentTexture = TextureHandler::getInstance()->GetTexture(file_);
	}
	return  currentTexture;
}

MaterialLoader::~MaterialLoader()
{
}
