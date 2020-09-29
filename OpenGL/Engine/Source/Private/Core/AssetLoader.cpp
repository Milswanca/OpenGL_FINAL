#include "PCH.h"
#include "AssetLoader.h"
#include "File.h"

#include "Shader.h"
#include "Material.h"
#include "Mesh.h"

#include "StaticHelpers.h"
#include "AssetImporter.h"

#include "Serialization.h"

Material* AssetLoader::LoadMaterial(Object* _outer, std::string _file)
{
	json json = json::parse(File::LoadFileToString(_file.c_str()));
	std::string vs = json["VS"].get<std::string>();
	std::string ps = json["PS"].get<std::string>();

	Shader* shader = Shader::Create(_outer, vs.c_str(), ps.c_str());
	Material* material = Material::Create(_outer, shader);

	return material;
}

Mesh* AssetLoader::LoadObj(Object* _outer, std::string _file)
{
	ObjImporter::MeshData data;

	Serializer serializer;
	serializer.Open(_file.c_str());
	serializer >> data;
	serializer.Close();

	Mesh* m = Mesh::Create(_outer, data.verts.data(), data.normals.data(), data.colours.data(), data.verts.size(), data.normals.size(), data.colours.size());

	for (int i = 0; i < data.indices.size(); ++i)
	{
		m->SetIndices(i, data.indices[i].data(), data.indices[i].size());
	}

	return m;
}