#pragma once
#include "CommonInclude.h"
#include "oepBoxCollider2D.h"
#include "oepCircleCollider2D.h"

namespace oep {
	using namespace enums;

	//충돌체의 충돌 등을 관리하는 클래스
	class CollisionManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

		static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable);
		static void LayerCollision(class Scene* scene, eLayerType left, eLayerType right);
		static void ColliderCollision(Collider* left, Collider* right);

	private:
		//모든 충돌체를 모두 체크할 수 없기 때문에 상용 엔진에서는 레이어 간 충돌 여부를 나누어서 충돌 확인
		//그리고 이 충돌 여부는 2차원 배열을 이용하여 저장하고 사용
		//이때 배열 한 요소들을 비트 단위로 쪼개서 사용할 수 있도록 비트 연산을 활용
		//matrix는 행렬이라는 뜻이다(즉, 레이어 간 충돌 여부 행렬이라는 뜻)
		//bitset은 보다 편리하게 비트를 활용한 배열 생성이 가능하도록 추가된 stl로 원소 하나가 1비트 크기이기 때문에 이런 체크됐는지 확인만 하는
		//역할의 배열같은 것에서 사용하기 용이하다.(이게 없었다면 모든 가능성을 확인하기 위한 연산이 필요했을 것인데 이 작업을 줄여주었다.)
		//아래와 같이 만든 것은 2차원 배열로 []를 사용하지 않으면 1차원 배열인 것이다.
		static std::bitset<(UINT)eLayerType::Max> mCollisionLayerMatrix[(UINT)eLayerType::Max];  
	};
}
