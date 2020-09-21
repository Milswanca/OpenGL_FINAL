#pragma once
#include "Object.h"

class Asset;

typedef void (*ImportAssetSignature)(std::string param);

class ObjImporter
{
public:
	static void ImportAsset(std::string _file);
};

class MaterialImporter
{
public:
	static void ImportAsset(std::string _file);
};

class AssetImporter : public Object
{
public:
	//TODO: Somehow generate this from preprocessor macros
	const std::map<std::string, ImportAssetSignature> importFunctions = 
	{
		{"obj", ObjImporter::ImportAsset },
		{"mtl", MaterialImporter::ImportAsset }
	};

	void ImportAsset(std::string _file)
	{
		std::string extension = _file.substr(_file.find_last_of(".") + 1);
		importFunctions.at(extension)(_file);
	}
};