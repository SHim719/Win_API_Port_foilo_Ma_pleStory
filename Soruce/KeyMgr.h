#pragma once

#include "CommonInclude.h"

enum class eKeyState
{
	Down,
	Pressed,
	Up,
	None,
};

enum class eKeyCode
{
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,
	Left, Right, Down, Up,
	Space, LButton, RButton,
	LCtrl, LShift, NUMPAD0,
	NUMPAD1,
	One, Two, Three, Four,
	Enter,
	End,
};

class KeyMgr
{
public:
	struct Key
	{
		eKeyCode eKeyCode;
		eKeyState eState;
		bool bPressed;
	};

	static void Initialize();
	static void Update();

	static bool GetKeyDown(eKeyCode _keyCode) { return vecKey[(UINT)_keyCode].eState == eKeyState::Down; }
	static bool GetKeyUp(eKeyCode _keyCode) { return vecKey[(UINT)_keyCode].eState == eKeyState::Up; }
	static bool GetKey(eKeyCode _keyCode) { return vecKey[(UINT)_keyCode].eState == eKeyState::Pressed; }
	static bool GetKeyNone(eKeyCode _keyCode) { return vecKey[(UINT)_keyCode].eState == eKeyState::None; }

	static const Vec2& GetMousePos() { return vMousePos; }
	static Vec2 GetWorldMousePos();
private:
	KeyMgr() {};
	~KeyMgr() {};

	static void createKeys();
	static void updateKeys();
	static void updateKey(Key& key);
	static void updateKeyDown(Key& key);
	static void updateKeyUp(Key& key);
	static bool isKeyDown(eKeyCode code);
	static void clearKeys();
	static void getMousePosByClient();

private:
	static vector<Key> vecKey;
	static Vec2 vMousePos;

};
