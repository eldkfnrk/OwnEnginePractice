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

            if (mActiveAnimation->IsComplete() == true && mbLoop == true) {
                mActiveAnimation->Reset();
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
        animation->CreateAnimation(name, spriteSheet, leftTop, size, offset, spriteLength, duration);

        animation->SetAnimator(this);  

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

        mActiveAnimation = animation;
        mActiveAnimation->Reset();  //애니메이션 1을 재생하던 중 애니메이션 2를 재생하려 할 때 재생 중이던 애니메이션이 동작하면서 바뀐 값을 초기화해주어야 하기 때문에 리셋 
        mbLoop = loop;  
    }

    Animator::~Animator()
    {
    }
}