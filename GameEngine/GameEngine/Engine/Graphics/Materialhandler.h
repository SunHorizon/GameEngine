#ifndef MATERIALHANDLER_H
#define MATERIALHANDLER_H

#include <glm/glm.hpp>
#include <glew.h>
#include <memory>
#include <map>
#include <string>

struct Material
{
	GLuint diffuceMap;
	float shininess; //NS
	float transparency; //D

	glm::vec3 ambient; //Ka
	glm::vec3 diffuse; //Kd
	glm::vec3 specular; //Ks

	inline Material()
	{
		diffuceMap = 0;
		shininess = 0.0f;
		transparency = 0.0f;

		ambient = glm::vec3(1.0f);
		diffuse = glm::vec3(1.0f);
		specular = glm::vec3();

	}
};

class Materialhandler
{
public:

	Materialhandler(const Materialhandler&) = delete;
	Materialhandler(Materialhandler&&) = delete;
	Materialhandler& operator=(const Materialhandler&) = delete;
	Materialhandler& operator=(Materialhandler&&) = delete;

	static Materialhandler* getInstance();
	void AddMaterial(const std::string& name_, Material mat_);
	const Material GetMaterial(const std::string& name_);
	void OnDestroy();

private:
	Materialhandler();
	~Materialhandler();

	static  std::unique_ptr<Materialhandler> MaterialHandlerInstance;
	friend  std::default_delete<Materialhandler>;

	static std::map <std::string, Material> materials;
};

#endif //!MATERIALHANDLER_H
