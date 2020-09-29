#pragma once
#include "Math.h"

class Object;
class Engine;
class Scene;

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
	Scene* scene;
};

struct Vertex
{
public:
	Vector3 position;
	Vector3 normal;
	Vector4 colour;
};

enum MouseButtons
{
	Left = 0,
	Middle = 1,
	Right = 2
};