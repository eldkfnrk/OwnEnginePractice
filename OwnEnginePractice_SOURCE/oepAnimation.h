#pragma once
#include "oepResource.h"
#include "oepTexture.h"

namespace oep {
	//Animation Ŭ���� - �ִϸ��̼��� �����ϴ� Ŭ����
	//�ִϸ��̼� ��ȭ�� ���� �׸����� ���������� �����ϸ鼭 �����̵��� ����� ȭ�鿡 �׷����� �׸����� ������ �ϰ� ����µ� ���ӵ� �÷����� �� ������Ʈ���� ������ �ִ� ���� �ƴ϶� ���
	//������ ������ �ϰ� �ִµ� �̷� �͵��� �ִϸ��̼��̶�� �Ѵ�. ���� ��� �������� ��� �������� ������ �� �������� ������ �ְ� �̵��ϴ°� �ƴ϶� �������� �ٴ� ������ �����ָ� �̵��ϰ�
	//���� �մ� �ɵ� ���� ���� �� ������ ���� �ʰ� ���� ������ �������� ���ϰ� �մ� ��ó�� ������Ʈ�� �������� �����ִ� ��� ���� �ִϸ��̼��̶�� �� �� �ִ�.
	class Animation : public Resource
	{
	public:
		//�ִϸ��̼����� �׷��� �׸� ��ü�� ��������Ʈ ��Ʈ, ��������Ʈ ��Ʈ�� �׷��� �ִ� ������ �׸����� ��������Ʈ��� �θ���� ����.(���� ����Ƽ�� �̷��� ��Ī�� ���̰� �ִ�.)
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			float duration;

			Sprite() : leftTop(Vector2::Zero), size(Vector2::Zero), offset(Vector2::Zero), duration(0.0f) {

			}
		};

		Animation();

		//�ִϸ��̼ǿ����� ������ ���������� ���� �������� ���� �ִϸ��̼� ���� ����� �ִϸ��̼��� ����� �����ϰ� �̸� �ε��� ��� ����� �� �ֵ��� ������ ���ܳ��� ���� ���ҽ��� ��ӹ޾� ������ �ִ´�.
		HRESULT Load(const std::wstring& path) override;

		void Update();
		void Render(HDC hdc);

		void CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet
			, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration);

		void Reset();  //�ִϸ��̼��� ������ ������ �ٽ� ó�� �������� �������ִ� �Լ�(�ִϸ��̼ǿ��� ��������Ʈ�� 0,1,2�� �� �� 2���� ����� �Ǿ����� �ٽ� 0���� �̵��ϴ� �Լ�)

		bool IsComplete() {  //�ִϸ��̼��� ���������� ��ȯ�ϴ� �Լ�
			return mbComplete;
		}

		void SetAnimator(class Animator* animator) {  //�ִϸ��̼��� ���� �� � �ִϸ��������� �����ϴ� �Լ�
			mAnimator = animator;
		}

		~Animation();

	private:
		//�ڱ� �ڽſ� �ش��ϴ� �ִϸ��̼��� ����ϰ� �ִ� �ִϸ����͸� ��� �ִ´�.
		//�ִϸ��̼��� �ڽ��� ����ϰ� �ִ� �ִϸ����͸� �ִϸ����ʹ� ����ϰ� �ִ� �ִϸ��̼��� ���� �˰� ������ ���� ������ �̷��� �ִϸ����͸� ������ �ֵ��� �Ѵ�.
		class Animator* mAnimator;

		graphics::Texture* mTexture;  //�ִϸ��̼ǿ� ���� �ؽ���

		std::vector<Sprite> mAnimationSheet;  //�ִϸ��̼ǿ� ���� ��������Ʈ���� ��Ƴ��� �迭
		int mIndex;  //�迭�� �ε���
		float mTime;  //�� ��������Ʈ���� ���� ��������Ʈ�� �Ѿ�� �ð�
		bool mbComplete;  //�迭�� ����� ��� ��������Ʈ�� ��ȸ�� �Ǿ����� üũ
	};
}
