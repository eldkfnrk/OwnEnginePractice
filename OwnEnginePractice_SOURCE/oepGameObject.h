#pragma once
#include "CommonInclude.h"

namespace oep {
	//GameObject 클래스 - 게임 오브젝트를 만들 기본 틀이 될 클래스
	//유니티에서는 오브젝트 언리얼에서는 액터라고 부른다.
	class GameObject
	{
	public:
		GameObject();

		//기존에 Application 클래스에 있던 GameObject와 관련된 동작들을 굳이 Application에서 동작하게 하지 말고 GameObject 안에서 동작을 구현하고
		//해당 함수를 Application에서는 알맞게 가져와서 사용할 수 있도록 수정하기 위한 함수들
		void Update();
		void LateUpdate();
		void Render(HDC hdc);

		//위와 같이 동작을 클래스 내에서 직접 구현하면 굳이 Get, Set 함수를 구현할 필요가 없어서 좋고 다른 클래스에서 간접 접근하는 과정으로 코드가
		//길어졌던 것을 짧게 단축할 수 있어서 좋다.
		////private멤버에 직접 접근할 수 없으니 간접 접근하도록 Get, Set 함수 구현
		//void SetPosition(float x, float y) {
		//	mX = x;
		//	mY = y;
		//}

		//float GetPositionX() {
		//	return mX;
		//}

		//float GetPositionY() {
		//	return mY;
		//}

		~GameObject();

	private:
		//게임 오브젝트의 좌표
		float mX;
		float mY;
	};
}
