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

		//������Ʈ���� Transform ������Ʈ�� �߰��� �� �⺻������ 0,0���� �����ϱ� ������ ���� �Ʒ� �ڵ带 �߰��� �ʿ�� ������.
		//Transform* tr = gameObj->GetComponent<Transform>();
		//tr->SetPosition(math::Vector2(0.0f, 0.0f));

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
}