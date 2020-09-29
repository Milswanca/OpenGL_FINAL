#pragma once
#include "Actor.h"
#include "DataTypes.h"

#define NUM_KEYS 256

class InputSystem : public Actor
{
public:
	InputSystem(const ObjectInitData& _OI);

public:
	virtual void PostUpdate(const float _deltaTime) override;

	bool IsKeyJustPressed(unsigned char _key) const;
	bool IsKeyJustReleased(unsigned char _key) const;
	bool IsKeyDown(unsigned char _key) const;

	bool IsMouseButtonJustPressed(MouseButtons _key) const;
	bool IsMouseButtonJustReleased(MouseButtons _key) const;
	bool IsMouseButtonDown(MouseButtons _key) const;

	Vector3 GetMousePosition() const;
	Vector3 GetMouseDelta() const;

protected:
	void KeyPressed(unsigned char _key);
	void KeyReleased(unsigned char _key);

	void MouseMoved(unsigned int _x, unsigned int _y);
	void MouseButtonPressed(unsigned char _button);
	void MouseButtonReleased(unsigned char _button);

private:
	// Keystates of all keys 
	// 1st byte = last frame value
	// 2nd byte = this frame value
	// 3rd & 4th are unused
	char m_keyStates[NUM_KEYS];
	char m_mouseStates[3];

	Vector3 m_mouseLast;
	Vector3 m_mouseLocation;

	friend Window;
};