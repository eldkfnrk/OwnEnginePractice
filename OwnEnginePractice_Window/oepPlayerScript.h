#pragma once
#include "..\OwnEnginePractice_SOURCE\oepScript.h"

namespace oep {
	class PlayerScript : public Script
	{
	public:
		//FSM ���� ����� ���� ������Ʈ ���� ����
		enum class eState {
			SitDown,
			//LeftWalk,
			//RightWalk,
			//DownWalk,
			//UpWalk,
			Walk,  //���� ������ ������ �ʰ� �ϳ��� ��� ���
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
		//�� ���¿� �´� ������ ������ �Լ�
		void sitDown();
		void move();

	private:
		eState mState;  //FSM ������ �ڽ��� ���¸� �˰� �־�� �ϰ� ���´� �ϳ��� ���� �� �ִ�.
		class Animator* mAnimator;  //�ִϸ��̼��� ���۽��Ѿ� �ϱ� ������ ������ �־�� �Ѵ�.
	};
}
