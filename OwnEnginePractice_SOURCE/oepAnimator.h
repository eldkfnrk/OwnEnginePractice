#pragma once
#include "oepComponent.h"
#include "oepAnimation.h"

namespace oep {
	//Animator 클래스 - 애니메이션들을 유기적으로 묶어주는 클래스
	//게임의 경우 플레이어 캐릭터가 가만히 서 있을 때도 그에 맞는 애니메이션이 있고 키 입력에 따라 이동과 점프, 공격 등의 동작들이 있게 되는데 이 모든 동작들에 맞는 애니메이션을
	//만들어 캐릭터가 가지고 있게 한다. 이때 가만히 있다가 이동 키 입력 시 이동 애니메이션을 출력하고 키를 떼면 가만히 있고 이동 중에 공격 키 입력 시 공격 애니메이션을 출력하는 등의
	//애니메이션이 왔다갔다 하면서 출력되게 해주는 역할을 하는 것이 바로 Animator이다.
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

		Animation* mActiveAnimation;  //현재 실행 중인 애니메이션

		bool mbLoop;  //애니메이션이 계속 반복 재생할지 여부
	};
}