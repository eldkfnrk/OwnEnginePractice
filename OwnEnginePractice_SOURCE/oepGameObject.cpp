#include "oepGameObject.h"
#include "oepInput.h"
#include "oepTime.h"

namespace oep {
	GameObject::GameObject() : mX(0.0f), mY(0.0f) {

	}

	void GameObject::Update() {
		const float speed = 100.0f;

		if (Input::GetKey(eKeyCode::A)) {
			mX -= speed * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::D)) {
			mX += speed * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::W)) {
			mY -= speed * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::S)) {
			mY += speed * Time::DeltaTime();
		}
		
		//if (Input::GetKeyDown(eKeyCode::Space)) {

		//}
	}

	void GameObject::LateUpdate() {
		
	}

	void GameObject::Render(HDC hdc) {
		//HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
		HBRUSH randomBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand()%255));  //색이 랜덤으로 설정되도록 rgb값을 랜덤으로 설정
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, randomBrush);
		//Rectangle(hdc, 100 + mX, 100 + mY, 200 + mX, 200 + mY);
		Ellipse(hdc, mX, mY, 100 + mX, 100 + mY);  //시작 주소가 mX, mY여야지 화면을 벗어난 도형이 생기지 않는다.

		SelectObject(hdc, oldBrush);

		DeleteObject(randomBrush);  //메모리 삭제
	}

	GameObject::~GameObject() {

	}
}