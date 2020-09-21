#include "PCH.h"
#include "Program.h"
#include "SystemDialogs.h"

Program::Program(const ObjectInitData& _data) : Actor(_data)
{
	SystemDialogs::OpenFile();
}

Program::~Program()
{

}