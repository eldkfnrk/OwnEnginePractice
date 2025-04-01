#pragma once
#include "oepComponent.h"
#include "oepAnimation.h"

namespace oep {
	class Animator : public Component
	{
	public:
		struct Event  //이벤트 관련된 것들을 모아놓을 구조체
		{
			//값을 대입할 때도 그냥 =연산자를 쓰는 것이 아니라 std::move()를 이용하여 넣어주어야 한다. 그러나 매번 이를 해주기는 귀찮으니 이 동작을 연산자 오버로딩하여
			//대입 연산자를 사용해 보기에도 편하고 쉽게 사용할 수 있도록 =연산자 오버로딩을 해준다.
			void operator=(std::function<void()> func) {
				mEvent = std::move(func);
			}

			//보통 아래와 같이 정의한 객체는 그냥 이름만 가지고 사용한다. 그러나 이 객체를 함수처럼 사용하면 좀 더 편하게 사용할 수 있을 것이다.
			//그래서 정의한 함수 포인터를 사용할 때 함수처럼 사용할 수 있도록 ()연산자를 오버로딩 해준다. 
			//익숙하지 않거나 오래되서 까먹은 경우 변수로 착각할 수 있으니 함수인 것을 명확히 보여주기 위해 사용하는 것도 있다.
			void operator()() {
				//함수 포인터와 연결된 함수가 있을 때만 동작해야 한다.
				if (mEvent) {  
					mEvent;  //함수처럼 동작시킬 뿐 실제로는 이와 같이 동작하는 것이다.
				}
			}

			//STL에서 함수 포인터를 사용하는 방법(함수 포인터를 STL로 객체화 시켜놓은 것)
			//<>안에 함수 포인터의 자료형과 인자 타입을 넣어주는 것이다.(보통 게임에선 데이터 전달보다는 각 동작 실행이 많아서 주로 void형을 사용할 것으로 예상)
			std::function<void()> mEvent;  //void (*StartEvent)(); 이 함수 포인터와 동일한데 STL을 이용하는 것이 좀 더 가독성이 좋다.(취향대로 사용하면 된다.)
		};

		struct Events
		{
			Event mStartEvent;  //시작 이벤트
			Event mCompleteEvent;  //완료 이벤트
			Event mEndEvent;  //종료 이벤트
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

		~Animator();

	private:
		std::map<std::wstring, Animation*> mAnimations;

		Animation* mActiveAnimation;  //현재 실행 중인 애니메이션

		bool mbLoop;  //애니메이션이 계속 반복 재생할지 여부

		//이벤트
		//각 애니메이션마다 이벤트들을 가지고 있어야 하기 때문에 동일한 키 값을 가지는 트리로 애니메이션마다의 이벤트 저장
		std::map<std::wstring, Events> mEvents;
	};
}