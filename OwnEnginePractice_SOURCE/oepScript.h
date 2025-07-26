#pragma once
#include "oepComponent.h"

namespace oep {
	class Script : public Component
	{
	public:
		Script();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		//이 함수들은 스크립트를 작성할 때 상속을 받아서 사용하면 된다.
		virtual void OnCollisionEnter(class Collider* other);  //두 충돌체가 막 충돌해서 붙었을 때 호출할 함수
		virtual void OnCollisionStay(class Collider* other);  //두 충돌체가 충돌 후 지나가고 있을 때 즉, 겹쳐진 상태가 지속되고 있을 때 호출할 함수
		virtual void OnCollisionExit(class Collider* other);  //두 충돌체가 충돌하다가 완전히 빠져나갔을 때 호출할 함수(더 이상 충돌x)

		~Script();

	private:

	};
}
