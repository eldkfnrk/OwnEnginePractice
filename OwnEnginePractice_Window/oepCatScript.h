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
		void playWalkAnimationByDirection(eDirection direction);  //���⿡ ���� �ִϸ��̼� ���
		void translate(Transform* transform);  //�̵� ���� ������ ��Ƴ��� �Լ�

	private:
		eState mState;  
		class Animator* mAnimator; 
		//������ ������ �ϴ� npc�� ���� behavior Ʈ���� ����Ѵ�.
		float mTime;  //�׷��� ������ ������ �ݺ��ϴ� npc�� FSM�� �ð��� �̿��Ͽ� ǥ���Ѵ�.
		eDirection mDirection;
	};
}