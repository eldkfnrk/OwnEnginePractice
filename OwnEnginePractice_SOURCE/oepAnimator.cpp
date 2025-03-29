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

    //�ڵ��� �������� ���̱� ���� �Ű� ������ ���� ��� ������ ���� �͵� �ϳ��� ����� �� �� �ִ�.
    void Animator::CreateAnimation(const std::wstring& name
        , graphics::Texture* spriteSheet
        , Vector2 leftTop
        , Vector2 size
        , Vector2 offset
        , UINT spriteLength
        , float duration)
    {
        //�̹� �ִ� �ִϸ��̼��� �߰��Ϸ��� ���� ���� �ֱ� ������ �̹� ������� �ִ� �������� �˻��ϱ� ���� �ִϸ��̼��� ã�Ƽ� ����
        Animation* animation = nullptr;  //�ƹ��͵� ���� ���·� �ʱ�ȭ�Ͽ��� �������� ���� ����.
        animation = FindAnimation(name);  
        if (animation != nullptr) {  //�̹� �ִϸ��̼��� �ִ� ���
            return;
        }

        //������� �ִϸ��̼��� ���� ���
        animation = new Animation();
        animation->CreateAnimation(name, spriteSheet, leftTop, size, offset, spriteLength, duration);

        animation->SetAnimator(this);  //�ִϸ��̼��� ��������� ���ÿ� �ִϸ��̼��� ���� �ִϸ����͸� �ִϸ��̼ǿ� ����

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
        //����ϱ� ���ؼ� �ش� �ִϸ��̼��� ã�ƾ� �Ѵ�.
        //�̷��� Ʈ���� �迭���� ���� ã�Ƽ� ����ϴ� ��� �ݵ�� ����� �����Ͱ� ���޵Ǿ������� �����ϴ� ������ �ʿ��ϴ�.
        Animation* animation = FindAnimation(name);

        if (animation == nullptr) {  //�ִϸ��̼��� ���� ���
            return;
        }

        mActiveAnimation = animation;
        mActiveAnimation->Reset();  //���� �ִϸ��̼��� �־��� �� �߰��� �ٲ� ��찡 ���� �� �ֱ� ������ �ִϸ��̼� ��� �� �� �� ������ ���־�� �Ѵ�.
        mbLoop = loop;  //�� �ִϸ��̼��� ������ �� �������� ���ڷ� �޾Ұ� �װ� �ִϸ��̼ǿ� ����(���� ������ ������ ���� ����Ʈ ���� true�̴�.)
    }

    Animator::~Animator()
    {
    }
}