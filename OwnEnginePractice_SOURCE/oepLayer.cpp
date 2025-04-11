#include "oepLayer.h"

namespace oep {
	Layer::Layer() :mGameObjects{} {

	}

	void Layer::Initialize() {
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr) {
				continue;
			}

			gameObj->Initialize();
		}
	}

	void Layer::Update() {
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr) {
				continue;
			}

			gameObj->Update();
		}
	}

	void Layer::LateUpdate() {
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr) {
				continue;
			}

			gameObj->LateUpdate();
		}
	}

	void Layer::Render(HDC hdc) {
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr) {  
				continue;
			}
			
			gameObj->Render(hdc);
		}
	}

	void Layer::Destroy() {
		for (GameObjectIter iter = mGameObjects.begin(); iter != mGameObjects.end(); /*iter++*/) {
			//반복자는 해당 원소를 가리키는 포인터이기 때문에 해당 원소를 사용하려고 하면 이와 같이 포인터처럼 사용하여야 한다.
			GameObject::eState state = (*iter)->GetActive();  

			if (state == GameObject::eState::Dead) {
				GameObject* deathObj = (*iter);

				iter = mGameObjects.erase(iter);  //erase함수는 벡터의 삭제 연산 함수로 중간 원소도 삭제할 수 있는 함수
				//erase 함수는 벡터에서 원소를 제거함과 동시에 다음 원소의 반복자를 반환하기 때문에 위와 같이 for문의 변화식을 사용하면 다음 원소를 검사하지 않고 바로 
				//다음 원소를 검사하게 될 수 있기 때문에 iter에다가 다음 원소의 반복자를 저장하고 다음으로 넘겨야 한다.

				//오브젝트가 벡터에서 삭제됨과 동시에 해당 오브젝트의 메모리를 해제해주어야 메모리 누수가 발생하지 않는다.
				delete deathObj;
				deathObj == nullptr;

				continue;  //그러기 위해서 다음 순서로 바로 넘어가게 한다.
			}

			iter++;  //위에서 원소를 지우는 것을 하지 않으면 다음 원소로 넘어가도록 ++연산을 해준다.

			//즉, 이런 조건 때문에 변화식을 사용하지 않고 동작을 하는 부분에서 따로 진행해야 한다.
		}
	}

	void Layer::AddGameObject(GameObject* gameObj) {
		if (gameObj == nullptr) {  
			return;
		}

		mGameObjects.push_back(gameObj);
	}

	Layer::~Layer() {
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr) {
				continue;
			}
			delete gameObj;
			gameObj = nullptr;
		}
	}
}