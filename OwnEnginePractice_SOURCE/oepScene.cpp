#include "oepScene.h"

namespace oep {
	Scene::Scene()
	{

	}

	void Scene::Initialize(){

	}

	void Scene::Update() {
		//for (size_t i = 0; i < mGameObjects.size(); i++) {
		//	mGameObjects[i]->Update();
		//}
		
		//위의 for문을 범위 기반 for문으로 수정
		for (GameObject* gameObj : mGameObjects) {  //GameObject*는  auto로 수정해도 된다.
			//(auto는 자동으로 알맞는 자료형을 맞춰주는 것으로 자료형이 길거나 가독성을 해치면 사용. 그러나, 무슨 자료형인지 알 수 없는 상황이 발생할 수 있어 유의해서 사용해야 한다.)
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
