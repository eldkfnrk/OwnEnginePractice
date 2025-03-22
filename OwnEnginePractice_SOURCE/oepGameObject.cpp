#include "oepGameObject.h"
#include "oepInput.h"
#include "oepTime.h"
#include "oepTransform.h"

namespace oep {
	GameObject::GameObject() {
		//Transform 컴포넌트는 모든 오브젝트가 가질 것이기 때문에 기본적으로 가지고 있을 수 있도록 오브젝트가 생성됨과 동시에 추가
		//AddComponent<Transform>();

		//위의 한 줄짜리 동작도 함수로 묶어놓는 습관을 기르는 것이 좋다.
		initializeTransform();
	}

	void GameObject::Initialize() {
		for (Component* comp : mComponents) {
			comp->Initialize();
		}
	}

	void GameObject::Update() {
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
		for (Component* comp : mComponents) {
			comp->Render(hdc);
		}
	}

	void GameObject::initializeTransform() {
		AddComponent<Transform>();
	}

	GameObject::~GameObject() {

	}
}