#pragma once
#include "Math/Matrix4x4.h"
#include "Math/Vector4.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include "Math/JsonConversionsMath.h"

static const float PI = 3.14159265359f;

class Math
{
public:
	static float ToRadians(const float _degrees);
};
