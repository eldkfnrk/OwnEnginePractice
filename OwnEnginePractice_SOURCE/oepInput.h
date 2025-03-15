#pragma once
#include "CommonInclude.h"

namespace oep {
	enum class eKeyState {  
		Down,  //���� ��
		Pressed,  //������ ���� ��
		Up,  //�� ��
		None,  //�ƹ��͵� �� �� ��
	};

	enum class eKeyCode {  
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
		static void createKeys();
		static void updateKeys();
		static void updateKeyDown(Input::Key& key);
		static void updateKeyUp(Input::Key& key);

	private:
		static std::vector<Key> Keys;  
	};
}
