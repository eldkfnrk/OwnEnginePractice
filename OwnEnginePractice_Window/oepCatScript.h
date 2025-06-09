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

		void SetPlayer(class GameObject* player) {
			mPlayer = player;
		}

		void SetDest(Vector2 dest) {
			mDest = dest;
		}

		~CatScript();

	private:
		//각 상태에 맞는 동작을 정의할 함수
		void sitDown();
		void move();
		//void layDown();
		void playWalkAnimationByDirection(eDirection direction);  
		void translate(Transform* transform);  

	private:
		eState mState;  
		class Animator* mAnimator; 
		float mTime;
		eDirection mDirection;
		float mDeathTime;  //오브젝트를 삭제시킬 시간을 측정하기 위한 변수

		class GameObject* mPlayer;  //자신을 발사시킨 오브젝트의 정보를 알기 위해 받아놓는 변수

		Vector2 mDest;  //마우스 클릭 시 마우스가 클릭한 좌표 정보
		float mRadian;  //각도(라디안)
	};
}