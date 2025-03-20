#include "oepScene.h"

namespace oep {
	Scene::Scene()
	{

	}

	void Scene::Initialize(){

	}

	void Scene::Update() {
		for (GameObject* gameObj : mGameObjects) { 
			gameObj->Update();
		}
	}

	void Scene::LateUpdate() {
		for (GameObject* gameObj : mGameObjects) {
			gameObj->LateUpdate();
		}
	}

	void Scene::Render(HDC hdc) {
		for (GameObject* gameObj : mGameObjects) {
			gameObj->Render(hdc);
		}
	}

	void Scene::AddGameObject(GameObject* gameObj) {
		mGameObjects.push_back(gameObj);
	}

	Scene::~Scene()
	{

	}
}
