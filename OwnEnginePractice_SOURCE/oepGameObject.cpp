#include "oepGameObject.h"
#include "oepInput.h"
#include "oepTime.h"

namespace oep {
	GameObject::GameObject() : mX(0.0f), mY(0.0f) {
		
	}

	void GameObject::Update() {
		const float speed = 100.0f;  //Time을 통해 모든 컴퓨터에서 동일한 결과 값이 나오도록 바꿨으니 도형의 이동 속도를 지정

		if (Input::GetKey(eKeyCode::A)) {
			//mX -= 0.01f;
			mX -= speed * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::D)) {
			//mX += 0.01f;
			mX += speed * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::W)) {
			//mY -= 0.01f;
			mY -= speed * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::S)) {
			//mY += 0.01f;
			mY += speed * Time::DeltaTime();
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