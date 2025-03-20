#pragma once
#include "oepComponent.h"

namespace oep {
	struct Pos {  //Transform ������Ʈ�� ������ ��ġ ��ǥ(2D �����̶� 2���� 3D �����̸� z�� ������ 3���� ������ �ȴ�.)
		float mX;
		float mY;
	};


	//Transform Ŭ���� - ������Ʈ�� ��ġ ������ ����ϴ� ������Ʈ
	class Transform : public Component
	{
	public:
		Transform();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void SetPos(float x, float y) {
			mX = x;
			mY = y;
		}

		float GetX() {
			return mX;
		}

		float GetY() {
			return mY;
		}

		~Transform();

	private:
		float mX;
		float mY;
	};
}
