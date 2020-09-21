#include "PCH.h"
#include "TimeManager.h"

std::chrono::system_clock::time_point TimeManager::m_lastTime;
std::chrono::system_clock::time_point TimeManager::m_currentTime;
std::chrono::system_clock::time_point TimeManager::m_startTime;

void TimeManager::Init()
{
	m_lastTime = std::chrono::system_clock::now();
	m_currentTime = m_lastTime;
	m_startTime = m_lastTime;
}

void TimeManager::Update()
{
	m_lastTime = m_currentTime;
	m_currentTime = std::chrono::system_clock::now();
}

float TimeManager::GetDeltaTime()
{
	return std::chrono::duration<float>((m_currentTime - m_lastTime)).count();
}

float TimeManager::GetElapsedTime()
{
	return std::chrono::duration<float>((m_currentTime - m_startTime)).count();
}
