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
		//	//키가 눌렸는지 아닌지
		//	if (GetAsyncKeyState(ASCII[i]) & 0x8000) {  //이전 프레임에 키가 눌린 경우
		//		if (Keys[i].bPressed) {  //이전 프레임에 키가 눌려있던 경우
		//			Keys[i].state = eKeyState::Pressed;
		//		}
		//		else {  //키가 눌려있지 않던 경우
		//			Keys[i].state = eKeyState::Down;
		//		}

		//		Keys[i].bPressed = true;
		//	}
		//	else {  //키가 안 눌린 경우
		//		if (Keys[i].bPressed) {  //이전 프레임에 키가 눌려있던 경우
		//			Keys[i].state = eKeyState::Up;
		//		}
		//		else {  //이전 프레임에 키가 눌려있지 않던 경우
		//			Keys[i].state = eKeyState::None;
		//		}

		//		Keys[i].bPressed = false;
		//	}
		//}

		updateKeys();
	}

	void Input::createKeys()
	{
		//기존에 Initialize 함수에서 하던 동작을 따로 해주는 함수를 정의하고 이 함수를 Initialize 함수에서 호출하도록 수정
		//벡터 크기 재조정
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
			//키가 눌렸는지 아닌지
			if (GetAsyncKeyState(ASCII[i]) & 0x8000) {  //이전 프레임에 키가 눌린 경우
				updateKeyDown(Keys[i]);
			}
			else {  //키가 안 눌린 경우
				updateKeyUp(Keys[i]);
			}
		}

		//위의 for문을 아래와 같이 for_each문으로 수정
		//안에서 키의 상태를 구분하는 부분도 따로 함수로 만들어서 호출하는 방법으로 사용
		//for_each의 세 번째 인자는 함수가 들어오게 되는데 여기서는 람다식을 사용하여 for_each문을 완성하였다.
		//std::for_each(Keys.begin(), Keys.end(),
		//	[](Key& key) -> void {
		//		updateKey(key);
		//	});
		//for_each문을 사용하여 구현하였더니 도형이 이동하지 않는 논리 오류가 발생. 기존 방법으로 구현
	}

	//void Input::updateKey(Input::Key& key)
	//{
	//	//if (GetAsyncKeyState(ASCII[(UINT)key.keycode]) & 0x8000) {  //이전 프레임에 키가 눌린 경우
	//	//	if (key.bPressed) {  //이전 프레임에 키가 눌려있던 경우
	//	//		key.state = eKeyState::Pressed;
	//	//	}
	//	//	else {  //키가 눌려있지 않던 경우
	//	//		key.state = eKeyState::Down;
	//	//	}

	//	//	key.bPressed = true;
	//	//}
	//	//else {  //키가 안 눌린 경우
	//	//	if (key.bPressed) {  //이전 프레임에 키가 눌려있던 경우
	//	//		key.state = eKeyState::Up;
	//	//	}
	//	//	else {  //이전 프레임에 키가 눌려있지 않던 경우
	//	//		key.state = eKeyState::None;
	//	//	}

	//	//	key.bPressed = false;
	//	//}

	//	//위의 코드를 또 여러 함수들로 나누어 세분화하여 구현
	//	//이렇게 하는 이유는 각 동작에 맞게 함수들로 정리해놓으면 후에 시간이 지나면 코드를 까먹게 되는데 그럴 경우 코드 수정 시 코드를 다시 분석하고 고쳐야 하는데 이러면 시간이 많이 소요될 수 밖에 없기 때문에
	//	//이렇게 모든 동작들을 적절한 이름을 붙인 함수에 분할하여 구현해놓으면 굳이 함수들을 분석할 필요없이 수정이 필요한 함수를 찾아서 수정하면 되기 때문에 이렇게 분리하고 정리하는 것이 좋다.
	//	//if (isKeyDown(key.keycode)) {  //이전 프레임에 키가 눌린 경우
	//	//	updateKeyDown(key);
	//	//}
	//	//else {  //키가 안 눌린 경우
	//	//	updateKeyUp(key);
	//	//}
	//}

	//bool Input::isKeyDown(eKeyCode code) 
	//{  
	//	return GetAsyncKeyState(ASCII[(UINT)code]) & 0x8000;
	//}

	void Input::updateKeyDown(Input::Key& key)  //키를 눌린 상태로 변경하는 함수
	{
		if (key.bPressed) {  //이전 프레임에 키가 눌려있던 경우
			key.state = eKeyState::Pressed;
		}
		else {  //키가 눌려있지 않던 경우
			key.state = eKeyState::Down;
		}

		key.bPressed = true;
	}

	void Input::updateKeyUp(Input::Key& key)  //키를 뗀 상태로 변경하는 함수
	{
		if (key.bPressed) {  //이전 프레임에 키가 눌려있던 경우
			key.state = eKeyState::Up;
		}
		else {  //이전 프레임에 키가 눌려있지 않던 경우
			key.state = eKeyState::None;
		}

		key.bPressed = false;
	}
}