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

			GameObject::eState state = gameObj->GetActive();

			if (state == GameObject::eState::Paused || state == GameObject::eState::Dead) {
				//������Ʈ�� ��Ȱ��ȭ�� ���¶�� �ǳʶٰ� �Ѵ�.
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

			GameObject::eState state = gameObj->GetActive();

			if (state == GameObject::eState::Paused || state == GameObject::eState::Dead) {
				//������Ʈ�� ��Ȱ��ȭ�� ���¶�� �ǳʶٰ� �Ѵ�.
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

			GameObject::eState state = gameObj->GetActive();

			if (state == GameObject::eState::Paused || state == GameObject::eState::Dead) {
				//������Ʈ�� ��Ȱ��ȭ�� ���¶�� �ǳʶٰ� �Ѵ�.
				continue;
			}
			
			gameObj->Render(hdc);
		}
	}

	void Layer::Destroy() {
		for (GameObjectIter iter = mGameObjects.begin(); iter != mGameObjects.end(); ) {
			GameObject::eState state = (*iter)->GetActive();  

			if (state == GameObject::eState::Dead) {
				GameObject* deathObj = (*iter);

				iter = mGameObjects.erase(iter);  

				delete deathObj;
				deathObj = nullptr;

				continue;  
			}

			iter++;  
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