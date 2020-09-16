#include "PCH.h"
#include "Material.h"
#include "Shader.h"

#include "Engine.h"

Material::Material(const ObjectInitData& _data) : Object(_data)
{
	m_shader = nullptr;
}

Material::~Material()
{

}

Material* Material::Create(Object* _ref, Shader* _shader)
{
	Material* mat = _ref->GetEngine()->NewObject<Material>(_ref);
	mat->SetShader(_shader);

	return mat;
}

void Material::SetVector3(const char* _name, const Vector3& _value)
{
	unsigned int val = glGetUniformLocation(m_shader->GetProgram(), _name);
	glUniform3fv(val, 1, &_value.x);
}

void Material::SetVector4(const char* _name, const Vector4& _value)
{
	unsigned int val = glGetUniformLocation(m_shader->GetProgram(), _name);
	glUniform4fv(val, 1, &_value.x);
}

void Material::SetInt(const char* _name, const int _value)
{
	unsigned int val = glGetUniformLocation(m_shader->GetProgram(), _name);
	glUniform1i(val, _value);
}

void Material::SetFloat(const char* _name, const float _value)
{
	unsigned int val = glGetUniformLocation(m_shader->GetProgram(), _name);
	glUniform1f(val, _value);
}

void Material::SetMatrix(const char* _name, const Matrix4x4& _value)
{
	unsigned int val = glGetUniformLocation(m_shader->GetProgram(), _name);
	glUniformMatrix4fv(val, 1, GL_FALSE, _value.GetData());
}

void Material::SetShader(Shader* _shader)
{
	m_shader = _shader;
}

void Material::Bind()
{
	m_shader->Bind();
}
