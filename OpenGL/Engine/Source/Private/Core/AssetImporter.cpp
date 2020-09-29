#include "PCH.h"
#include "AssetImporter.h"
#include "StaticHelpers.h"
#include "zLib/zlib.h"
#include "Serialization.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <json.hpp>
using json = nlohmann::json;

const std::map<std::string, ImportAssetSignature> AssetImporter::importFunctions = AssetImporter::create_map();

void ObjImporter::ImportAsset(std::string _file, std::string _output)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, _file.c_str());

	if (!warn.empty()) {
		std::cout << warn << std::endl;
	}

	if (!err.empty()) {
		std::cerr << err << std::endl;
	}

	MeshData data;

	// Loop over shapes
	int totalIndexOffset = 0;
	for (size_t s = 0; s < shapes.size(); s++) {

		std::vector<int> indices;
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (size_t i = 0; i < fv; i++) {
				indices.push_back(i + totalIndexOffset);

				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + i];
				tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
				tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
				tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
				tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
				tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
				tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
				tinyobj::real_t red = attrib.colors[3 * idx.vertex_index + 0];
				tinyobj::real_t green = attrib.colors[3 * idx.vertex_index + 1];
				tinyobj::real_t blue = attrib.colors[3 * idx.vertex_index + 2];

				Vector3 v = Vector3(vx, vy, vz);
				Vector3 n = Vector3(nx, ny, nz);
				Vector3 c = Vector4(red, green, blue, 1.0f);

				data.verts.push_back(v);
				data.normals.push_back(n);
				data.colours.push_back(c);
			}
			index_offset += fv;
			totalIndexOffset += fv;

			// per-face material
			shapes[s].mesh.material_ids[f];

		}

		if (indices.size() > 0)
		{
			data.indices.push_back(indices);
		}
	}

	Serializer stream;
	stream << data;
	stream.SaveToFile(_output.c_str());
	stream.Close();
}

Serializer& operator<<(Serializer& _s, const ObjImporter::MeshData& _m)
{
	_s << _m.verts;
	_s << _m.normals;
	_s << _m.colours;

	_s << _m.indices.size();
	for (int i = 0; i < _m.indices.size(); ++i)
	{
		_s << _m.indices[i];
	}

	return _s;
}

Serializer& operator>>(Serializer& _s, ObjImporter::MeshData& _m)
{
	_s >> _m.verts;
	_s >> _m.normals;
	_s >> _m.colours;

	int size = 0;
	_s >> size;
	for (int i = 0; i < size; ++i)
	{
		std::vector<int> indices;
		_s >> indices;
		_m.indices.push_back(indices);
	}
	return _s;
}

void MaterialImporter::ImportAsset(std::string _file, std::string _output)
{

}