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
			//�ݺ��ڴ� �ش� ���Ҹ� ����Ű�� �������̱� ������ �ش� ���Ҹ� ����Ϸ��� �ϸ� �̿� ���� ������ó�� ����Ͽ��� �Ѵ�.
			GameObject::eState state = (*iter)->GetActive();  

			if (state == GameObject::eState::Dead) {
				GameObject* deathObj = (*iter);

				iter = mGameObjects.erase(iter);  //erase�Լ��� ������ ���� ���� �Լ��� �߰� ���ҵ� ������ �� �ִ� �Լ�
				//erase �Լ��� ���Ϳ��� ���Ҹ� �����԰� ���ÿ� ���� ������ �ݺ��ڸ� ��ȯ�ϱ� ������ ���� ���� for���� ��ȭ���� ����ϸ� ���� ���Ҹ� �˻����� �ʰ� �ٷ� 
				//���� ���Ҹ� �˻��ϰ� �� �� �ֱ� ������ iter���ٰ� ���� ������ �ݺ��ڸ� �����ϰ� �������� �Ѱܾ� �Ѵ�.

				//������Ʈ�� ���Ϳ��� �����ʰ� ���ÿ� �ش� ������Ʈ�� �޸𸮸� �������־�� �޸� ������ �߻����� �ʴ´�.
				delete deathObj;
				deathObj == nullptr;

				continue;  //�׷��� ���ؼ� ���� ������ �ٷ� �Ѿ�� �Ѵ�.
			}

			iter++;  //������ ���Ҹ� ����� ���� ���� ������ ���� ���ҷ� �Ѿ���� ++������ ���ش�.

			//��, �̷� ���� ������ ��ȭ���� ������� �ʰ� ������ �ϴ� �κп��� ���� �����ؾ� �Ѵ�.
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