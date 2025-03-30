#pragma once
#include "oepComponent.h"
#include "oepAnimation.h"

namespace oep {
	//Animator Ŭ���� - �ִϸ��̼ǵ��� ���������� �����ִ� Ŭ����
	//������ ��� �÷��̾� ĳ���Ͱ� ������ �� ���� ���� �׿� �´� �ִϸ��̼��� �ְ� Ű �Է¿� ���� �̵��� ����, ���� ���� ���۵��� �ְ� �Ǵµ� �� ��� ���۵鿡 �´� �ִϸ��̼���
	//����� ĳ���Ͱ� ������ �ְ� �Ѵ�. �̶� ������ �ִٰ� �̵� Ű �Է� �� �̵� �ִϸ��̼��� ����ϰ� Ű�� ���� ������ �ְ� �̵� �߿� ���� Ű �Է� �� ���� �ִϸ��̼��� ����ϴ� ����
	//�ִϸ��̼��� �Դٰ��� �ϸ鼭 ��µǰ� ���ִ� ������ �ϴ� ���� �ٷ� Animator�̴�.
	class Animator : public Component
	{
	public:
		Animator();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet
			, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration);

		Animation* FindAnimation(const std::wstring& name);

		void PlayAnimation(const std::wstring& name, bool loop = true);

		~Animator();

	private:
		std::map<std::wstring, Animation*> mAnimations;

		Animation* mActiveAnimation;  //���� ���� ���� �ִϸ��̼�

		bool mbLoop;  //�ִϸ��̼��� ��� �ݺ� ������� ����
	};
}