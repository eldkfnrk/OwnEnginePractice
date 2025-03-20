#pragma once
#include "CommonInclude.h"

namespace oep {
	class GameObject
	{
	public:
		GameObject();

		void Update();
		void LateUpdate();
		void Render(HDC hdc);

		void SetPosition(float x, float y) {
			mX = x;
			mY = y;
		}

		~GameObject();

	private:
		//���� ������Ʈ�� ��ǥ
		float mX;
		float mY;
	};
}
