#include "oepScene.h"

namespace oep {
	Scene::Scene() : mLayers{}
	{
		createLayers();
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
		for (Layer* layer : mLayers) {
			if (layer == nullptr) {
				continue;
			}

			layer->Update();
		}
	}

	void Scene::LateUpdate() {
		for (Layer* layer : mLayers) {
			if (layer == nullptr) {
				continue;
			}

			layer->LateUpdate();
		}
	}

	void Scene::Render(HDC hdc) {
		for (Layer* layer : mLayers) {
			if (layer == nullptr) {
				continue;
			}

			layer->Render(hdc);
		}
	}

	void Scene::Destroy() {
		for (Layer* layer : mLayers) {
			if (layer == nullptr) {
				continue;
			}

			layer->Destroy();
		}
	}

	void Scene::OnEnter() {

	}

	void Scene::OnExit() {

	}

	void Scene::AddGameObject(GameObject* gameObj, const enums::eLayerType type) {
		if (gameObj == nullptr) {
			return;
		}

		mLayers[(UINT)type]->AddGameObject(gameObj);
	}

	void Scene::createLayers() {
		mLayers.resize((UINT)enums::eLayerType::Max);

		for (size_t i = 0; i < (UINT)enums::eLayerType::Max; i++) {
			mLayers[i] = new Layer();
		}
	}

	Scene::~Scene()
	{
		for (Layer* layer : mLayers) {
			delete layer;
			layer = nullptr;
		}
	}
}
