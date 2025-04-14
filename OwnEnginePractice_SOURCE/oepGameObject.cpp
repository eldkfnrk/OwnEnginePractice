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
				//게임 오브젝트에서 컴포넌트를 저장할 때 컴포넌트들을 추가한 것만 벡터에 저장한 것이 아니라 컴포넌트의 업데이트 순서를 지키기 위해 컴포넌트의
				//순서에 맞게 추가하여 해당 컴포넌트가 없으면 그 인덱스는 비어있는 방식으로 벡터에 저장했기 때문에 비어있는 인덱스가 있을 수 있어서 아무것도 없는 것을
				//메모리 해제할 순 없으니 비어있으면 넘어가도록 설정해주어야 한다.
				continue;
			}

			delete comp;
			comp == nullptr;
		}
	}
}