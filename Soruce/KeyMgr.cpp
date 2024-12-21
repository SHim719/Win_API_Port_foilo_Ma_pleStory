#include "KeyMgr.h"
#include "MainGame.h"
#include "Camera.h"


extern MainGame g_MainGame;

vector<KeyMgr::Key> KeyMgr::vecKey = { };
Vec2 KeyMgr::vMousePos = Vec2::Zero;

int ASCII[(UINT)eKeyCode::End] =
{
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
	'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP,
	VK_SPACE, VK_LBUTTON, VK_RBUTTON,
	VK_LCONTROL, VK_LSHIFT, 
	VK_NUMPAD0, VK_NUMPAD1,
	'1', '2', '3' ,'4', VK_RETURN
};

void KeyMgr::Initialize()
{
	createKeys();
}

void KeyMgr::Update()
{
	updateKeys();
}

Vec2 KeyMgr::GetWorldMousePos()
{
	Vec2 vDistance = Camera::GetDistance();
	return vDistance + vMousePos;
}

void KeyMgr::createKeys()
{
	vecKey.reserve((size_t)eKeyCode::End);
	for (size_t i = 0; i < (size_t)eKeyCode::End; ++i)
	{
		Key key;
		key.eKeyCode = (eKeyCode)i;
		key.eState = eKeyState::None;
		key.bPressed = false;

		vecKey.push_back(key);
	}
}

void KeyMgr::updateKeys()
{
	for_each(vecKey.begin(), vecKey.end(),
		[](Key& Key) -> void
		{
			updateKey(Key);
		});
}

void KeyMgr::updateKey(Key& key)
{
	if (GetFocus())
	{
		if (isKeyDown(key.eKeyCode))
		{
			updateKeyDown(key);
		}
		else
		{
			updateKeyUp(key);
		}

		getMousePosByClient();
	}
	else
	{
		clearKeys();
	}
}

void KeyMgr::updateKeyDown(Key& key)
{
	if (key.bPressed)
		key.eState = eKeyState::Pressed;
	else
		key.eState = eKeyState::Down;

	key.bPressed = true;
}

void KeyMgr::updateKeyUp(Key& key)
{
	if (key.bPressed)
		key.eState = eKeyState::Up;
	else
		key.eState = eKeyState::None;

	key.bPressed = false;
}

bool KeyMgr::isKeyDown(eKeyCode code)
{
	return GetAsyncKeyState(ASCII[(UINT)code]) & 0x8000;
}

void KeyMgr::clearKeys()
{
	for (Key& key : vecKey)
	{
		if (key.eState == eKeyState::Down || key.eState == eKeyState::Pressed)
			key.eState = eKeyState::Up;
		else if (key.eState == eKeyState::Up)
			key.eState = eKeyState::None;
		key.bPressed = false;
	}
}

void KeyMgr::getMousePosByClient()
{
	POINT mousePos = { };
	GetCursorPos(&mousePos);
	ScreenToClient(g_MainGame.GetHwnd(), &mousePos);

	vMousePos.x = (float)mousePos.x;
	vMousePos.y = (float)mousePos.y;
}
