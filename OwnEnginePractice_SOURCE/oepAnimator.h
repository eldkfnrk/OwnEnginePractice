#pragma once
#include "oepComponent.h"
#include "oepAnimation.h"

namespace oep {
	class Animator : public Component
	{
	public:
		//이러한 이벤트 시스템을 spine event이라 하는 시스템에서 디폴트로 사용되고 있다.
		//이걸 사용하는 이유는 픽셀로 일일히 그려서 애니메이션을 제작하는 것이 번거롭고 귀찮은 작업인데 이를 더 쉽게 해줄 수 있기 때문이다.
		//그리고 이벤트 시스템은 해당 시스템의 기본적으로 들어가 있기 때문에 추가
		
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
			//모든 애니메이션은 이 이벤트를 가지고 있는 것이다.
			//애니메이션 시작 시 스타트 이벤트를 애니메이션이 끝나면 컴플리트 이벤트를 다른 애니메이션으로 바뀌면 기존 애니메이션에 엔드 이벤트가 동작하는 원리
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

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = true);

		bool IsComplete() {
			return mActiveAnimation->IsComplete();
		}

		//이벤트를 찾는 함수
		Events* FindEvents(const std::wstring& name);

		//각 애니메이션의 이벤트들을 가지고 오는 함수(자료형이 STL의 함수 포인터를 사용하기 위한 객체형이기 때문에 그대로 사용하여야 한다.)
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