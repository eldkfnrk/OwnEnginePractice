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
        if (animation != nullptr) {  //�̹� �ִϸ��̼��� �ִ� ���
            return;
        }

        //������� �ִϸ��̼��� ���� ���
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

        if (animation == nullptr) {  //�ִϸ��̼��� ���� ���
            return;
        }

        mActiveAnimation = animation;
        mActiveAnimation->Reset();  //�ִϸ��̼� 1�� ����ϴ� �� �ִϸ��̼� 2�� ����Ϸ� �� �� ��� ���̴� �ִϸ��̼��� �����ϸ鼭 �ٲ� ���� �ʱ�ȭ���־�� �ϱ� ������ ���� 
        mbLoop = loop;  
    }

    Animator::~Animator()
    {
    }
}