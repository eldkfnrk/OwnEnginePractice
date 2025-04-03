#include "oepAnimator.h"

namespace oep {
    Animator::Animator()
        : Component(enums::eComponentType::Animator), mAnimations{}, mActiveAnimation(nullptr), mbLoop(false)
    {
    }

    void Animator::Initialize()
    {

    }

    void Animator::Update()
    {
        if (mActiveAnimation) {
            mActiveAnimation->Update();

            Events* events = FindEvents(mActiveAnimation->GetName());

            if (mActiveAnimation->IsComplete() == true/* && mbLoop == true*/) {
                if (events) {  //이벤트가 있을 때만 이벤트 호출(이벤트가 없으면 호출이 불가하니 검사를 해주어야 한다.)
                    //애니메이션이 컴플리트되었으니 컴플리트 이벤트가 실행이 되어야 한다.
                    //컴플리트 이벤트는 애니메이션이 컴플리트
                    events->completeEvent();  //원래는 객체를 호출해야 하지만 이렇게 함수처럼 쓸 수 있도록 연산자 오버로딩을 진행해서 이 구문이 가능해졌다.
                }

                if (mbLoop == true) {
                    //원래는 하나의 if문만 있어도 되었지만 지금은 루프와 상관없이 컴플리트 이벤트가 실행되어야 하니 따로 루프 여부를 확인
                    mActiveAnimation->Reset();
                }
            }
        }
    }

    void Animator::LateUpdate()
    {
    }

    void Animator::Render(HDC hdc)
    {
        if (mActiveAnimation) {
            mActiveAnimation->Render(hdc);
        }
    }

    void Animator::CreateAnimation(const std::wstring& name
        , graphics::Texture* spriteSheet
        , Vector2 leftTop
        , Vector2 size
        , Vector2 offset
        , UINT spriteLength
        , float duration)
    {
        Animation* animation = nullptr;  
        animation = FindAnimation(name);  
        if (animation != nullptr) {  //이미 애니메이션이 있는 경우
            return;
        }

        //만들려는 애니메이션이 없는 경우
        animation = new Animation();
        animation->SetName(name);
        animation->CreateAnimation(name, spriteSheet, leftTop, size, offset, spriteLength, duration);

        animation->SetAnimator(this);  

        //애니메이션을 만듦과 동시에 애니메이션의 이벤트들을 생성
        Events* events = new Events();
        mEvents.insert(std::make_pair(name, events));

        mAnimations.insert(std::make_pair(name, animation));
    }

    Animation* Animator::FindAnimation(const std::wstring& name)
    {
        auto iter = mAnimations.find(name);

        if (iter == mAnimations.end()) {
            return nullptr;
        }

        return iter->second;
    }

    void Animator::PlayAnimation(const std::wstring& name, bool loop)
    {
        Animation* animation = FindAnimation(name);

        if (animation == nullptr) {  //애니메이션이 없는 경우
            return;
        }

        //순서가 굉장히 중요하다. 아래의 순서대로 진행되어야 한다.
        //기존 애니메이션의 엔드 이벤트 -> 새 애니메이션의 스타트 이벤트 -> 새 애니메이션 활성화

        //애니메이션이 새로 플레이될 때에도 기존 애니메이션의 이벤트가 발생
        if (mActiveAnimation) {
            Events* currentEvents = FindEvents(mActiveAnimation->GetName());
            if (currentEvents) {
                //기존 애니메이션은 끝내고 다음 애니메이션을 호출하는 것이기 때문에 기존 애니메이션의 엔드 이벤트가 먼저 발생
                currentEvents->endEvent();
            }
        }

        //새로 시작할 애니메이션의 이벤트를 가지고 와야 한다.
        Events* nextEvents = FindEvents(animation->GetName());
        if (nextEvents) {
            //지금 활성화된 애니메이션은 이제 시작을 하는 것이니 스타트 이벤트 호출
            //애니메이션이 재생되기 전에 이벤트가 일어나야 하니 순서가 중요하다.(스타트 이벤트 -> 애니메이션 시작)
            nextEvents->startEvent();
        }

        mActiveAnimation = animation;
        mActiveAnimation->Reset();  //애니메이션 1을 재생하던 중 애니메이션 2를 재생하려 할 때 재생 중이던 애니메이션이 동작하면서 바뀐 값을 초기화해주어야 하기 때문에 리셋 
        mbLoop = loop;  
    }

    Animator::Events* Animator::FindEvents(const std::wstring& name)
    {
        //애니메이션을 찾는 동작과 크게 다른 것은 없다. 찾는 주체가 애니메이션에서 이벤트로 변한 것 뿐이다
        auto iter = mEvents.find(name);

        if (iter == mEvents.end()) {
            return nullptr;
        }

        return iter->second;
    }

    std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
    {
        // TODO: 여기에 return 문을 삽입합니다.
        Events* events = FindEvents(name);
        return events->startEvent.mEvent;  //이벤트의 실제 동작을 가지고 있는 함수 포인터 객체를 가져와야 한다.
    }

    std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
    {
        // TODO: 여기에 return 문을 삽입합니다.
        Events* events = FindEvents(name);
        return events->completeEvent.mEvent;
    }

    std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
    {
        // TODO: 여기에 return 문을 삽입합니다.
        Events* events = FindEvents(name);
        return events->endEvent.mEvent;
    }

    Animator::~Animator()
    {
        for (auto& iter : mAnimations) {
            delete iter.second;
            iter.second = nullptr;  
        }

        for (auto& iter : mEvents) {
            delete iter.second;
            iter.second = nullptr;  //delete를 하면 메모리는 삭제되는데 원래 가지고 있던 메모리 주소 값은 가지고 있는데 혹시 모를 위험을 대비해서 삭제시켜주어야 한다.
        }
    }
}