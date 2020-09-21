#pragma once
#include "Object.h"

class Shader;

class Material : public Object
{
public:
	Material(const ObjectInitData& _data);
	~Material();

	static Material* Create(Object* _ref, Shader* _shader);

	void SetInt(const char* _name, const int _value);
	void SetFloat(const char* _name, const float _value);
	void SetVector3(const char* _name, const Vector3& _value);
	void SetVector4(const char* _name, const Vector4& _value);
	void SetMatrix(const char* _name, const Matrix4x4& _value);

	void SetShader(Shader* _shader);
	void Bind();

private:
	Shader* m_shader;
};

