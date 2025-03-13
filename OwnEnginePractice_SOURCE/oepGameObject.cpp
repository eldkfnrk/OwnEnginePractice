#include "oepGameObject.h"
#include "oepInput.h"

namespace oep {
	GameObject::GameObject() : mX(0.0f), mY(0.0f) {
		
	}

	void GameObject::Update() {
		//if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		//	mX -= 0.01f;
		//}

		//if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		//	mX += 0.01f;
		//}

		//if (GetAsyncKeyState(VK_UP) & 0x8000) {
		//	mY -= 0.01f;
		//}

		//if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		//	mY += 0.01f;
		//}

		//위의 코드를 이제 Input 클래스를 사용하는 것으로 수정(방향키 대신 WASD로 변경)
		//정적 멤버 함수이기 때문에 객체가 필요하지 않고 대신 어느 클래스의 함수인지만 알려주면 함수를 사용할 수 있다.
		//이렇게 바꾸니 위의 방법보다 코드의 이해가 조금 더 편해지게 된다. 한마디로 가독성이 좋아졌다 말할 수 있다.
		if (Input::GetKey(eKeyCode::A)) {
			mX -= 0.01f;
		}

		if (Input::GetKey(eKeyCode::D)) {
			mX += 0.01f;
		}

		if (Input::GetKey(eKeyCode::W)) {
			mY -= 0.01f;
		}

		if (Input::GetKey(eKeyCode::S)) {
			mY += 0.01f;
		}
	}

	void GameObject::LateUpdate() {

	}

	void GameObject::Render(HDC hdc) {
		HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);
		Rectangle(hdc, 100 + mX, 100 + mY, 200 + mX, 200 + mY);

		SelectObject(hdc, oldBrush);

		DeleteObject(blueBrush);  //메모리 삭제
	}

	GameObject::~GameObject() {

	}
}