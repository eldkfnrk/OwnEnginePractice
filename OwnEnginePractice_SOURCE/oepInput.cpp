#include "oepInput.h"

namespace oep {
	//정적 멤버 변수는 클래스의 전역 변수이기 때문에 반드시 초기화가 되어야 한다.
	//이렇게 선언한 정적 멤버는 해당 클래스의 객체가 여러 개여도 전역 변수처럼 메모리 상에 하나만 존재해 객체들은 이에 접근하여 사용할 수 있게 되는 것이다.
	//즉, 정적 멤버는 메모리가 한 번 할당되면 프로그램이 종료될 때까지 사라지지 않는다.(클래스 뿐 아니라 함수등에서도 사용할 수 있다.)
	std::vector<Input::Key> Input::mKeys = {};

	//이 배열은 아래의 키 입력 상태를 확인하기 위한 ASCII 코드를 키의 순서에 맞게 정렬해놓은 배열이다.(다른 키가 추가되면 이 배열도 순서에 맞게 추가)
	int ASCII[(int)eKeyCode::End] = {
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	};

	//정적 멤버는 함수도 반드시 정의가 되어 있어야 한다.
	void Input::Initialize() {
		//벡터 크기 재조정
		mKeys.resize((UINT)eKeyCode::End);

		//키 초기화
		//열거형은 숫자가 아니기 때문에 숫자형으로 형 변환을 해주어야 한다.
		for (size_t i = 0; i < (UINT)eKeyCode::End; i++) {
			Key key = {};
			key.keycode = (eKeyCode)i;  //이것도 마찬가지로 정수형은 열거형이 아니니 형 변환을 해주는 것이다.
			key.state = eKeyState::None;
			key.bPressed = false;

			mKeys.push_back(key);  //벡터의 맨 마지막에 삽입(이렇게 해두면 순서대로 벡터에 저장되게 된다.)
		}
	}

	void Input::Update() {
		for (size_t i = 0; i < mKeys.size(); i++) {  //이 조건문은 위에처럼 사용해도 되고 지금처럼 사용해도 된다.
			//키가 눌렸는지 아닌지
			if (GetAsyncKeyState(ASCII[i]) & 0x8000) {  //이전 프레임에 키가 눌린 경우
				if (mKeys[i].bPressed) {  //이전 프레임에 키가 눌려있던 경우
					mKeys[i].state = eKeyState::Pressed;
				}
				else {  //키가 눌려있지 않던 경우
					mKeys[i].state = eKeyState::Down;
				}

				mKeys[i].bPressed = true;
			}
			else {  //키가 안 눌린 경우
				if (mKeys[i].bPressed) {  //이전 프레임에 키가 눌려있던 경우
					mKeys[i].state = eKeyState::Up;
				}
				else {  //이전 프레임에 키가 눌려있지 않던 경우
					mKeys[i].state = eKeyState::None;
				}

				mKeys[i].bPressed = false;
			}
		}
	}
}