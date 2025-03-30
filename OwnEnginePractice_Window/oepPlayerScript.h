#pragma once
#include "..\OwnEnginePractice_SOURCE\oepScript.h"

namespace oep {
	class PlayerScript : public Script
	{
	public:
		//FSM 패턴 사용을 위한 오브젝트 상태 정의
		enum class eState {
			SitDown,
			//LeftWalk,
			//RightWalk,
			//DownWalk,
			//UpWalk,
			Walk,  //굳이 방향을 나누지 않고 하나로 묶어서 사용
			Sleep,
			WakeUp,
			Grooming,
		};

		PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		~PlayerScript();

	private:
		//각 상태에 맞는 동작을 정의할 함수
		void sitDown();
		void move();

	private:
		eState mState;  //FSM 패턴은 자신의 상태를 알고 있어야 하고 상태는 하나만 가질 수 있다.
		class Animator* mAnimator;  //애니메이션을 동작시켜야 하기 때문에 가지고 있어야 한다.
	};
}
