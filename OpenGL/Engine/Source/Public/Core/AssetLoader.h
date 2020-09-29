#pragma once
#include "Object.h"

class Mesh;
class Shader;
class Material;

class AssetLoader
{
public:
	template<typename T>
	static T* LoadAsset(Object* _outer, std::string _file)
	{
		std::string extension = _file.substr(_file.find_last_of(".") + 1);

		if (extension == "mesh")
		{
			return reinterpret_cast<T*>(LoadObj(_outer, _file));
		}
		else if (extension == "mat")
		{
			return reinterpret_cast<T*>(LoadMaterial(_outer, _file));
		}
	}

	static Material* LoadMaterial(Object* _outer, std::string _file);
	static Mesh* LoadObj(Object* _outer, std::string _file);
};