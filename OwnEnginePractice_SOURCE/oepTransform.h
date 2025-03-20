#pragma once
#include "oepComponent.h"

namespace oep {
	struct Pos {  //Transform 컴포넌트가 가지는 위치 좌표(2D 게임이라 2개고 3D 게임이면 z축 값까지 3개를 가지면 된다.)
		float mX;
		float mY;
	};


	//Transform 클래스 - 오브젝트의 위치 정보를 담당하는 컴포넌트
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
