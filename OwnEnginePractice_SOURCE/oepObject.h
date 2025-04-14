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
	//그것을 하는 것이 바로 Destroy라는 것이다.
	void Destroy(GameObject* gameObj) {  //삭제할 오브젝트의 상태를 Dead로 변경(Dead 상태는 삭제 대상임을 알리는 상태이다.)
		//삭제할 대상을 인자로 받는다.
		if (gameObj != nullptr) {  //삭제할 대상이 있는 경우에만 되도록 설정(객체가 없어서 에러가 나는 것을 방지하는 코드)
			gameObj->death();
		}
	}

	//이렇게 게임 오브젝트를 게임 플레이 중간에 삭제하는 것까지 배웠는데 여기서 하나 알아야 하는 것이 메모리 할당과 해제 즉, new와 delete 연산이 복잡한 연산이기 때문에
	//연산 속도가 낮다. 그렇기 때문에 new와 delete가 많으면 그만큼 게임 플레이 중 끊기는 현상이라던지 또는 게임 멈춤 현상까지도 야기할 수 있다. 그래서 알아야 하는 것이
	//오브젝트 풀이다. 오브젝트 풀이란 하나의 오브젝트에 하위 오브젝트들을 모아두고 그 오브젝트들을 활성화했다가 비활성화했다가 하는 식으로 게임을 구현하는 방식을 말한다.
	//게임들을 보면 이펙트나 아이템 창 UI 등 생겼다가 사라졌다가를 반복하는 오브젝트들이 여러 개가 있다. 특히 이펙트 같은 경우 공격이나 스킬 이펙트가 있는 경우 해당 동작
	//을 할 때마다 이펙트를 보여주게 되고 해당 동작이 끝나면 없어지는데 이것들도 모두 오브젝트이니 지금까지처럼 new로 새로 이펙트 등에 해당하는 오브젝트를 매번 만들고
	//끝나면 delete를 해주게 되면 앞서 말했듯이 new와 delete 연산이 오래 걸리기 때문에 게임 끊김이나 멈춤 현상이 생길 수 있는 것이다. 그래서 이런 어떤 오브젝트에 속한
	//오브젝트들을 메모리 할당을 한 상태로 컨테이너에 모아서 가지고 있으면 new와 delete 연산을 하지 않아도 되니 속도가 조금 더 빠르게 만들 수 있는 것이다. 그리고 할당한
	//메모리는 게임을 종료시키면 함께 종료시키면 되니 메모리 누수 발생도 방지할 수 있어서 게임을 최적화할 때 필요한 방법 중 하나이다. 그래서 오브젝트 풀이라는 것을
	//사용하는 것인데 무조건 오브젝트 풀 사용이 좋은 것은 아니니 게임을 구현할 때 조금 더 나은 방향을 찾아서 상황에 따라 알맞게 사용하면 된다.

	//오브젝트 풀처럼 메모리 풀이라는 것도 있다. 메모리 풀은 게임 제작 반드시 new 연산이 있을 것이니 미리 사용할 메모리를 계산하여 계산한 메모리만큼 미리 할당을 받고
	//이 할당된 메모리를 new를 할 때 사용하는 것으로 미리 메모리를 할당받은 상태에서 새로 메모리 할당할 객체가 있다면 할당받은 메모리에 저장만 하면 된다.
	//이것이 가능한 이유는 new도 연산자이기 때문에 연산자 오버로딩이 가능하여 우리가 알맞게 기능을 변경한 상태로 사용할 수 있기 때문이다. 메모리를 미리 할당하고 
	//new 연산자를 이 할당한 메모리 상에 저장만 하도록 오버로딩 시켜놓으면 복잡한 new 연산으로의 시간 소모를 줄이고 미리 할당한 메모리에 저장만 하면 되기에 사용한다.
	//이 메모리 풀은 메모리를 직접 할당 가능한 C++같은 언어에서만 사용 가능하고 C#이나 자바는 사용이 불가능하다.

	//클라이언트 쪽에서는 오브젝트 풀링을 최적화하는 용도로 자주 쓰고 메모리 풀링은 서버 등의 부분에서 필요에 따라 사용하기도 한다.
}