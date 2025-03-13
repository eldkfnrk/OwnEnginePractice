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

		~GameObject();

	private:
		//���� ������Ʈ�� ��ǥ
		float mX;
		float mY;
	};
}
