#pragma once
#include "PCH.h"
#include "Engine.h"
#include "GameProgram.h"

int main()
{
	ObjectInitData data;
	Engine* engine = new Engine(data);

	engine->Init();
#if !EDITOR
	engine->SpawnProgram<GameProgram>();
#endif
	engine->Run();
	engine->Shutdown();
}