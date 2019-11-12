#include "Materialhandler.h"
#include "../Core/Debug.h"

std::unique_ptr<Materialhandler> Materialhandler::MaterialHandlerInstance = nullptr;
std::map <std::string, Material> Materialhandler::materials = std::map <std::string, Material>();


Materialhandler::Materialhandler()
{

}

Materialhandler* Materialhandler::getInstance()
{
	if (MaterialHandlerInstance.get() == nullptr)
	{
		MaterialHandlerInstance.reset(new Materialhandler);
	}
	return MaterialHandlerInstance.get();
}

void Materialhandler::AddMaterial(const std::string& name_, Material mat_)
{
	materials[name_] = mat_;
}

const Material Materialhandler::GetMaterial(const std::string& name_)
{
	if(materials.find(name_) != materials.end())
	{
		return materials[name_];
	}
	Debug::Error("trying to get material" + name_ + " which does not exist", __FILE__, __LINE__);
	return Material();
}

Materialhandler::~Materialhandler()
{
	OnDestroy();
}

void Materialhandler::OnDestroy()
{
	if(materials.size() > 0)
	{
		materials.clear();
	}
}