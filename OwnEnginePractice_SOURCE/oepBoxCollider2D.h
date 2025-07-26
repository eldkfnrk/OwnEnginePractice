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

		~BoxCollider2D();

	private:

	};
}
