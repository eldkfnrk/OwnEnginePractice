#pragma once
#include "oepComponent.h"

namespace oep {
	using namespace oep::math;

	class Camera : public Component
	{
	public:
		Camera();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		//오브젝트의 위치 정보를 인자로 받아 카메라의 이동 거리를 빼서 오브젝트의 위치를 구하는 함수
		Vector2 CalculatePosition(Vector2 pos) {
			return pos - mDistance;
		}

		void SetTarget(GameObject* target) {
			mTarget = target;
		}

		~Camera();

	private:
		class GameObject* mTarget;  

		Vector2 mDistance;  //카메라와 카메라가 비추는 대상의 거리
		Vector2 mResolution;  //화면 해상도
		Vector2 mLookPosition;  //카메라가 바라보는 위치 정보
	};
}
