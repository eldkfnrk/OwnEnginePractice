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
		//게임 오브젝트의 좌표
		float mX;
		float mY;
	};
}
