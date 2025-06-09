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

		void SetPlayer(class GameObject* player) {
			mPlayer = player;
		}

		void SetDest(Vector2 dest) {
			mDest = dest;
		}

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

		class GameObject* mPlayer;  //�ڽ��� �߻��Ų ������Ʈ�� ������ �˱� ���� �޾Ƴ��� ����

		Vector2 mDest;  //���콺 Ŭ�� �� ���콺�� Ŭ���� ��ǥ ����
		float mRadian;  //����(����)
	};
}