#pragma once
#include "oepComponent.h"

namespace oep {
	//SpriteRenderer 클래스 - 오브젝트 렌더(화면 상에 그림을 그려주는 역할)를 담당하는 컴포넌트
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		~SpriteRenderer();

	private:

	};
}
