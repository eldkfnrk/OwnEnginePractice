#pragma once
#include "oepLayer.h"
#include "oepGameObject.h"
#include "oepScene.h"
#include "oepSceneManager.h"
#include "oepTransform.h"

namespace oep::object {
	//지금까지의 프로그램은 오브젝트를 만들 때마다 오브젝트가 가지고 있어야 하는 컴포넌트들을 일일이 추가해주었다.
	//이젠 일일이 코드로 오브젝트를 생성하는 것이 아니라 함수를 하나 만들어서 이를 호출하는 것으로 알아서 오브젝트를 생성할 수 있도록 변경한다.
	//이때 기본적으로 가지고 있는 컴포넌트의 값을 초기화 해주는 것도 해줄 수 있으니 함수 호출 하나로 오브젝트 생성과 기본적으로 있는 컴포넌트의 값 설정까지 할 수 있어 코드를 간결하게 만들 수 있다.
	//이 함수를 쓰면 조금 더 쉽고 간결하게 게임 오브젝트를 생성할 수 있기 때문에 정의한 것으로 유니티에도 동일한 이름의 함수를 사용하여 오브젝트를 생성하도록 하고 있다.

	//그러기 위해서는 함수가 모든 오브젝트에 대응할 수 있어야 하기 때문에 템플릿 함수로 함수를 만들면 된다.
	//이때 static으로 만드는 이유는 전역 함수로써 여러 씬에서 자유롭게 함수를 호출할 수 있도록 하기 위해서이다.
	template <typename T>
	static T* Instantiate(enums::eLayerType type) {  //오브젝트의 레이어를 받아서 해당 레이어에 추가
		T* gameObj = new T();
		Scene* activeScene = SceneManager::GetActiveScene();  //굳이 어느 씬의 오브젝트인지를 인자를 받을 필요없이 씬이 생성되는 과정에서 활성화된 씬을 해당 씬으로 설정하고 이를 받으면 된다.
		Layer* layer = activeScene->GetLayer(type);

		//위치 정보 전달x -> 0,0으로 설정
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(0.0f, 0.0f));

		layer->AddGameObject(gameObj);
		
		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, math::Vector2 position) {  //오브젝트의 위치를 설정하면서 추가할 수 있도록 오버라이딩
		T* gameObj = new T();
		//씬의 오브젝트가 추가되는 시기는 오브젝트가 소속되는 씬이 활성화되는 시기이기 때문에 굳이 어떤 씬에서 오브젝트를 추가하는지 가져올 필요없이 
		//현재 활성화된 씬을 가져오면 자연스럽게 해당 씬에서 오브젝트가 생성될 수 있기 때문에 현재 활성화된 씬을 가져오는 것이다.
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);

		//위치 정보 전달o -> 해당 위치 정보로 설정
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(position);

		layer->AddGameObject(gameObj);

		return gameObj;
	}
}