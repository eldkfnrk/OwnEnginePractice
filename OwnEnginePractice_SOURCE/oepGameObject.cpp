#include "oepGameObject.h"
#include "oepInput.h"
#include "oepTime.h"

namespace oep {
	GameObject::GameObject() {

	}

	void GameObject::Initialize() {
		for (Component* comp : mComponents) {
			comp->Initialize();
		}
	}

	void GameObject::Update() {
		//const float speed = 100.0f;

		//이런 키 입력에 의한 이동도 다른 컴포넌트에서 동작하게 될 예정이다.
		//if (Input::GetKey(eKeyCode::A)) {
		//	mX -= speed * Time::DeltaTime();
		//}

		//if (Input::GetKey(eKeyCode::D)) {
		//	mX += speed * Time::DeltaTime();
		//}

		//if (Input::GetKey(eKeyCode::W)) {
		//	mY -= speed * Time::DeltaTime();
		//}

		//if (Input::GetKey(eKeyCode::S)) {
		//	mY += speed * Time::DeltaTime();
		//}
		
		//if (Input::GetKeyDown(eKeyCode::Space)) {

		//}

		for (Component* comp : mComponents) {
			comp->Update();
		}
	}

	void GameObject::LateUpdate() {
		for (Component* comp : mComponents) {
			comp->LateUpdate();
		}
	}

	void GameObject::Render(HDC hdc) {
		//HBRUSH randomBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand()%255));
		//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, randomBrush);
		//Ellipse(hdc, mX, mY, 100 + mX, 100 + mY);  

		//SelectObject(hdc, oldBrush);

		//DeleteObject(randomBrush);  //메모리 삭제

		for (Component* comp : mComponents) {
			comp->Render(hdc);
		}
	}

	GameObject::~GameObject() {

	}
}