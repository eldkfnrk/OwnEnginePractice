#include "oepLayer.h"

namespace oep {
	Layer::Layer() : /*mType(eLayerType::None),*/ mGameObjects{} {

	}

	//기존 씬에서 하던 동작을 그대로 하면 된다.
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

	void Layer::AddGameObject(GameObject* gameObj) {
		if (gameObj == nullptr) {  //게임 오브젝트가 nullptr이면 추가를 못하게 막는 방어 코드
			//왜냐하면 게임 오브젝트가 없는데 벡터에 들어가게 되면 위에서 하는 게임 오브젝트의 작업들이 게임 오브젝트가 없는 원소를 순회할 때 없는 것의 함수를 접근하려고 하니 문제가 발생할 수 있어서 그렇다.
			//모든 포인터 벡터가 for문으로 순회를 돌면 이런 일을 방지하기 위한 비슷한 방어 코드가 있어야 한다.(안 그러면 이유 모를 문제가 발생할 수 있다.)
			return;
		}

		mGameObjects.push_back(gameObj);
	}

	Layer::~Layer() {

	}
}