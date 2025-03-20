#include "oepInput.h"

namespace oep {
	std::vector<Input::Key> Input::Keys = {};

	int ASCII[(int)eKeyCode::End] = {
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M', 
		VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, VK_SPACE,
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
			if (GetAsyncKeyState(ASCII[i]) & 0x8000) {
				updateKeyDown(Keys[i]);
			}
			else {
				updateKeyUp(Keys[i]);
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
}