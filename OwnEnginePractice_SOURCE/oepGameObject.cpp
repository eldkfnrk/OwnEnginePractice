#include "oepGameObject.h"
#include "oepInput.h"
#include "oepTime.h"
#include "oepTransform.h"

namespace oep {
	GameObject::GameObject() {
		//������Ʈ�� ������ŭ ũ�� �缳�� �̶� ���� �Ҵ�(������ ������Ʈ�� 2���� ���� ���� ���⿡ �� �迭�� �ִ� ũ��� ���α׷��� ������Ʈ ����)
		mComponents.resize((UINT)enums::eComponentType::End);  
		initializeTransform();
	}

	void GameObject::Initialize() {
		for (Component* comp : mComponents) {
			//������ ������ ������ ��ŭ�� ���Ҹ� �ִ� ���� �ƴ϶� ���ҵ��� NULL�� �ʱ�ȭ�� �迭�� ������ ������Ʈ ������ �°� ���Ҹ� ����
			//�׷��鼭 �ش�Ǵ� ��ũ��Ʈ�� �߰����� �ʾҴٸ� �ش� ��ũ��Ʈ�� ������ �ִ� ���Ҵ� NULL�� ���̰� �׷��� ���� ��ü�� �Լ��� ȣ���ϴ� ���� �Ǵ� �װ��� �����ֵ��� �Ͽ��� �Ѵ�.
			//�̴� �ٸ� ���۵鿡���� �ش�ȴ�.
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
			delete comp;
			comp == nullptr;
		}
	}
}