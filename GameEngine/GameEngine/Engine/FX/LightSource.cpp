#include "LightSource.h"



LightSource::LightSource(glm::vec3 position_, float ambient_, float diffuse_, glm::vec3 lightColor_)
{
	position = position_;
	ambient = ambient_;
	diffuse = diffuse_;
	lightColor = lightColor_;
}


LightSource::~LightSource()
{

}

glm::vec3 LightSource::getPosition()
{
	return position;
}

float LightSource::getAmbient()
{
	return ambient;
}

float LightSource::getDiffuse()
{
	return diffuse;
}

glm::vec3 LightSource::GetlightColor()
{
	return lightColor;
}

void LightSource::SetPosition(glm::vec3 position_)
{
	position = position_;
}

void LightSource::SetAmbient(float ambient_)
{
	ambient = ambient_;
}

void LightSource::SetDiffuse(float diffuse_)
{
	diffuse = diffuse_;
}

void LightSource::SetlightColor(glm::vec3 lightColor_)
{
	lightColor = lightColor_;
}
