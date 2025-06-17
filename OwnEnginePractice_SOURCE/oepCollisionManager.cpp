#include "oepCollisionManager.h"
#include "oepScene.h"
#include "oepSceneManager.h"
#include "oepGameObject.h"
#include "oepCollider.h"

namespace oep {
	std::bitset<(UINT)eLayerType::Max> CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};

	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();  //현재 동작하고 있는 씬의 충돌 여부를 확인하는 것이기 때문에 현재 동작 중인 씬을 가지고 온다.
		//matrix를 순회하여 true인 경우만 충돌 여부 판단을 하도록 한다
		for (UINT row = 0; row < (UINT)eLayerType::Max; row++) {
			for (UINT col = 0; col < (UINT)eLayerType::Max; col++) {
				if (mCollisionLayerMatrix[row][col] == true) {
					//어느 씬의 어느 레이어 오브젝트 간의 충돌 여부를 체크하기 위해 이와 같이 인자를 전달한다.
					LayerCollision(scene, (eLayerType)row, (eLayerType)col);
				}
			}
		}
	}

	void CollisionManager::LateUpdate()
	{
	}

	void CollisionManager::Render(HDC hdc)
	{
	}

	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		//left와 right라는 이름으로 레이어 타입을 매개변수로 받는 이유는 아래에서 설명하겠다.
		//3x3 크기의 2차원 배열이 있다고 가정을 하자. 그러면 배열은 아래와 같아지게 된다.
		//  1  2  3
		//1
		//2
		//3
		//위와 같은 모습의 배열에서 1번과 3번을 충돌한다고 하면 1행 3열도 체크가 되고 3행 1열도 체크가 되는데 이는 결론적으로 둘이 충돌한다는 것을 의미한다.
		//그래서 한쪽만 체크를 해주면 되기 때문에 두 레이어 중 작은 레이어 쪽에다가만 표시해주기로 약속하여서 사용하기 위해 left와 right를 받아서 작은 쪽을
		//행으로 큰 쪽을 열로 사용하여 해당 요소만 체크를 하는 방식을 구현하기 위해서이다.(이렇게 하는 이유는 의미없는 메모리 낭비를 만들지 않기 위함이다.)
		//이러면 아래와 같이 3행 1열의 메모리를 사용하지 않을 수 있고 체크를 확인할 수 있다.
		//  1  2  3                        1  2  3
		//1 x  x  o                      1 x  x  o
		//2 x  x  x         --->         2    x  x
		//3 o  x  x                      3       x
		int row = 0;  //행
		int col = 0;  //열

		if (left <= right) {
			row = (UINT)left;
			col = (UINT)right;
		}
		else {
			row = (UINT)right;
			col = (UINT)left;
		}

		mCollisionLayerMatrix[row][col] = enable;  //해당 원소에 true나 false를 삽입
	}

	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		const std::vector<GameObject*>& lefts = scene->GetLayer(left)->GetGameObjects();
		const std::vector<GameObject*>& rights = scene->GetLayer(right)->GetGameObjects();

		//각 레이어 간의 모든 오브젝트들 검사
		for (GameObject* left : lefts) {
			//게임 오브젝트의 상태가 false라는 것은 화면에 안 보이게 해놓았다거나 사라질 예정이라는 것으로 충돌 검사를 할 필요가 없으니 넘어간다.
			if (left->IsActive() == false) {  
				continue;
			}

			Collider* leftCollider = left->GetComponent<Collider>();

			//게임 오브젝트가 Collider 컴포넌트가 없다면 이 오브젝트는 충돌체가 아니기 때문에 충돌 검사를 할 필요가 없으니 넘어간다.
			if (leftCollider == nullptr) {
				continue;
			}

			for (GameObject* right : rights) {
				//left와 마찬가지로 right도 위와 같은 경우들은 넘어가야 한다.
				if (right->IsActive() == false) {
					continue;
				}

				Collider* rightCollider = right->GetComponent<Collider>();

				if (rightCollider == nullptr) {
					continue;
				}

				//동일한 레이어끼리 충돌을 체크하는 경우 동일 레이어의 다른 오브젝트들은 체크를 해야하지만 레이어를 모두 순회를 하다보면 결국
				//자기자신끼리 충돌 체크를 하는 순서가 오게 되는데 이 경우는 당연히 체크를 할 필요가 없기 때문에 넘어간다.
				if (left == right) {
					continue;
				}

				//두 충돌체가 충돌하는지 체크
				ColliderCollision(leftCollider, rightCollider);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		//충돌 체크 로직

	}
}