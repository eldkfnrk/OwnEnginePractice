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
		
		//���� for���� ���� ��� for������ ����
		for (GameObject* gameObj : mGameObjects) {  //GameObject*��  auto�� �����ص� �ȴ�.
			//(auto�� �ڵ����� �˸´� �ڷ����� �����ִ� ������ �ڷ����� ��ų� �������� ��ġ�� ���. �׷���, ���� �ڷ������� �� �� ���� ��Ȳ�� �߻��� �� �־� �����ؼ� ����ؾ� �Ѵ�.)
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
