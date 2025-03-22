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

		~Transform();

	private:
		Vector2 mPosition;  //구조체 생성자 안에서 초기화 해주고 있기 때문에 굳이 따로 이 클래스 생성자에서 초기화 해주지 않아도 된다.
	};
}
