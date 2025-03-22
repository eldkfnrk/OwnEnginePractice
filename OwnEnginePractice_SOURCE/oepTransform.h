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
		Vector2 mPosition;  //����ü ������ �ȿ��� �ʱ�ȭ ���ְ� �ֱ� ������ ���� ���� �� Ŭ���� �����ڿ��� �ʱ�ȭ ������ �ʾƵ� �ȴ�.
	};
}
