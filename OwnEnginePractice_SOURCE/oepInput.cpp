#include "oepInput.h"

namespace oep {
	std::vector<Input::Key> Input::Keys = {};

	int ASCII[(int)eKeyCode::End] = {
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M', 
		VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
	};

	void Input::Initialize() 
	{
		//Keys.resize((UINT)eKeyCode::End);

		//for (size_t i = 0; i < (UINT)eKeyCode::End; i++) {
		//	Key key = {};
		//	key.keycode = (eKeyCode)i;  
		//	key.state = eKeyState::None;
		//	key.bPressed = false;

		//	Keys.push_back(key);  
		//}

		createKeys();
	}

	void Input::Update() 
	{
		//for (size_t i = 0; i < Keys.size(); i++) {
		//	//Ű�� ���ȴ��� �ƴ���
		//	if (GetAsyncKeyState(ASCII[i]) & 0x8000) {  //���� �����ӿ� Ű�� ���� ���
		//		if (Keys[i].bPressed) {  //���� �����ӿ� Ű�� �����ִ� ���
		//			Keys[i].state = eKeyState::Pressed;
		//		}
		//		else {  //Ű�� �������� �ʴ� ���
		//			Keys[i].state = eKeyState::Down;
		//		}

		//		Keys[i].bPressed = true;
		//	}
		//	else {  //Ű�� �� ���� ���
		//		if (Keys[i].bPressed) {  //���� �����ӿ� Ű�� �����ִ� ���
		//			Keys[i].state = eKeyState::Up;
		//		}
		//		else {  //���� �����ӿ� Ű�� �������� �ʴ� ���
		//			Keys[i].state = eKeyState::None;
		//		}

		//		Keys[i].bPressed = false;
		//	}
		//}

		updateKeys();
	}

	void Input::createKeys()
	{
		//������ Initialize �Լ����� �ϴ� ������ ���� ���ִ� �Լ��� �����ϰ� �� �Լ��� Initialize �Լ����� ȣ���ϵ��� ����
		//���� ũ�� ������
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
			//Ű�� ���ȴ��� �ƴ���
			if (GetAsyncKeyState(ASCII[i]) & 0x8000) {  //���� �����ӿ� Ű�� ���� ���
				updateKeyDown(Keys[i]);
			}
			else {  //Ű�� �� ���� ���
				updateKeyUp(Keys[i]);
			}
		}

		//���� for���� �Ʒ��� ���� for_each������ ����
		//�ȿ��� Ű�� ���¸� �����ϴ� �κе� ���� �Լ��� ���� ȣ���ϴ� ������� ���
		//for_each�� �� ��° ���ڴ� �Լ��� ������ �Ǵµ� ���⼭�� ���ٽ��� ����Ͽ� for_each���� �ϼ��Ͽ���.
		//std::for_each(Keys.begin(), Keys.end(),
		//	[](Key& key) -> void {
		//		updateKey(key);
		//	});
		//for_each���� ����Ͽ� �����Ͽ����� ������ �̵����� �ʴ� �� ������ �߻�. ���� ������� ����
	}

	//void Input::updateKey(Input::Key& key)
	//{
	//	//if (GetAsyncKeyState(ASCII[(UINT)key.keycode]) & 0x8000) {  //���� �����ӿ� Ű�� ���� ���
	//	//	if (key.bPressed) {  //���� �����ӿ� Ű�� �����ִ� ���
	//	//		key.state = eKeyState::Pressed;
	//	//	}
	//	//	else {  //Ű�� �������� �ʴ� ���
	//	//		key.state = eKeyState::Down;
	//	//	}

	//	//	key.bPressed = true;
	//	//}
	//	//else {  //Ű�� �� ���� ���
	//	//	if (key.bPressed) {  //���� �����ӿ� Ű�� �����ִ� ���
	//	//		key.state = eKeyState::Up;
	//	//	}
	//	//	else {  //���� �����ӿ� Ű�� �������� �ʴ� ���
	//	//		key.state = eKeyState::None;
	//	//	}

	//	//	key.bPressed = false;
	//	//}

	//	//���� �ڵ带 �� ���� �Լ���� ������ ����ȭ�Ͽ� ����
	//	//�̷��� �ϴ� ������ �� ���ۿ� �°� �Լ���� �����س����� �Ŀ� �ð��� ������ �ڵ带 ��԰� �Ǵµ� �׷� ��� �ڵ� ���� �� �ڵ带 �ٽ� �м��ϰ� ���ľ� �ϴµ� �̷��� �ð��� ���� �ҿ�� �� �ۿ� ���� ������
	//	//�̷��� ��� ���۵��� ������ �̸��� ���� �Լ��� �����Ͽ� �����س����� ���� �Լ����� �м��� �ʿ���� ������ �ʿ��� �Լ��� ã�Ƽ� �����ϸ� �Ǳ� ������ �̷��� �и��ϰ� �����ϴ� ���� ����.
	//	//if (isKeyDown(key.keycode)) {  //���� �����ӿ� Ű�� ���� ���
	//	//	updateKeyDown(key);
	//	//}
	//	//else {  //Ű�� �� ���� ���
	//	//	updateKeyUp(key);
	//	//}
	//}

	//bool Input::isKeyDown(eKeyCode code) 
	//{  
	//	return GetAsyncKeyState(ASCII[(UINT)code]) & 0x8000;
	//}

	void Input::updateKeyDown(Input::Key& key)  //Ű�� ���� ���·� �����ϴ� �Լ�
	{
		if (key.bPressed) {  //���� �����ӿ� Ű�� �����ִ� ���
			key.state = eKeyState::Pressed;
		}
		else {  //Ű�� �������� �ʴ� ���
			key.state = eKeyState::Down;
		}

		key.bPressed = true;
	}

	void Input::updateKeyUp(Input::Key& key)  //Ű�� �� ���·� �����ϴ� �Լ�
	{
		if (key.bPressed) {  //���� �����ӿ� Ű�� �����ִ� ���
			key.state = eKeyState::Up;
		}
		else {  //���� �����ӿ� Ű�� �������� �ʴ� ���
			key.state = eKeyState::None;
		}

		key.bPressed = false;
	}
}