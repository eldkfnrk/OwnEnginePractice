#pragma once
#include "oepComponent.h"

namespace oep {
	//Collider 클래스 - 오브젝트의 물리 충돌 처리를 위한 클래스
	//격투 게임을 예시로 보면 서로 공격을 하고 공격을 받으면 데미지를 받아 체력이 줄어드는 것을 알 수 있는데 이때 이 타격 판정을 위해 필요한 것이 바로 
	//물리 충돌을 처리하는 Collider 클래스인 것이다.
	//이 Collider는 보이도록 하면 판정을 이해하기 편하지만 그렇게 되면 화면이 Collider로 인해 난잡해지고 정확한 시각 정보 전달을 방해할 수도 있기 때문에
	//실제로는 우리 눈에 안 보이도록 만들게 되고 Collider는 반드시 오브젝트와 동일한 모습을 할 필요없이 대략적인 근사치 형태로 만들어주는게 효율적이다.
	//왜냐하면, 충돌체에 대한 연산이 오브젝트와 동일한 모습일 때보다 네모나 원 등으로 비슷하게 대응되도록 할 때의 연산이 더 간단해서 성능을 높일 수 있기 때문이다.
	class Collider : public Component
	{
	public:
		Collider();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetOffset(Vector2 offset) {
			mOffset = offset;
		}

		Vector2 GetOffset() {
			return mOffset;
		}

		~Collider();

	private:
		Vector2 mOffset;  //모든 충돌체는 offset을 가진다.(offset = 오브젝트의 기준점)
	};
}
