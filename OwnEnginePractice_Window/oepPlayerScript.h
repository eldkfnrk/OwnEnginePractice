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

		//이벤트
		void AttackEffect();

		~PlayerScript();

	private:
		//각 상태에 맞는 동작을 정의할 함수
		void idle();
		void move();
		void giveWater();

	private:
		eState mState;  
		class Animator* mAnimator;  
	};
}
