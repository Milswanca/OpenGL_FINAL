#pragma once
#include "Object.h"

struct MeshShape;

class Mesh : public Object
{
public:
	Mesh(const ObjectInitData& _data);

	static Mesh* Create(Object* _outer);
	static Mesh* Create(Object* _outer, Vector3* _verts, Vector3* _normals, Vector4* _colours, int _numVerts, int _numNormals, int _numColours);

	void RebuildVertices();
	void SetIndices(int _meshIndex, int* _indices, int _numIndices);

	int GetNumShapes() const;
	unsigned int GetVAO() const;
	unsigned int GetEBO(int _shape) const;
	unsigned int GetNumIndices(int _shape) const;

private:
	Vertex* verts;
	Vector3* p;
	Vector3* n;
	Vector4* c;
	int numVerts;
	int numNormals;
	int numColours;

	unsigned int VBO;
	unsigned int VAO;

	struct MeshShape
	{
	public:
		int* indices;
		int numIndices;
		unsigned int EBO;
	};

	std::vector<MeshShape> shapes;
};

