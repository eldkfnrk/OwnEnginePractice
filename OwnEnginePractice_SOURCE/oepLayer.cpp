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

			//오브젝트가 비활성화된 상태라면 건너뛰게 한다.
			if (gameObj->IsActive() == false) {
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

			//오브젝트가 비활성화된 상태라면 건너뛰게 한다.
			if (gameObj->IsActive() == false) {
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

			//오브젝트가 비활성화된 상태라면 건너뛰게 한다.
			if (gameObj->IsActive() == false) {
				continue;
			}
			
			gameObj->Render(hdc);
		}
	}

	void Layer::Destroy() {
		std::vector<GameObject*> deleteObjects = {};
		findDeadGameObjects(deleteObjects);
		deleteGameObjects(deleteObjects);
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

	void Layer::findDeadGameObjects(OUT std::vector<GameObject*>& gameObjs) {
		for (GameObject* gameObj : mGameObjects) {
			GameObject::eState active = gameObj->GetState();
			
			if (active == GameObject::eState::Dead) {
				gameObjs.push_back(gameObj);
			}
		}
	}

	void Layer::deleteGameObjects(std::vector<GameObject*> deleteObjs) {
		for (GameObject* obj : deleteObjs) {
			delete obj;
			obj = nullptr;
		}
	}
}