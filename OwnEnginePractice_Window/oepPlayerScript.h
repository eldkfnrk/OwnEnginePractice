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

		~PlayerScript();

	private:
		//�� ���¿� �´� ������ ������ �Լ�
		void idle();
		void move();
		void giveWater();

	private:
		eState mState;  
		class Animator* mAnimator;  

		//void (*StartEvent)();  //�ִϸ��̼��� ������ ������ �̺�Ʈ�� ������ �� �� �ִ� �Լ��� �Լ� �����ͷ� ������ �ִ´�.

		//�Լ� �������� �������� �״�� ����ϸ� ����� ���� �����ϰ� �������� �������ٴ� ���� �ִ�. �׷��� STL�� �Լ� �����͸� Ŭ������ �� ��� �迭�� ���� ��ó��
		//��üȭ���� ���� ���� �ִ�.

		//������ �ϳ� �̷����� ���� ������ �� �Լ��� ������ �Ǵ� ���� ���� ���α׷��ֿ��� �̺�Ʈ �ý����̶�� �θ���.
		//�̷� ���α׷����� �̺�Ʈ ��� ���α׷����̶�� �ϴµ� ���ӿ����� ���� �������� �ʴ´�.(�׷���, ���� �� �ֱ⿡ ������� �߰��ϼ̴�.)
	};
}
