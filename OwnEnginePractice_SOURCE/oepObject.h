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

		//오브젝트에서 Transform 컴포넌트를 추가할 때 기본적으로 0,0으로 생성하기 때문에 굳이 아래 코드를 추가할 필요는 없었다.
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