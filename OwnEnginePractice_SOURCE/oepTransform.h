#pragma once
#include "oepComponent.h"

namespace oep {
	//struct Pos { 
	//	float mX;
	//	float mY;
	//};

	//���� ������ ������ ����ü�� ����ؼ� math ���ӽ����̽��� ������ Vector2 ����ü�� ����Ͽ� ������Ʈ�� ��ǥ�� ������ �����̴�.
	using namespace math;  //�ش� ���ӽ����̽��� ���� ���� ������ ���� ����ϱ� ���� ����

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
		//������Ʈ ��ǥ
		//float mX;
		//float mY;

		//Vector2 ����ü�� ����Ͽ� ������Ʈ ��ǥ ����
		Vector2 mPosition;
	};
}
