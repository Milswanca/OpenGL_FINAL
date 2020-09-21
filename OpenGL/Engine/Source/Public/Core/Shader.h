#pragma once
#include "Object.h"

class Shader : public Object
{
	struct ShaderData
	{
	public:
		const char* path;
		unsigned int shaderId;
	};

public:
	Shader(const ObjectInitData& _data);

	static Shader* Create(Object* _ref, const char* _vertexShader, const char* _pixelShader);

	void Bind();
	void Recompile(bool _reloadShaders = false);

	unsigned int GetProgram() const;

private:
	void Load(const char* _vertexShader, const char* _pixelShader);
	void LoadShaderSource(const char* _file, std::string& _source);
	void LoadShader(ShaderTypes _type, const char* _shader);

	unsigned int m_program;
	std::map<ShaderTypes, ShaderData> m_shaders;
};