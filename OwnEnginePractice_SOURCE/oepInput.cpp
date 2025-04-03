#include "oepInput.h"
#include "oepApplication.h"

extern oep::Application application;  

namespace oep {
	std::vector<Input::Key> Input::Keys = {};
	math::Vector2 Input::mMousePosition = math::Vector2::One;

	int ASCII[(int)eKeyCode::End] = {  
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M', 
		VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, VK_SPACE,
		VK_LBUTTON, VK_MBUTTON, VK_RBUTTON,
	};

	void Input::Initialize() 
	{
		createKeys();
	}

	void Input::Update() 
	{
		updateKeys();
	}

	void Input::createKeys()
	{
		Keys.resize((UINT)eKeyCode::End);

		for (size_t i = 0; i < (UINT)eKeyCode::End; i++) {
			Key key = {};
			key.keycode = (eKeyCode)i;
			key.state = eKeyState::None;
			key.bPressed = false;

			Keys.push_back(key);
		}
	}

	void Input::updateKeys()
	{
		for (size_t i = 0; i < Keys.size(); i++) {
			if (GetFocus()) {  //�����찡 Ȱ��ȭ �Ǿ������� if���� �ɸ��� �ȴ�.
				if (GetAsyncKeyState(ASCII[i]) & 0x8000) {
					updateKeyDown(Keys[i]);
				}
				else {
					updateKeyUp(Keys[i]);
				}

				getMousePositionByWindow();
			}
			else {  
				clearKeys();
			}
		}
	}

	void Input::updateKeyDown(Input::Key& key)
	{
		if (key.bPressed) {
			key.state = eKeyState::Pressed;
		}
		else {
			key.state = eKeyState::Down;
		}

		key.bPressed = true;
	}

	void Input::updateKeyUp(Input::Key& key)
	{
		if (key.bPressed) { 
			key.state = eKeyState::Up;
		}
		else {  
			key.state = eKeyState::None;
		}

		key.bPressed = false;
	}

	void Input::getMousePositionByWindow()
	{
		POINT mousePos = {};
		GetCursorPos(&mousePos);  

		ScreenToClient(application.GetHwnd(), &mousePos);  

		//�̷��� ���� ���콺 ��ǥ�� ���� ������ ����
		mMousePosition.x = mousePos.x;
		mMousePosition.y = mousePos.y;
	}

	void Input::clearKeys()
	{
		for (Key& key : Keys)
		{
			//��� Ű���� ���� ���� ���� ���·� �ʱ�ȭ
			if (key.state == eKeyState::Down || key.state == eKeyState::Pressed) {
				key.state = eKeyState::Up;
			}
			else if (key.state == eKeyState::Up) {
				key.state = eKeyState::None;
			}

			key.bPressed = false;
		}
	}
}