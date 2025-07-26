#pragma once
#include "CommonInclude.h"
#include "oepBoxCollider2D.h"
#include "oepCircleCollider2D.h"

namespace oep {
	using namespace enums;

	//union은 공용체라는 것으로 간단하게 설명하면 데이터를 묶어서 사용하는 것도 가능하고 쪼개서 사용하는 것도 가능한 문법이다.
	//조금 더 자세하게 설명하면 공용체는 구조체랑 거의 동일하지만 모든 멤버 변수가 하나의 메모리 공간을 공유한다는 차이점이 있는데 이는 내부에 여러
	//타입 변수 선언을 할 수 있지만 실제 사용 시에는 하나의 멤버 변수만 사용할 수 있는 것이다.
	//공용체의 크기는 멤버 변수 중 가장 크기가 큰 변수의 크기로 아무리 여러 타입의 변수를 선언해도 크기는 커지지 않기 때문에 메모리 절약을 목적으로 사용한다.
	//즉, 공용체는 하나의 변수값만을 저장할 수 있고 다른 타입의 멤버 변수가 이 값을 사용할 땐 그 변수의 크기만큼만 데이터를 나눠서 사용하는 것이다.
	//그렇기 때문에 공용체는 데이터를 묶어서도 사용할 수 있고 분리해서도 사용할 수 있는 변수라고 볼 수 있다.
	union CollisionID {
		struct {  //이 구조체도 하나의 멤버 변수이다.
			//left와 right는 각각 오브젝트의 ID
			UINT32 left;
			UINT32 right;
		};

		//id는 left와 right의 값이 합쳐진 값이 될 것이고 이 두 충돌체 간의 충돌 상황을 구분하는 ID로 사용할 것이다.
		UINT64 id;
	};

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
		static bool Intersect(Collider* left, Collider* right);

	private:
		//모든 충돌체를 모두 체크할 수 없기 때문에 상용 엔진에서는 레이어 간 충돌 여부를 나누어서 충돌 확인
		//그리고 이 충돌 여부는 2차원 배열을 이용하여 저장하고 사용
		//이때 배열 한 요소들을 비트 단위로 쪼개서 사용할 수 있도록 비트 연산을 활용
		//matrix는 행렬이라는 뜻이다(즉, 레이어 간 충돌 여부 행렬이라는 뜻)
		//bitset은 보다 편리하게 비트를 활용한 배열 생성이 가능하도록 추가된 stl로 원소 하나가 1비트 크기이기 때문에 이런 체크됐는지 확인만 하는
		//역할의 배열같은 것에서 사용하기 용이하다.(이게 없었다면 모든 가능성을 확인하기 위한 연산이 필요했을 것인데 이 작업을 줄여주었다.)
		//아래와 같이 만든 것은 2차원 배열로 []를 사용하지 않으면 1차원 배열인 것이다.
		static std::bitset<(UINT)eLayerType::Max> mCollisionLayerMatrix[(UINT)eLayerType::Max];  

		//오브젝트 간 충돌 중인지 체크하기 위한 bool 변수가 필요할 것이고 이를 저장하기 위한 unordered_map을 하나 선언
		static std::unordered_map<UINT64, bool> mCollisionMap;
	};
}
