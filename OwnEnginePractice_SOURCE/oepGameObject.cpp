#include "oepGameObject.h"
#include "oepInput.h"
#include "oepTime.h"
#include "oepTransform.h"

namespace oep {
	GameObject::GameObject() {
		//컴포넌트의 갯수만큼 크기 재설정 이때 동적 할당(동일한 컴포넌트가 2개씩 있을 수는 없기에 이 배열의 최대 크기는 프로그램의 컴포넌트 갯수)
		mComponents.resize((UINT)enums::eComponentType::End);  
		initializeTransform();
	}

	void GameObject::Initialize() {
		for (Component* comp : mComponents) {
			//이제는 벡터의 삽입한 만큼의 원소만 있는 것이 아니라 원소들이 NULL로 초기화된 배열에 지정된 컴포넌트 순서에 맞게 원소를 삽입
			//그러면서 해당되는 스크립트를 추가하지 않았다면 해당 스크립트의 순서에 있는 원소는 NULL일 것이고 그러면 없는 객체의 함수를 호출하는 것이 되니 그것을 막아주도록 하여야 한다.
			//이는 다른 동작들에서도 해당된다.
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