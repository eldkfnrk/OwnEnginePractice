#pragma once
#include "..\OwnEnginePractice_SOURCE\oepScript.h"
#include "..\OwnEnginePractice_SOURCE\oepTransform.h"

namespace oep {
	class CatScript : public Script
	{
	public:
		//FSM 패턴 사용을 위한 오브젝트 상태 정의
		enum class eState {
			SitDown,
			Move,  
			LayDown,
			WakeUp,
			Grooming,
		};

		enum class eDirection {
			Left,
			Right,
			Up,
			Down,
			End,
		};

		CatScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		~CatScript();

	private:
		//각 상태에 맞는 동작을 정의할 함수
		void sitDown();
		void move();
		//void layDown();
		void playWalkAnimationByDirection(eDirection direction);  //방향에 따른 애니메이션 출력
		void translate(Transform* transform);  //이동 관련 동작을 모아놓은 함수

	private:
		eState mState;  
		class Animator* mAnimator; 
		//복잡한 동작을 하는 npc는 보통 behavior 트리를 사용한다.
		float mTime;  //그러나 간단한 동작을 반복하는 npc는 FSM에 시간을 이용하여 표현한다.
		eDirection mDirection;
	};
}