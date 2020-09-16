#pragma once
class TimeManager
{
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::duration<float> fsec;

public:
	static void Init();
	static void Update();
	static float GetDeltaTime();
	static float GetElapsedTime();

private:
	static std::chrono::system_clock::time_point m_startTime;
	static std::chrono::system_clock::time_point m_lastTime;
	static std::chrono::system_clock::time_point m_currentTime;
};

