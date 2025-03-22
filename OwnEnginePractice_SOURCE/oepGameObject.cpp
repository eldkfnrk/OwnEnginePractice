#include "oepGameObject.h"
#include "oepInput.h"
#include "oepTime.h"
#include "oepTransform.h"

namespace oep {
	GameObject::GameObject() {
		//Transform ������Ʈ�� ��� ������Ʈ�� ���� ���̱� ������ �⺻������ ������ ���� �� �ֵ��� ������Ʈ�� �����ʰ� ���ÿ� �߰�
		//AddComponent<Transform>();

		//���� �� ��¥�� ���۵� �Լ��� ������� ������ �⸣�� ���� ����.
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