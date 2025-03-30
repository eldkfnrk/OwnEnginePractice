#pragma once
#include "oepComponent.h"

namespace oep {
	using namespace math;  

	class Transform : public Component
	{
	public:
		Transform();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetPosition(Vector2 pos) {
			mPosition.x = pos.x;
			mPosition.y = pos.y;
		}

		Vector2 GetPosition() {
			return mPosition;
		}

		void SetRotation(float rotation) {
			mRotation = rotation;
		}

		float GetRotation() {
			return mRotation;
		}
		
		void SetScale(Vector2 scale) {
			mScale.x = scale.x;
			mScale.y = scale.y;
		}

		Vector2 GetScale() {
			return mScale;
		}

		~Transform();

	private:
		//Transform 컴포넌트가 이제부턴 오브젝트의 위치 정보 뿐만 아니라 오브젝트의 크기와 각도까지 모두 위임받아 관리하도록 수정
		Vector2 mPosition;  
		Vector2 mScale;  //이 컴포넌트를 가지고 있는 오브젝트의 크기
		float mRotation;  //오브젝트의 각도(회전)
	};
}
