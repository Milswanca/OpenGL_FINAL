#include "PCH.h"
#include "AssetLoader.h"
#include "File.h"

#include "Shader.h"
#include "Material.h"
#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

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

	std::vector<Vector3> verts;
	std::vector<Vector3> normals;
	std::vector<Vector4> colours;
	std::vector<int> indices;

	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (size_t i = 0; i < fv; i++) {
				indices.push_back(i + index_offset);

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

				verts.push_back(v);
				normals.push_back(n);
				colours.push_back(c);
			}
			index_offset += fv;

			// per-face material
			shapes[s].mesh.material_ids[f];
		}
	}

	Mesh* m = Mesh::Create(_outer, verts.data(), normals.data(), colours.data(), verts.size(), normals.size(), colours.size());

	for (int i = 0; i < shapes.size(); ++i)
	{
		m->SetIndices(i, indices.data(), indices.size());
	}

	return m;
}