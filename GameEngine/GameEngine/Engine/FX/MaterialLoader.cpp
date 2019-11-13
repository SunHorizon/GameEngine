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
		if (line.substr(0, 3) == "\tNs")
		{
			std::istringstream v(line.substr(3));
			float ns;
			v >> ns;
			m.shininess = ns;
		}
		if (line.substr(0, 2) == "\td")
		{
			std::istringstream v(line.substr(2));
			float d;
			v >> d;
			m.transparency = d;
		}
		if (line.substr(0, 3) == "\tKa")
		{
			std::istringstream v(line.substr(3));
			double x, y, z;
			v >> x >> y >> z;
			m.ambient = glm::vec3(x, y, z);
		}
		if (line.substr(0, 3) == "\tKd")
		{
			std::istringstream v(line.substr(3));
			double x, y, z;
			v >> x >> y >> z;
			m.diffuse = glm::vec3(x, y, z);
		}
		if (line.substr(0, 3) == "\tKs")
		{
			std::istringstream v(line.substr(3));
			double x, y, z;
			v >> x >> y >> z;
			m.specular = glm::vec3(x, y, z);
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
