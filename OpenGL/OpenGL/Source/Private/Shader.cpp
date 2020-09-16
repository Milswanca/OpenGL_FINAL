#include "PCH.h"
#include "Shader.h"
#include "File.h"

#include "Engine.h"

Shader::Shader(const ObjectInitData& _data) : Object(_data)
{

}

Shader* Shader::Create(Object* _ref, const char* _vertexShader, const char* _pixelShader)
{
	Shader* shader = _ref->GetEngine()->NewObject<Shader>(_ref);
	shader->m_program = glCreateProgram();
	shader->Load(_vertexShader, _pixelShader);

	return shader;
}

void Shader::Load(const char* _vertexShader, const char* _pixelShader)
{
	LoadShader(ShaderTypes::Vertex, _vertexShader);
	LoadShader(ShaderTypes::Pixel, _pixelShader);

	Recompile();
}

void Shader::LoadShader(ShaderTypes _type, const char* _shader)
{
	unsigned int shader = 0;

	std::string source;
	LoadShaderSource(_shader, source);
	const char* str = source.c_str();

	switch (_type)
	{
	case ShaderTypes::Vertex:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;

	case ShaderTypes::Pixel:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}

	glShaderSource(shader, 1, &str, NULL);
	glCompileShader(shader);

	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
	}

	//Store the shader
	ShaderData data;
	data.path = _shader;
	data.shaderId = shader;
	m_shaders[_type] = data;
}

void Shader::LoadShaderSource(const char* _file, std::string&_source)
{
	std::string code = File::LoadFileToString(_file);
	_source = code;
}

void Shader::Recompile(bool _reloadShaders)
{
	for (auto i : m_shaders)
	{
		unsigned int shaderId = i.second.shaderId;

		if (_reloadShaders)
		{
			std::string source;
			LoadShaderSource(i.second.path, source);
			const char* str = source.c_str();
			glShaderSource(shaderId, 1, &str, NULL);
			glCompileShader(shaderId);
		}

		glAttachShader(m_program, shaderId);
	}

	glLinkProgram(m_program);
}

void Shader::Bind()
{
	int i = glGetError();
	glUseProgram(m_program);
	i = glGetError();
}

unsigned int Shader::GetProgram() const
{
	return m_program;
}