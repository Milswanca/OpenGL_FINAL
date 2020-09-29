#include "PCH.h"
#include "JsonConversionsMath.h"

#include "Math/Vector3.h"

void to_json(json& j, const Vector3& _v)
{
	j = json{ {"x", _v.x}, {"y", _v.y}, {"z", _v.z} };
}

void from_json(const json& j, Vector3& _v)
{
	j.at("x").get_to(_v.x);
	j.at("y").get_to(_v.y);
	j.at("z").get_to(_v.z);
}