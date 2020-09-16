#pragma once
#include "Math.h"

class Object;
class Engine;

enum class ShaderTypes
{
	Vertex,
	Pixel
};

struct ObjectInitData
{
public:
	Engine* engine;
	Object* outer;
};

struct Vertex
{
public:
	Vector3 position;
	Vector3 normal;
	Vector4 colour;
};