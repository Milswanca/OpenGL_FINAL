#pragma once

class Object
{
public:
	Object() = delete;
	Object(const ObjectInitData& _data);

	virtual Engine* GetEngine();
	virtual const Engine* GetEngine() const;

private:
	Engine* m_engine;
};

