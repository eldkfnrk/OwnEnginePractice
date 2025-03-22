#include "oepScene.h"

namespace oep {
	Scene::Scene() : mLayers{}
	{
		mLayers.resize((UINT)eLayerType::Max);  //���̾ ������ ���͸� �ִ� ������ ������ ����ŭ ũ�� ������

		//�迭 �� ���ҵ��� �޸� �Ҵ�
		for (size_t i = 0; i < (UINT)eLayerType::Max; i++) {
			mLayers[i] = new Layer();
		}
	}

	void Scene::Initialize() {
		for (Layer* layer : mLayers) {
			if (layer == nullptr) {
				continue;
			}

			layer->Initialize();
		}
	}

	void Scene::Update() {
		//for (GameObject* gameObj : mGameObjects) {
		//	gameObj->Update();
		//}

		//������ �ϴ� ������ ���� ������Ʈ Update���ٸ� ������ ���̾� Update�̴�.(LateUpdate�� Render, Initialize�� ��������)
		for (Layer* layer : mLayers) {
			if (layer == nullptr) {
				continue;
			}

			layer->Update();
		}
	}

	void Scene::LateUpdate() {
		//for (GameObject* gameObj : mGameObjects) {
		//	gameObj->LateUpdate();
		//}

		for (Layer* layer : mLayers) {
			if (layer == nullptr) {
				continue;
			}

			layer->LateUpdate();
		}
	}

	void Scene::Render(HDC hdc) {
		//for (GameObject* gameObj : mGameObjects) {
		//	gameObj->Render(hdc);
		//}

		for (Layer* layer : mLayers) {
			if (layer == nullptr) {
				continue;
			}

			layer->Render(hdc);
		}
	}

	void Scene::OnEnter() {

	}

	void Scene::OnExit() {

	}

	//void Scene::AddGameObject(GameObject* gameObj) {
	//	mGameObjects.push_back(gameObj);
	//}

	void Scene::AddGameObject(GameObject* gameObj, const eLayerType type) {
		if (gameObj == nullptr) {
			return;
		}

		mLayers[(UINT)type]->AddGameObject(gameObj);
	}

	Scene::~Scene()
	{

	}
}
