// OpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "PCH.h"
#include "Engine.h"

int main()
{
	ObjectInitData data;
    Engine* engine = new Engine(data);
    
	engine->Init();
    engine->Run();
    engine->Shutdown();
}