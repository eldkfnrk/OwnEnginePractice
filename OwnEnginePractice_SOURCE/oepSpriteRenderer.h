#pragma once
#include "oepComponent.h"

namespace oep {
	//SpriteRenderer Ŭ���� - ������Ʈ ����(ȭ�� �� �׸��� �׷��ִ� ����)�� ����ϴ� ������Ʈ
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
