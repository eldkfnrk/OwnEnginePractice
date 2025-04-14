#include "oepGameObject.h"
#include "oepInput.h"
#include "oepTime.h"
#include "oepTransform.h"

namespace oep {
	GameObject::GameObject() : mState(eState::Active) {
		mComponents.resize((UINT)enums::eComponentType::End);  
		initializeTransform();
	}

	void GameObject::Initialize() {
		for (Component* comp : mComponents) {
			if (comp == nullptr) {  
				continue;
			}

			comp->Initialize();
		}
	}

	void GameObject::Update() {
		for (Component* comp : mComponents) {
			if (comp == nullptr) {
				continue;
			}

			comp->Update();
		}
	}

	void GameObject::LateUpdate() {
		for (Component* comp : mComponents) {
			if (comp == nullptr) {
				continue;
			}

			comp->LateUpdate();
		}
	}

	void GameObject::Render(HDC hdc) {
		for (Component* comp : mComponents) {
			if (comp == nullptr) {
				continue;
			}

			comp->Render(hdc);
		}
	}

	void GameObject::initializeTransform() {
		AddComponent<Transform>();
	}

	GameObject::~GameObject() {
		for (Component* comp : mComponents) {
			if (comp == nullptr) {
				//���� ������Ʈ���� ������Ʈ�� ������ �� ������Ʈ���� �߰��� �͸� ���Ϳ� ������ ���� �ƴ϶� ������Ʈ�� ������Ʈ ������ ��Ű�� ���� ������Ʈ��
				//������ �°� �߰��Ͽ� �ش� ������Ʈ�� ������ �� �ε����� ����ִ� ������� ���Ϳ� �����߱� ������ ����ִ� �ε����� ���� �� �־ �ƹ��͵� ���� ����
				//�޸� ������ �� ������ ��������� �Ѿ���� �������־�� �Ѵ�.
				continue;
			}

			delete comp;
			comp == nullptr;
		}
	}
}