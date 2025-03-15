#pragma once
#include "CommonInclude.h"

namespace oep {
	enum class eKeyState {  
		Down,  //누를 때
		Pressed,  //누르고 있을 때
		Up,  //뗄 때
		None,  //아무것도 안 할 때
	};

	enum class eKeyCode {  //키보드 영문자에 방향키 추가
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		Left, Right, Up, Down,
		End,
	};

	class Input
	{
	public:
		struct Key 
		{
			eKeyCode keycode; 
			eKeyState state;  
			bool bPressed;  
		};

		static void Initialize();  
		static void Update();  

		static bool GetKeyDown(eKeyCode code) {
			return Keys[(UINT)code].state == eKeyState::Down;
		}

		static bool GetKeyUp(eKeyCode code) {
			return Keys[(UINT)code].state == eKeyState::Up;
		}

		static bool GetKey(eKeyCode code) {
			return Keys[(UINT)code].state == eKeyState::Pressed;
		}

	private:
		//외부에서 직접 접근할 필요도 없고 직접 접근이 가능해서도 안 되는 작업이기 때문에 private 멤버로 선언(private 멤버 함수의 이름은 보통 소문자로 설정한다.)
		//꿀팁으로 ctrl + r + r 을 하게 되면 함수의 이름을 변경할 때 이 함수를 사용하고 있던 곳에서도 한 번에 함수명 수정이 가능하다.
		//정적 멤버 함수 내에서 호출되어야 하는 함수는 정적 멤버로 선언하여야 한다.	
		static void createKeys();
		static void updateKeys();
		//아래 두 함수는 구현 과정에서 논리 오류를 일으켜 삭제 처리
		//static void updateKey(Input::Key& key);
		//static bool isKeyDown(eKeyCode code);
		static void updateKeyDown(Input::Key& key);
		static void updateKeyUp(Input::Key& key);

	private:
		//private 멤버이지만 정적 변수이기 때문에 다른 멤버 변수들과의 구분을 위해 대문자로 이름 시작
		static std::vector<Key> Keys;  
	};
}
