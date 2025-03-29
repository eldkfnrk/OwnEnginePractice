#pragma once
#include "oepResource.h"
#include "oepTexture.h"

namespace oep {
	//Animation 클래스 - 애니메이션을 생성하는 클래스
	//애니메이션 영화를 보면 그림들이 연속적으로 동작하면서 움직이도록 만들어 화면에 그려지는 그림들이 동작을 하게 만드는데 게임도 플레이할 때 오브젝트들이 가만히 있는 것이 아니라 모두
	//각자의 동작을 하고 있는데 이런 것들을 애니메이션이라고 한다. 예를 들어 마리오의 경우 마리오가 움직일 때 마리오는 가만히 있고 이동하는게 아니라 마리오도 뛰는 동작을 보여주며 이동하고
	//불을 뿜는 꽃도 불을 뿜을 때 가만히 뿜지 않고 입을 벌리는 움직임을 취하고 뿜는 것처럼 오브젝트의 움직임을 보여주는 모든 것이 애니메이션이라고 할 수 있다.
	class Animation : public Resource
	{
	public:
		//애니메이션으로 그려질 그림 전체를 스프라이트 시트, 스프라이트 시트에 그려져 있는 각각의 그림들을 스프라이트라고 부르기로 하자.(실제 유니티도 이렇게 명칭을 붙이고 있다.)
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

		//애니메이션에서는 당장은 재정의하지 않을 것이지만 만약 애니메이션 툴을 만들어 애니메이션을 만들어 저장하고 이를 로드할 경우 사용할 수 있도록 여지를 남겨놓기 위해 리소스를 상속받아 가지고 있는다.
		HRESULT Load(const std::wstring& path) override;

		void Update();
		void Render(HDC hdc);

		void CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet
			, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration);

		void Reset();  //애니메이션의 동작이 끝나면 다시 처음 동작으로 리셋해주는 함수(애니메이션에서 스프라이트를 0,1,2를 쓸 때 2까지 출력이 되었으면 다시 0으로 이동하는 함수)

		bool IsComplete() {  //애니메이션이 끝난는지를 반환하는 함수
			return mbComplete;
		}

		void SetAnimator(class Animator* animator) {  //애니메이션을 만들 때 어떤 애니메이터인지 저장하는 함수
			mAnimator = animator;
		}

		~Animation();

	private:
		//자기 자신에 해당하는 애니메이션을 재생하고 있는 애니메이터를 들고 있는다.
		//애니메이션은 자신을 재생하고 있는 애니메이터를 애니메이터는 재생하고 있는 애니메이션을 서로 알고 있으면 좋기 때문에 이렇게 애니메이터를 가지고 있도록 한다.
		class Animator* mAnimator;

		graphics::Texture* mTexture;  //애니메이션에 사용될 텍스쳐

		std::vector<Sprite> mAnimationSheet;  //애니메이션에 사용될 스프라이트들을 모아놓을 배열
		int mIndex;  //배열의 인덱스
		float mTime;  //한 스프라이트에서 다음 스프라이트로 넘어가는 시간
		bool mbComplete;  //배열에 저장된 모든 스프라이트가 순회가 되었는지 체크
	};
}
