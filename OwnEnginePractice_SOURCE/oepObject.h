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

	//게임을 하다 보면 게임 오브젝트들이 여러 이유로 삭제된다. 예를 들면 RPG에서 몬스터를 잡으면 몬스터가 없어지면서 아이템을 드랍한다. 이때 몬스터 오브젝트는 없어진 것이니
	//프로그램 상에서 메모리를 삭제해줘야 할 필요가 있다. 그러지 않으면 메모리 누수가 발생하게 되기 때문이다. 그러나 이것을 지우는 과정이 문제인데 게임 로직 상 업데이트 
	//과정에서 오브젝트를 삭제하게 될텐데 그러면 LateUpdate나 렌더 과정에서 오브젝트를 가지고 로직이 돌아갈텐데 이미 메모리 상 존재하지 않는 오브젝트이기 때문에 없는 
	//객체의 함수를 사용하려 하니 에러가 발생할 것이다. 이런 문제를 해결하기 위해서 업데이트 과정에서 삭제될 오브젝트들을 따로 모아서 저장해두었다가 모든 로직을 수행하고 
	//다음 프레임으로 넘어가기 전에 모아두었던 오브젝트들을 한 번에 삭제시켜주면 문제없이 게임 중 오브젝트 삭제를 진행할 수 있다. 이러기 위해선 따로 작업을 해주어야 한다.

	void Destroy(GameObject* gameObj) {  //삭제할 오브젝트의 상태를 Dead로 변경(Dead 상태는 삭제 대상임을 알리는 상태이다.)
		//삭제할 대상을 인자로 받는다.
		if (gameObj != nullptr) {  //삭제할 대상이 있는 경우에만 되도록 설정(객체가 없어서 에러가 나는 것을 방지하는 코드)
			gameObj->death();
		}
	}
}