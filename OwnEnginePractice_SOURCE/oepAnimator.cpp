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
                if (events) {  //�̺�Ʈ�� ���� ���� �̺�Ʈ ȣ��(�̺�Ʈ�� ������ ȣ���� �Ұ��ϴ� �˻縦 ���־�� �Ѵ�.)
                    //�ִϸ��̼��� ���ø�Ʈ�Ǿ����� ���ø�Ʈ �̺�Ʈ�� ������ �Ǿ�� �Ѵ�.
                    //���ø�Ʈ �̺�Ʈ�� �ִϸ��̼��� ���ø�Ʈ
                    events->completeEvent();  //������ ��ü�� ȣ���ؾ� ������ �̷��� �Լ�ó�� �� �� �ֵ��� ������ �����ε��� �����ؼ� �� ������ ����������.
                }

                if (mbLoop == true) {
                    //������ �ϳ��� if���� �־ �Ǿ����� ������ ������ ������� ���ø�Ʈ �̺�Ʈ�� ����Ǿ�� �ϴ� ���� ���� ���θ� Ȯ��
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
        if (animation != nullptr) {  //�̹� �ִϸ��̼��� �ִ� ���
            return;
        }

        //������� �ִϸ��̼��� ���� ���
        animation = new Animation();
        animation->SetName(name);
        animation->CreateAnimation(name, spriteSheet, leftTop, size, offset, spriteLength, duration);

        animation->SetAnimator(this);  

        //�ִϸ��̼��� ����� ���ÿ� �ִϸ��̼��� �̺�Ʈ���� ����
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

        if (animation == nullptr) {  //�ִϸ��̼��� ���� ���
            return;
        }

        //������ ������ �߿��ϴ�. �Ʒ��� ������� ����Ǿ�� �Ѵ�.
        //���� �ִϸ��̼��� ���� �̺�Ʈ -> �� �ִϸ��̼��� ��ŸƮ �̺�Ʈ -> �� �ִϸ��̼� Ȱ��ȭ

        //�ִϸ��̼��� ���� �÷��̵� ������ ���� �ִϸ��̼��� �̺�Ʈ�� �߻�
        if (mActiveAnimation) {
            Events* currentEvents = FindEvents(mActiveAnimation->GetName());
            if (currentEvents) {
                //���� �ִϸ��̼��� ������ ���� �ִϸ��̼��� ȣ���ϴ� ���̱� ������ ���� �ִϸ��̼��� ���� �̺�Ʈ�� ���� �߻�
                currentEvents->endEvent();
            }
        }

        //���� ������ �ִϸ��̼��� �̺�Ʈ�� ������ �;� �Ѵ�.
        Events* nextEvents = FindEvents(animation->GetName());
        if (nextEvents) {
            //���� Ȱ��ȭ�� �ִϸ��̼��� ���� ������ �ϴ� ���̴� ��ŸƮ �̺�Ʈ ȣ��
            //�ִϸ��̼��� ����Ǳ� ���� �̺�Ʈ�� �Ͼ�� �ϴ� ������ �߿��ϴ�.(��ŸƮ �̺�Ʈ -> �ִϸ��̼� ����)
            nextEvents->startEvent();
        }

        mActiveAnimation = animation;
        mActiveAnimation->Reset();  //�ִϸ��̼� 1�� ����ϴ� �� �ִϸ��̼� 2�� ����Ϸ� �� �� ��� ���̴� �ִϸ��̼��� �����ϸ鼭 �ٲ� ���� �ʱ�ȭ���־�� �ϱ� ������ ���� 
        mbLoop = loop;  
    }

    Animator::Events* Animator::FindEvents(const std::wstring& name)
    {
        //�ִϸ��̼��� ã�� ���۰� ũ�� �ٸ� ���� ����. ã�� ��ü�� �ִϸ��̼ǿ��� �̺�Ʈ�� ���� �� ���̴�
        auto iter = mEvents.find(name);

        if (iter == mEvents.end()) {
            return nullptr;
        }

        return iter->second;
    }

    std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
    {
        // TODO: ���⿡ return ���� �����մϴ�.
        Events* events = FindEvents(name);
        return events->startEvent.mEvent;  //�̺�Ʈ�� ���� ������ ������ �ִ� �Լ� ������ ��ü�� �����;� �Ѵ�.
    }

    std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
    {
        // TODO: ���⿡ return ���� �����մϴ�.
        Events* events = FindEvents(name);
        return events->completeEvent.mEvent;
    }

    std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
    {
        // TODO: ���⿡ return ���� �����մϴ�.
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
            iter.second = nullptr;  //delete�� �ϸ� �޸𸮴� �����Ǵµ� ���� ������ �ִ� �޸� �ּ� ���� ������ �ִµ� Ȥ�� �� ������ ����ؼ� ���������־�� �Ѵ�.
        }
    }
}