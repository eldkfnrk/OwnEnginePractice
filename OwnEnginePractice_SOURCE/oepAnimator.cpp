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

    //코드의 가독성을 높이기 위해 매개 변수가 많은 경우 내려서 쓰는 것도 하나의 방법이 될 수 있다.
    void Animator::CreateAnimation(const std::wstring& name
        , graphics::Texture* spriteSheet
        , Vector2 leftTop
        , Vector2 size
        , Vector2 offset
        , UINT spriteLength
        , float duration)
    {
        //이미 있는 애니메이션을 추가하려는 것일 수도 있기 때문에 이미 만들어져 있는 것인지를 검사하기 위해 애니메이션을 찾아서 저장
        Animation* animation = nullptr;  //아무것도 없는 상태로 초기화하여야 버려지는 값이 없다.
        animation = FindAnimation(name);  
        if (animation != nullptr) {  //이미 애니메이션이 있는 경우
            return;
        }

        //만들려는 애니메이션이 없는 경우
        animation = new Animation();
        animation->CreateAnimation(name, spriteSheet, leftTop, size, offset, spriteLength, duration);

        animation->SetAnimator(this);  //애니메이션이 만들어짐과 동시에 애니메이션을 만든 애니메이터를 애니메이션에 저장

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
        //재생하기 위해선 해당 애니메이션을 찾아야 한다.
        //이렇게 트리나 배열에서 값을 찾아서 사용하는 경우 반드시 제대로 데이터가 전달되었는지를 점검하는 절차가 필요하다.
        Animation* animation = FindAnimation(name);

        if (animation == nullptr) {  //애니메이션이 없는 경우
            return;
        }

        mActiveAnimation = animation;
        mActiveAnimation->Reset();  //이전 애니메이션이 있었고 그 중간에 바뀐 경우가 있을 수 있기 때문에 애니메이션 재생 시 한 번 리셋을 해주어야 한다.
        mbLoop = loop;  //이 애니메이션이 루프를 돌 것인지를 인자로 받았고 그걸 애니메이션에 적용(인자 전달이 없었을 경우는 디폴트 값인 true이다.)
    }

    Animator::~Animator()
    {
    }
}