#pragma once
#include "CommonInclude.h"

namespace oep {
	enum class eKeyState {  
		Down,  //���� ��
		Pressed,  //������ ���� ��
		Up,  //�� ��
		None,  //�ƹ��͵� �� �� ��
	};

	enum class eKeyCode {  //Ű���� �����ڿ� ����Ű �߰�
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
		//�ܺο��� ���� ������ �ʿ䵵 ���� ���� ������ �����ؼ��� �� �Ǵ� �۾��̱� ������ private ����� ����(private ��� �Լ��� �̸��� ���� �ҹ��ڷ� �����Ѵ�.)
		//�������� ctrl + r + r �� �ϰ� �Ǹ� �Լ��� �̸��� ������ �� �� �Լ��� ����ϰ� �ִ� �������� �� ���� �Լ��� ������ �����ϴ�.
		//���� ��� �Լ� ������ ȣ��Ǿ�� �ϴ� �Լ��� ���� ����� �����Ͽ��� �Ѵ�.	
		static void createKeys();
		static void updateKeys();
		//�Ʒ� �� �Լ��� ���� �������� �� ������ ������ ���� ó��
		//static void updateKey(Input::Key& key);
		//static bool isKeyDown(eKeyCode code);
		static void updateKeyDown(Input::Key& key);
		static void updateKeyUp(Input::Key& key);

	private:
		//private ��������� ���� �����̱� ������ �ٸ� ��� ��������� ������ ���� �빮�ڷ� �̸� ����
		static std::vector<Key> Keys;  
	};
}
