#include "oepCollisionManager.h"
#include "oepScene.h"
#include "oepSceneManager.h"
#include "oepGameObject.h"
#include "oepCollider.h"
#include "oepTransform.h"

namespace oep {
	std::bitset<(UINT)eLayerType::Max> CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};
	std::unordered_map<UINT64, bool> CollisionManager::mCollisionMap = {};

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
		//두 충돌체의 ID를 확인해서 CollisionID값을 세팅
		CollisionID id = {};  //이 변수값이 두 충돌체 간 충돌 상황을 구분할 ID값
		id.left = left->GetID();
		id.right = right->GetID();

		//해당 ID로 충돌체 정보를 검색
		//왜냐하면, 만약 충돌체 간 충돌 상황 정보가 없다면 충돌 정보를 생성해주어야 하기 때문이다.
		//unordered_map에 해당 정보가 있는지 확인하기 위한 것으로 이 키값을 가진 정보가 있다면 second 값을 없다면 end()을 저장할 것이다.
		auto iter = mCollisionMap.find(id.id);  
		if (iter == mCollisionMap.end()) {
			mCollisionMap.insert(std::make_pair(id.id, false));  //충돌을 아직 한 상태는 아니기 때문에 false를 넣어서 생성 후 삽입해준다.
			iter = mCollisionMap.find(id.id);
		}

		//충돌 체크
		if (Intersect(left, right)) {  //충돌했으면 true 아니면 false
			//충돌 여부 체크
			if (iter->second == false) {  //이전 프레임까지는 충돌하지 않았던 상태(최초 충돌 상태를 의미)
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
			else {  //충돌 중인 상태를 의미
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else {
			//충돌 여부 체크
			if (iter->second == true) {  //이전 프레임까지는 계속 충돌 중이었던 상태(충돌 상태에서 벗어났음을 의미)
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				iter->second = false;
			}
		}
	}

	//두 충돌체 간 충돌을 하는지에 대한 연산 결과를 표현하기 위한 함수
	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		//충돌체들이 충돌하고 있는지 여부를 체크
		//이때 사각형 충돌체 간 충돌 로직은 AABB라고 하는 직사각형끼리의 충돌 체크를 해주는 알고리즘을 사용
		//AABB는 Axis-Aligned Bounding Box의 줄임말로 축이 나란한 경계상자 박스라 생각하면 된다. 이는 박스를 이루는 모든 사각형의 축들은 일치한다는 의미로
		//회전에 따라 사각형이 같이 회전하지는 않지만 크기는 변하게 한다. 크기 변화가 계속되기 때문에 큰 부담은 아니지만 성능 상 부담이 될 수도 있다.
		//이 방식의 충돌 체크 방법은 x축의 변끼리 비교해보고 y축의 변끼리 비교해서 겹치면 충돌 판정을 내는 방식이다. 좀 더 이해하기 쉽게 표현하자면 사각형의 
		//중점을 기준으로 두 사각형의 중점의 x거리를 구하고 이 x거리와 각 사각형의 x축 변의 1/2 길이를 합친 값을 비교해서 x거리가 길면 충돌이 아니고 같거나 짧으면 충돌로
		//판정되는 것이다. y축도 마찬가지로 비교해서 x축 비교와 y축 비교 둘 중 하나라도 충돌 판정이 나면 충돌 처리를 하는 것이다.
		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		//각 사각형의 시작점 위치 저장
		Vector2 leftPos = leftTr->GetPosition() + left->GetOffset();
		Vector2 rightPos = rightTr->GetPosition() + right->GetOffset(); 

		//size가 1,1일 경우 기본 크기가 100픽셀이다.
		Vector2 leftSize = left->GetSize() * 100.0f;
		Vector2 rightSize = right->GetSize() * 100.0f;

		enums::eColliderType leftType = left->GetColliderType();
		enums::eColliderType rightType = right->GetColliderType();

		//AABB층돌(fabs()는 부동소수점 인수의 절대값을 연산하는 함수 -> 즉, 실수의 절대값을 반환하는 함수)
		//직사각형과 직사각형의 충돌체 충돌 검사
		if (leftType == enums::eColliderType::Rect2D && rightType == enums::eColliderType::Rect2D) {
			if (fabs(leftPos.x - rightPos.x) <= fabs(leftSize.x / 2.0f + rightSize.x / 2.0f) 
				&& fabs(leftPos.y - rightPos.y) <= fabs(leftSize.y / 2.0f + rightSize.y / 2.0f)) {
				return true;
			}
		}

		//원과 원의 충돌체 충돌 검사
		//원의 충돌 검사는 각 원의 중점 사이 거리와 각 원의 반지름의 합으로 검사한다.(구(shape)도 똑같은데 이 방법은 정확하지는 않지만 제일 빠른 방법이다.)
		if (leftType == enums::eColliderType::Circle2D && rightType == enums::eColliderType::Circle2D) {
			//각 원의 중점 위치를 찾아서 저장
			Vector2 leftCirclePos = leftPos + (leftSize / 2.0f);
			Vector2 rightCirclePos = rightPos + (rightSize / 2.0f);

			float distance = (leftCirclePos - rightCirclePos).Length();
			if (distance <= (leftSize.x / 2.0f + rightSize.x / 2.0f)) {  //원의 중점 간 거리와 각 원의 반지름의 합을 비교
				return true;
			}
		}

		//원과 사각형의 충돌체 충돌 검사
		//이 경우에는 지금까지와는 살짝 다른 방법을 사용하여야 한다. 사각형을 그대로 사용하는 것이 아니라 상하좌우로 원의 반지름만큼 키운 가상의 사각형
		if ((leftType == enums::eColliderType::Circle2D && rightType == enums::eColliderType::Rect2D)
			|| (leftType == enums::eColliderType::Rect2D && rightType == enums::eColliderType::Circle2D)) {
			Vector2 rectPos;
			Vector2 circlePos;
			Vector2 rectSize;
			Vector2 circleSize;

			if (leftType == enums::eColliderType::Rect2D) {
				rectPos = leftPos;  
				circlePos = rightPos + (rightSize / 2.0f);  //원의 중점
				rectSize = leftSize;
				circleSize = rightSize;
			}
			else {
				rectPos = rightPos;  
				circlePos = leftPos + (leftSize / 2.0f);  //원의 중점
				rectSize = rightSize;
				circleSize = leftSize;
			}

			//원과 사각형의 충돌은 원의 반지름만큼 사각형의 크기를 키우고 원의 중심이 이 사각형 안에 들어가 있는지를 두고 충돌을 판정한다.
			//그러나 예외적으로 각 꼭지점들은 따로 연산을 해주어야 하는데 그 이유는 꼭지점 부근에서는 원의 중점이 안에 들어가 있어도 실제로는 닿지
			//않은 경우가 있기 때문이다. 그래서 꼭지점은 원의 중점과의 거리를 계산하는 방식으로 따로 연산을 해주어야 한다.
			//그러니 해줘야 할 연산은 두 가지이다. 그것은 원의 중점이 사각형을 원의 반지름만큼 확장한 사각형 안에 있는지를 체크하는 것과 
			//각 꼭지점과 원의 중점의 거리가 반지름보다 작은지 체크하는 것이다.
			float radius = circleSize.x / 2.0f;  //원의 반지름
			Vector2 leftTop;
			Vector2 leftBottom;
			Vector2 rightTop;
			Vector2 rightBottom;
			
			leftTop = rectPos;

			leftBottom.x = rectPos.x;
			rightTop.x = rectPos.x + rectSize.x;
			rightBottom.x = rectPos.x + rectSize.x;
			
			leftBottom.y = rectPos.y + rectSize.y;
			rightTop.y = rectPos.y;
			rightBottom.y = rectPos.y + rectSize.y;

			float leftTopDistance = (circlePos - leftTop).Length();
			float leftBottomDistance = (circlePos - leftBottom).Length();
			float rightTopDistance = (circlePos - rightTop).Length();
			float rightBottomDistance = (circlePos - rightBottom).Length();

			if (radius >= leftTopDistance ||
				radius >= leftBottomDistance ||
				radius >= rightTopDistance ||
				radius >= rightBottomDistance) {
				//꼭지점과 원의 중심 간의 거리가 원의 반지름보다 작은지 확인하여 작으면 true를 반환해준다.
				return true;
			}

			if ((circlePos.x >= leftTop.x - radius
				&& circlePos.x <= rightTop.x + radius) &&
				(circlePos.y >= leftTop.y - radius
				&& circlePos.y <= rightBottom.y + radius)) {
				//원의 반지름만큼 확장한 사각형 안에 원의 중점이 있는지 확인하여 안에 있으면 true를 반환해준다.
				return true;
			}
		}

		return false;
	}
}