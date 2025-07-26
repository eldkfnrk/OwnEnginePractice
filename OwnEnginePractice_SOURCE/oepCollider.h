#pragma once
#include "oepComponent.h"
#include "oepEnums.h"

namespace oep {
	using namespace enums;
	//Collider 클래스 - 오브젝트의 물리 충돌 처리를 위한 클래스
	//격투 게임을 예시로 보면 서로 공격을 하고 공격을 받으면 데미지를 받아 체력이 줄어드는 것을 알 수 있는데 이때 이 타격 판정을 위해 필요한 것이 바로 
	//물리 충돌을 처리하는 Collider 클래스인 것이다.
	//이 Collider는 보이도록 하면 판정을 이해하기 편하지만 그렇게 되면 화면이 Collider로 인해 난잡해지고 정확한 시각 정보 전달을 방해할 수도 있기 때문에
	//실제로는 우리 눈에 안 보이도록 만들게 되고 Collider는 반드시 오브젝트와 동일한 모습을 할 필요없이 대략적인 근사치 형태로 만들어주는게 효율적이다.
	//왜냐하면, 충돌체에 대한 연산이 오브젝트와 동일한 모습일 때보다 네모나 원 등으로 비슷하게 대응되도록 할 때의 연산이 더 간단해서 성능을 높일 수 있기 때문이다.
	class Collider : public Component
	{
	public:
		Collider(eColliderType type);

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);  //두 충돌체가 막 충돌해서 붙었을 때 호출할 함수
		virtual void OnCollisionStay(Collider* other);  //두 충돌체가 충돌 후 지나가고 있을 때 즉, 겹쳐진 상태가 지속되고 있을 때 호출할 함수
		virtual void OnCollisionExit(Collider* other);  //두 충돌체가 충돌하다가 완전히 빠져나갔을 때 호출할 함수(더 이상 충돌x)

		Vector2 GetOffset() {
			return mOffset;
		}

		void SetOffset(Vector2 offset) {
			mOffset = offset;
		}

		Vector2 GetSize() {
			return mSize;
		}

		void SetSize(Vector2 size) {
			mSize = size;
		}

		UINT32 GetID() {
			return mID;
		}

		eColliderType GetColliderType() {
			return mType;
		}

		~Collider();

	private:
		static UINT32 mCollisionID;  //충돌체가 생성되면 해당 충돌체에게 부여될 ID값(생성되는 순서대로 번호가 부여될 것이다.)
		UINT32 mID;  //충돌체 구분을 위한 충돌체 고유 ID
		Vector2 mOffset;  //모든 충돌체는 offset을 가진다.(offset = 오브젝트의 기준점)
		Vector2 mSize;
		eColliderType mType;  //해당 충돌체가 어떤 형태의 충돌체인지 구분하기 위한 변수(여기서는 원인지 직사각형인지를 구분)
	};
}
