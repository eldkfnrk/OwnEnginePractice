#include "oepScene.h"

namespace oep {
	Scene::Scene() : mLayers{}
	{
		mLayers.resize((UINT)eLayerType::Max);  //레이어를 저장한 벡터를 최대 값으로 설정한 값만큼 크기 재조정

		//배열 안 원소들을 메모리 할당
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

		//기존에 하던 동작은 게임 오브젝트 Update였다면 지금은 레이어 Update이다.(LateUpdate와 Render, Initialize도 마찬가지)
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
