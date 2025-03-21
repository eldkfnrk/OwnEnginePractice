#pragma once
#include "oepComponent.h"

namespace oep {
	//struct Pos { 
	//	float mX;
	//	float mY;
	//};

	//이제 위에서 정의한 구조체를 대신해서 math 네임스페이스에 정의한 Vector2 구조체를 사용하여 오브젝트의 좌표를 관리할 예정이다.
	using namespace math;  //해당 네임스페이스를 범위 지정 연산자 없이 사용하기 위한 구문

	class Transform : public Component
	{
	public:
		Transform();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		//void SetPos(float x, float y) {
		//	mX = x;
		//	mY = y;
		//}

		void SetPos(Vector2 pos) {
			mPosition.x = pos.x;
			mPosition.y = pos.y;
		}

		//float GetX() {
		//	return mX;
		//}

		//float GetY() {
		//	return mY;
		//}

		Vector2 GetPosition() {
			return mPosition;
		}

		~Transform();

	private:
		//오브젝트 좌표
		//float mX;
		//float mY;

		//Vector2 구조체를 사용하여 오브젝트 좌표 관리
		Vector2 mPosition;
	};
}
