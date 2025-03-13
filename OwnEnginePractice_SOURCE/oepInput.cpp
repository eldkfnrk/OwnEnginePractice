#include "oepInput.h"

namespace oep {
	//���� ��� ������ Ŭ������ ���� �����̱� ������ �ݵ�� �ʱ�ȭ�� �Ǿ�� �Ѵ�.
	//�̷��� ������ ���� ����� �ش� Ŭ������ ��ü�� ���� ������ ���� ����ó�� �޸� �� �ϳ��� ������ ��ü���� �̿� �����Ͽ� ����� �� �ְ� �Ǵ� ���̴�.
	//��, ���� ����� �޸𸮰� �� �� �Ҵ�Ǹ� ���α׷��� ����� ������ ������� �ʴ´�.(Ŭ���� �� �ƴ϶� �Լ������ ����� �� �ִ�.)
	std::vector<Input::Key> Input::mKeys = {};

	//�� �迭�� �Ʒ��� Ű �Է� ���¸� Ȯ���ϱ� ���� ASCII �ڵ带 Ű�� ������ �°� �����س��� �迭�̴�.(�ٸ� Ű�� �߰��Ǹ� �� �迭�� ������ �°� �߰�)
	int ASCII[(int)eKeyCode::End] = {
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	};

	//���� ����� �Լ��� �ݵ�� ���ǰ� �Ǿ� �־�� �Ѵ�.
	void Input::Initialize() {
		//���� ũ�� ������
		mKeys.resize((UINT)eKeyCode::End);

		//Ű �ʱ�ȭ
		//�������� ���ڰ� �ƴϱ� ������ ���������� �� ��ȯ�� ���־�� �Ѵ�.
		for (size_t i = 0; i < (UINT)eKeyCode::End; i++) {
			Key key = {};
			key.keycode = (eKeyCode)i;  //�̰͵� ���������� �������� �������� �ƴϴ� �� ��ȯ�� ���ִ� ���̴�.
			key.state = eKeyState::None;
			key.bPressed = false;

			mKeys.push_back(key);  //������ �� �������� ����(�̷��� �صθ� ������� ���Ϳ� ����ǰ� �ȴ�.)
		}
	}

	void Input::Update() {
		for (size_t i = 0; i < mKeys.size(); i++) {  //�� ���ǹ��� ����ó�� ����ص� �ǰ� ����ó�� ����ص� �ȴ�.
			//Ű�� ���ȴ��� �ƴ���
			if (GetAsyncKeyState(ASCII[i]) & 0x8000) {  //���� �����ӿ� Ű�� ���� ���
				if (mKeys[i].bPressed) {  //���� �����ӿ� Ű�� �����ִ� ���
					mKeys[i].state = eKeyState::Pressed;
				}
				else {  //Ű�� �������� �ʴ� ���
					mKeys[i].state = eKeyState::Down;
				}

				mKeys[i].bPressed = true;
			}
			else {  //Ű�� �� ���� ���
				if (mKeys[i].bPressed) {  //���� �����ӿ� Ű�� �����ִ� ���
					mKeys[i].state = eKeyState::Up;
				}
				else {  //���� �����ӿ� Ű�� �������� �ʴ� ���
					mKeys[i].state = eKeyState::None;
				}

				mKeys[i].bPressed = false;
			}
		}
	}
}