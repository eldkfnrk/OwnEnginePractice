#pragma once
#include "oepCollider.h"

namespace oep {
	class BoxCollider2D : public Collider
	{
	public:
		BoxCollider2D();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetSize(Vector2 size) {
			mSize.x = size.x;
			mSize.y = size.y;
		}
		
		Vector2 GetSize() {
			return mSize;
		}

		~BoxCollider2D();

	private:
		Vector2 mSize;  //네모형 충돌체의 크기
	};
}
