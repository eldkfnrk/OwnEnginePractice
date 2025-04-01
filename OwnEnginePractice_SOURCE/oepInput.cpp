#include "oepInput.h"
#include "oepApplication.h"

extern oep::Application application;  //�� ���� ������ �������� �ڵ� ���� ������ �־ ���

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
			else {  //�����찡 Ȱ��ȭ�Ǿ� ���� �ʴٸ� Ű �������� false�� �ٲ㼭 ��� �ʱ�ȭ���� �־�� �Ѵ�.(�����찡 ��Ȱ��ȭ�Ǹ� ���ӿ� �Է��� �� �ǵ��� ���ƾ� �ϱ� �����̴�.)
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
		//������32 API�� �ڷ��� �߿� LP�� �ٴ� �ڷ����� �ִµ� �̴� LP�ڿ� �پ��ִ� �ڷ����� �����͸� �ǹ��Ѵ�.(LPPOINT�̸� POINT�� �ڷ����� �ǹ�)
		//���� �Լ����� ��� ���ڷ� �����͸� �ޱ� ������ �Լ� �ȿ��� ������ �����Ϳ� �����ؼ� ���� �� ���� �ٷ� ���� �����Ѵ�.(call-by-reference �������� ����)
		POINT mousePos = {};
		GetCursorPos(&mousePos);  //���콺 Ŀ���� ��ġ�� �� �� �ִ� �Լ�

		//���� �Լ��� ������ �����츦 �������� ���콺�� ��ǥ�� ��ȯ���� �ʴ´�. �׷��� ��Ȯ�� ��ǥ ���� �������� ���� ������ ������ �߻��� �� ������ ���α׷��� ���ư��� �ִ�
		//�����츦 �������� ���콺 ��ġ ������ �޵��� �Ʒ��� �Լ��� ����Ѵ�.
		ScreenToClient(application.GetHwnd(), &mousePos);  //�� �Լ��� ���α׷��� ���ư��� �ִ� �������� �ڵ��� ���ڷ� �޾� �����츦 Ư���� �� �ִ�.

		//�̷��� ���� ���콺 ��ǥ�� ���� ������ ����
		mMousePosition.x = mousePos.x;
		mMousePosition.y = mousePos.y;

		//���� �̷��Ը� �ϸ� �����찡 Ȱ��ȭ���� ���� ���¿����� �����츦 �������� ��ǥ�� ��ȯ�ȴ�. ����, �����츦 ����� ���������̴�.
		//ū ������ ���� ������ ������ �߻��� ���ɼ� ��ü�� ���̱� ���� �����찡 Ȱ��ȭ�� ���¿����� ���콺 ��ǥ�� ���� �� �ֵ��� �����ؾ� �Ѵ�.
		//�� ������ ���ִ� �Լ��� �ٷ� GetFocus() �Լ��̴�.
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