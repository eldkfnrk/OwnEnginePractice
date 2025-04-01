#pragma once
#include "..\OwnEnginePractice_SOURCE\oepScript.h"

namespace oep {
	class PlayerScript : public Script
	{
	public:
		enum class eState {
			//SitDown,
			Idle,  //아무것도 하지 않는 상태를 보통 Idle이라고 한다.
			Walk,  
			Sleep,
			WakeUp,
			GiveWater,
			Attack,
		};

		PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		~PlayerScript();

	private:
		//각 상태에 맞는 동작을 정의할 함수
		void idle();
		void move();
		void giveWater();

	private:
		eState mState;  
		class Animator* mAnimator;  

		//void (*StartEvent)();  //애니메이션이 끝났을 때마다 이벤트를 실행해 줄 수 있는 함수를 함수 포인터로 가지고 있는다.

		//함수 포인터의 단점으로 그대로 사용하면 사용이 많이 불편하고 가독성이 떨어진다는 것이 있다. 그래서 STL에 함수 포인터를 클래스로 잘 묶어서 배열을 묶은 것처럼
		//객체화시켜 놓은 것이 있다.

		//동작이 하나 이뤄졌을 때나 끝났을 때 함수가 실행이 되는 것을 보통 프로그래밍에서 이벤트 시스템이라고 부른다.
		//이런 프로그래밍을 이벤트 기반 프로그래밍이라고 하는데 게임에서는 보통 사용되지는 않는다.(그러나, 있을 수 있기에 강사님이 추가하셨다.)
	};
}
