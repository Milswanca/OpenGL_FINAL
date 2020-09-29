#include "PCH.h"
#include "InputSystem.h"

InputSystem::InputSystem(const ObjectInitData& _data) : Actor(_data)
{

}

void InputSystem::PostUpdate(const float _deltaTime)
{
	Actor::PostUpdate(_deltaTime);

	for (int i = 0; i < NUM_KEYS; ++i)
	{
		//This stores the value of the 2nd bit into the 1st
		int isOn = m_keyStates[i] >> 1 & 1U;
		m_keyStates[i] ^= (-isOn ^ m_keyStates[i]) & (1UL << 0);
	}

	for (int i = 0; i < 3; ++i)
	{
		//This stores the value of the 2nd bit into the 1st
		int isOn = m_mouseStates[i] >> 1 & 1U;
		m_mouseStates[i] ^= (-isOn ^ m_mouseStates[i]) & (1UL << 0);
	}

	m_mouseLast = m_mouseLocation;
}

bool InputSystem::IsKeyJustPressed(unsigned char _key) const
{
	char entry = m_keyStates[_key];

	//Check if the 2nd byte is on and the first byte is off
	return ((entry >> 1) & 1U) != 0 && ((entry >> 0) & 1U) == 0;
}

bool InputSystem::IsKeyJustReleased(unsigned char _key) const
{
	char entry = m_keyStates[_key];

	//Check if the 2nd byte is on and the first byte is off
	return ((entry >> 1) & 1U) == 0 && ((entry >> 0) & 1U) != 0;
}

bool InputSystem::IsKeyDown(unsigned char _key) const
{
	char entry = m_keyStates[_key];

	//Check if the 2nd byte is on and the first byte is off
	return ((entry >> 1) & 1U) != 0;
}

bool InputSystem::IsMouseButtonJustPressed(MouseButtons _key) const
{
	char entry = m_mouseStates[_key];

	//Check if the 2nd byte is on and the first byte is off
	return ((entry >> 1) & 1U) != 0 && ((entry >> 0) & 1U) == 0;
}

bool InputSystem::IsMouseButtonJustReleased(MouseButtons _key) const
{
	char entry = m_mouseStates[_key];

	//Check if the 2nd byte is on and the first byte is off
	return ((entry >> 1) & 1U) == 0 && ((entry >> 0) & 1U) != 0;
}

bool InputSystem::IsMouseButtonDown(MouseButtons _key) const
{
	char entry = m_mouseStates[_key];

	//Check if the 2nd byte is on and the first byte is off
	return ((entry >> 1) & 1U) != 0;
}

Vector3 InputSystem::GetMousePosition() const
{
	return m_mouseLocation;
}

Vector3 InputSystem::GetMouseDelta() const
{
	return m_mouseLast - m_mouseLocation;
}

void InputSystem::KeyPressed(unsigned char _key)
{
	char entry = m_keyStates[_key];

	//Set the 2nd byte on
	entry |= (1 << 1);

	m_keyStates[_key] = entry;
}

void InputSystem::KeyReleased(unsigned char _key)
{
	char entry = m_keyStates[_key];

	//Set the 2nd byte off
	entry &= ~(1UL << 1);

	m_keyStates[_key] = entry;
}

void InputSystem::MouseMoved(unsigned int _x, unsigned int _y)
{
	m_mouseLocation = Vector3((float)_x, (float)_y, 0.0f);
}

void InputSystem::MouseButtonPressed(unsigned char _button)
{
	char entry = m_mouseStates[_button];

	//Set the 2nd byte on
	entry |= (1 << 1);

	m_mouseStates[_button] = entry;
}

void InputSystem::MouseButtonReleased(unsigned char _button)
{
	char entry = m_mouseStates[_button];

	//Set the 2nd byte off
	entry &= ~(1UL << 1);

	m_mouseStates[_button] = entry;
}