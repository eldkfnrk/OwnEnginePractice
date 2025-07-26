#pragma once
#include "..\OwnEnginePractice_SOURCE\oepScript.h"

namespace oep {
	class PlayerScript : public Script
	{
	public:
		enum class eState {
			//SitDown,
			Idle,  //�ƹ��͵� ���� �ʴ� ���¸� ���� Idle�̶�� �Ѵ�.
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

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		//�̺�Ʈ
		void AttackEffect();

		~PlayerScript();

	private:
		//�� ���¿� �´� ������ ������ �Լ�
		void idle();
		void move();
		void giveWater();

	private:
		eState mState;  
		class Animator* mAnimator;  
	};
}
