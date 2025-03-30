#pragma once
#include "oepResource.h"
#include "oepTexture.h"

namespace oep {
	class Animation : public Resource
	{
	public:
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

		HRESULT Load(const std::wstring& path) override;

		void Update();
		void Render(HDC hdc);

		void CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet
			, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration);

		void Reset();  

		bool IsComplete() {  
			return mbComplete;
		}

		void SetAnimator(class Animator* animator) {
			mAnimator = animator;
		}

		~Animation();

	private:
		class Animator* mAnimator;  //�ִϸ��̼��� ����Ǿ� �ִ� �ִϸ�����

		graphics::Texture* mTexture;  //�ִϸ��̼��� ������ ��������Ʈ�� ����� �ؽ���

		std::vector<Sprite> mAnimationSheet;  //�ִϸ��̼ǿ� ����� ��������Ʈ���� ��Ƴ��� �迭
		int mIndex;  //�迭�� �ε���
		float mTime;  //�ִϸ��̼��� ������ �ð�
		bool mbComplete;  //�ִϸ��̼��� �������� üũ
	};
}
