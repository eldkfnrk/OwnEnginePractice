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

	void Layer::AddGameObject(GameObject* gameObj) {
		if (gameObj == nullptr) {  
			return;
		}

		mGameObjects.push_back(gameObj);
	}

	Layer::~Layer() {

	}
}