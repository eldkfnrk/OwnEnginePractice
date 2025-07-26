#pragma once
#include "oepCollider.h"

namespace oep {
	class CircleCollider2D : public Collider
	{
	public:
		CircleCollider2D();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		~CircleCollider2D();

	private:
		float mRadius;  //원형 충돌체의 반지름(충돌체 오브젝트의 좌표를 중심으로 반지름 크기의 원이 생성되어서 물리 충돌 처리를 할 예정)
	};
}
