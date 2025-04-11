#pragma once
#include "..\OwnEnginePractice_SOURCE\oepScript.h"
#include "..\OwnEnginePractice_SOURCE\oepTransform.h"

namespace oep {
	class CatScript : public Script
	{
	public:
		//FSM ���� ����� ���� ������Ʈ ���� ����
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
		//�� ���¿� �´� ������ ������ �Լ�
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
		float mDeathTime;  //������Ʈ�� ������ų �ð��� �����ϱ� ���� ����
	};
}