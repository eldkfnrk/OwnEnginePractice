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

	GameObject::~GameObject() {

	}
}