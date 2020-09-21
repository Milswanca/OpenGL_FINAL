#include "PCH.h"
#include "Mesh.h"

#include "Engine.h"

Mesh::Mesh(const ObjectInitData& _data) : Object(_data)
{
	verts = nullptr;
	p = nullptr;
	n = nullptr;
	c = nullptr;
	numVerts = 0;
	shapes = std::vector<MeshShape>();
}

Mesh* Mesh::Create(Object* _outer, Vector3* _verts, Vector3* _normals, Vector4* _colours, int _numVerts, int _numNormals, int _numColours)
{
	Mesh* mesh = _outer->GetEngine()->NewObject<Mesh>(_outer);
	mesh->p = new Vector3[_numVerts];
	mesh->n = new Vector3[_numNormals];
	mesh->c = new Vector4[_numColours];
	mesh->numVerts = _numVerts;
	mesh->numNormals = _numNormals;
	mesh->numColours = _numColours;

	std::memcpy(mesh->p, _verts, sizeof(Vector3) * _numVerts);
	std::memcpy(mesh->n, _normals, sizeof(Vector3) * _numNormals);
	std::memcpy(mesh->c, _colours, sizeof(Vector4) * _numColours);

	mesh->RebuildVertices();

	return mesh;
}

void Mesh::RebuildVertices()
{
	if (verts != nullptr)
	{
		delete[] verts;
		verts = nullptr;
	}

	verts = new	Vertex[numVerts];

	for (int i = 0; i < numVerts; ++i)
	{
		verts[i].position = p[i];

		if (numColours > i)
		{
			verts[i].colour = c[i];
		}

		if (numNormals > i)
		{
			verts[i].normal = n[i];
		}
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, numVerts * sizeof(Vertex), &verts[0], GL_STATIC_DRAW);
	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex colours
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
	glBindVertexArray(0);
}

void Mesh::SetIndices(int _meshIndex, int* _indices, int _numIndices)
{
	while (_meshIndex >= shapes.size())
	{
		MeshShape shape = MeshShape();
		shape.indices = nullptr;
		shape.numIndices = 0;

		shapes.push_back(shape);
	}

	if (shapes[_meshIndex].indices != nullptr)
	{
		delete[] shapes[_meshIndex].indices;
		shapes[_meshIndex].indices = nullptr;
	}

	MeshShape shape = shapes[_meshIndex];
	shape.indices = new int[_numIndices];
	shape.numIndices = _numIndices;
	std::memcpy(shape.indices, _indices, _numIndices * sizeof(int));

	glBindVertexArray(VAO);
	glGenBuffers(1, &shape.EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape.EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numIndices * sizeof(unsigned int), &shape.indices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);

	shapes[_meshIndex] = shape;
}

int Mesh::GetNumShapes() const
{
	return shapes.size();
}

unsigned int Mesh::GetVAO() const
{
	return VAO;
}

unsigned int Mesh::GetEBO(int _shape) const
{
	return shapes[_shape].EBO;
}

unsigned int Mesh::GetNumIndices(int _shape) const
{
	return shapes[_shape].numIndices;
}