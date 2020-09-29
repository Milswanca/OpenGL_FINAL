#pragma once
#include "json.hpp"

struct Vector3;

void to_json(nlohmann::json& _j, const Vector3& _v);
void from_json(nlohmann::json& _j, const Vector3& _v);