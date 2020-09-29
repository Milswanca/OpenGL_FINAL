#pragma once
#include "Engine.h"

class EngineEditor : public Engine
{
public:
	EngineEditor(const ObjectInitData& _data);

	virtual void Init(HINSTANCE _handle) override;
	virtual void Update(float _dt) override;
	virtual void Shutdown() override;
};

