#pragma once
#include "oepLayer.h"
#include "oepGameObject.h"
#include "oepScene.h"
#include "oepSceneManager.h"
#include "oepTransform.h"

namespace oep::object {
	template <typename T>
	static T* Instantiate(enums::eLayerType type) {  
		T* gameObj = new T();
		Scene* activeScene = SceneManager::GetActiveScene();  
		Layer* layer = activeScene->GetLayer(type);

		layer->AddGameObject(gameObj);
		
		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, math::Vector2 position) {  
		T* gameObj = new T();
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);

		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(position);

		layer->AddGameObject(gameObj);

		return gameObj;
	}

	//������ �ϴ� ���� ���� ������Ʈ���� ���� ������ �����ȴ�. ���� ��� RPG���� ���͸� ������ ���Ͱ� �������鼭 �������� ����Ѵ�. �̶� ���� ������Ʈ�� ������ ���̴�
	//���α׷� �󿡼� �޸𸮸� ��������� �� �ʿ䰡 �ִ�. �׷��� ������ �޸� ������ �߻��ϰ� �Ǳ� �����̴�. �׷��� �̰��� ����� ������ �����ε� ���� ���� �� ������Ʈ 
	//�������� ������Ʈ�� �����ϰ� ���ٵ� �׷��� LateUpdate�� ���� �������� ������Ʈ�� ������ ������ ���ư��ٵ� �̹� �޸� �� �������� �ʴ� ������Ʈ�̱� ������ ���� 
	//��ü�� �Լ��� ����Ϸ� �ϴ� ������ �߻��� ���̴�. �̷� ������ �ذ��ϱ� ���ؼ� ������Ʈ �������� ������ ������Ʈ���� ���� ��Ƽ� �����صξ��ٰ� ��� ������ �����ϰ� 
	//���� ���������� �Ѿ�� ���� ��Ƶξ��� ������Ʈ���� �� ���� ���������ָ� �������� ���� �� ������Ʈ ������ ������ �� �ִ�. �̷��� ���ؼ� ���� �۾��� ���־�� �Ѵ�.

	void Destroy(GameObject* gameObj) {  //������ ������Ʈ�� ���¸� Dead�� ����(Dead ���´� ���� ������� �˸��� �����̴�.)
		//������ ����� ���ڷ� �޴´�.
		if (gameObj != nullptr) {  //������ ����� �ִ� ��쿡�� �ǵ��� ����(��ü�� ��� ������ ���� ���� �����ϴ� �ڵ�)
			gameObj->death();
		}
	}
}