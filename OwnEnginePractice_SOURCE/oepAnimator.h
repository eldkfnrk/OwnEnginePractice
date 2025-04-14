#pragma once
#include "oepComponent.h"
#include "oepAnimation.h"

namespace oep {
	class Animator : public Component
	{
	public:
		struct Event  
		{
			void operator=(std::function<void()> func) {
				mEvent = std::move(func);
			}

			void operator()() {
				if (mEvent) {  
					mEvent();  //함수 호출(()가 없으면 객체 호출)
				}
			}

			std::function<void()> mEvent;  
		};

		struct Events
		{
			Event startEvent;  //시작 이벤트
			Event completeEvent;  //완료 이벤트
			Event endEvent;  //종료 이벤트
		};

		Animator();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet
			, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration);

		//애니메이션을 만들 때는 지금까지 모두 그려져 있는 스프라이트 시트를 가지고 와서 사용을 했는데 이 방법 말고 애니메이션에 관련된 이미지들을 한 폴더에 모아서
		//사용하는 애니메이션 폴더 구조를 추가해서 사용할 수 있도록 할 것이다.
		//인자로 애니메이션 이름, 불러올 애니메이션 폴더 경로, 오프셋, 다음 장으로 넘길 주기를 받을 것이다.
		void CreateAnimationByFolder(const std::wstring& name, const std::wstring& path, Vector2 offset, float duration);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = true);

		bool IsComplete() {
			return mActiveAnimation->IsComplete();
		}

		Events* FindEvents(const std::wstring& name);

		std::function<void()>& GetStartEvent(const std::wstring& name);  //&를 사용하는 것은 복사가 아닌 참조 즉, 원본을 가지고 오기 위해서 참조형을 사용하는 것이다.
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);

		~Animator();

	private:
		std::map<std::wstring, Animation*> mAnimations;

		Animation* mActiveAnimation;  //현재 실행 중인 애니메이션

		bool mbLoop;  //애니메이션이 계속 반복 재생할지 여부

		std::map<std::wstring, Events*> mEvents;
	};
}