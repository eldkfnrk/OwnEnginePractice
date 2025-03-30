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
		class Animator* mAnimator;  //애니메이션이 저장되어 있는 애니메이터

		graphics::Texture* mTexture;  //애니메이션을 제작할 스프라이트가 저장된 텍스쳐

		std::vector<Sprite> mAnimationSheet;  //애니메이션에 사용할 스프라이트들을 모아놓은 배열
		int mIndex;  //배열의 인덱스
		float mTime;  //애니메이션이 동작한 시간
		bool mbComplete;  //애니메이션이 끝났는지 체크
	};
}
