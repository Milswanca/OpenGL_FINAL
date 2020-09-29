#pragma once
#include "Object.h"

class Asset;
class Serializer;

typedef void (*ImportAssetSignature)(std::string _file, std::string _output);

class ObjImporter
{
public:
	static void ImportAsset(std::string _file, std::string _output);

	struct MeshData
	{
	public:
		std::vector<Vector3> verts;
		std::vector<Vector3> normals;
		std::vector<Vector4> colours;
		std::vector<std::vector<int>> indices;

		friend Serializer& operator<<(Serializer& _s, const MeshData& _m);
		friend Serializer& operator>>(Serializer& _s, MeshData& _m);
	};
};

class MaterialImporter
{
public:
	static void ImportAsset(std::string _file, std::string _output);
};

class AssetImporter : public Object
{
public:
	//TODO: Somehow generate this from preprocessor macros
	static std::map<std::string, ImportAssetSignature> create_map()
	{
		std::map<std::string, ImportAssetSignature> m;
		m["obj"] = ObjImporter::ImportAsset;
		m["mtl"] = MaterialImporter::ImportAsset;
		return m;
	}
	static const std::map<std::string, ImportAssetSignature> importFunctions;

	static void ImportAsset(std::string _file, std::string _output)
	{
		std::string extension = _file.substr(_file.find_last_of(".") + 1);
		AssetImporter::importFunctions.at(extension)(_file, _output);
	}
};