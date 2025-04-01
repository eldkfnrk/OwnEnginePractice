#include "oepInput.h"
#include "oepApplication.h"

extern oep::Application application;  //이 전역 변수가 윈도우의 핸들 값을 가지고 있어서 사용

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
			if (GetFocus()) {  //윈도우가 활성화 되어있으면 if문에 걸리게 된다.
				if (GetAsyncKeyState(ASCII[i]) & 0x8000) {
					updateKeyDown(Keys[i]);
				}
				else {
					updateKeyUp(Keys[i]);
				}

				getMousePositionByWindow();
			}
			else {  //윈도우가 활성화되어 있지 않다면 키 정보들을 false로 바꿔서 모두 초기화시켜 주어야 한다.(윈도우가 비활성화되면 게임에 입력이 안 되도록 막아야 하기 때문이다.)
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
		//윈도우32 API의 자료형 중에 LP가 붙는 자료형이 있는데 이는 LP뒤에 붙어있는 자료형의 포인터를 의미한다.(LPPOINT이면 POINT의 자료형을 의미)
		//위의 함수같은 경우 인자로 포인터를 받기 때문에 함수 안에서 정보를 포인터에 저장해서 리턴 값 없이 바로 값을 전달한다.(call-by-reference 형식으로 이해)
		POINT mousePos = {};
		GetCursorPos(&mousePos);  //마우스 커서의 위치를 얻어낼 수 있는 함수

		//위의 함수는 생성한 윈도우를 기준으로 마우스의 좌표를 반환하지 않는다. 그래서 정확한 좌표 값을 추출하지 못해 게임의 문제가 발생할 수 있으니 프로그램이 돌아가고 있는
		//윈도우를 기준으로 마우스 위치 정보를 받도록 아래의 함수를 사용한다.
		ScreenToClient(application.GetHwnd(), &mousePos);  //이 함수는 프로그램이 돌아가고 있는 윈도우의 핸들을 인자로 받아 윈도우를 특정할 수 있다.

		//이렇게 얻은 마우스 좌표를 따로 변수에 저장
		mMousePosition.x = mousePos.x;
		mMousePosition.y = mousePos.y;

		//지금 이렇게만 하면 윈도우가 활성화되지 않은 상태에서도 윈도우를 기준으로 좌표가 반환된다. 물론, 윈도우를 벗어나도 마찬가지이다.
		//큰 문제는 되지 않지만 문제가 발생할 가능성 자체를 줄이기 위해 윈도우가 활성화된 상태에서만 마우스 좌표를 얻을 수 있도록 수정해야 한다.
		//그 역할을 해주는 함수가 바로 GetFocus() 함수이다.
	}
	void Input::clearKeys()
	{
		for (Key& key : Keys)
		{
			//모든 키들이 눌려 있지 않은 상태로 초기화
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