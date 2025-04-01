#pragma once
#include "CommonInclude.h"

namespace oep {
	enum class eKeyState {  
		Down,  //누를 때
		Pressed,  //누르고 있을 때
		Up,  //뗄 때
		None,  //아무것도 안 할 때
	};

	enum class eKeyCode {  ////마우스 좌우 클릭 및 휠 클릭 추가
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		Left, Right, Up, Down, Space,
		MLButton, MMButton/*마우스 휠 버튼*/, MRButton,
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

		static math::Vector2 GetMousePosition() {
			return mMousePosition;
		}

	private:
		static void createKeys();
		static void updateKeys();
		static void updateKeyDown(Input::Key& key);
		static void updateKeyUp(Input::Key& key);
		static void getMousePositionByWindow();
		static void clearKeys();

	private:
		static std::vector<Key> Keys;  
		static math::Vector2 mMousePosition;  //마우스 좌표(클릭하는 게임을 만들 때 사용할 수 있도록 추가)
	};
}
