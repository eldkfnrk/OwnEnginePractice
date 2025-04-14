#include "oepAnimator.h"
#include "oepResources.h"

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

            if (mActiveAnimation->IsComplete() == true) {
                if (events) { 
                    events->completeEvent();  
                }

                if (mbLoop == true) {
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

    void Animator::CreateAnimationByFolder(const std::wstring& name, const std::wstring& path, Vector2 offset, float duration)
    {
        Animation* animation = nullptr;
        animation = FindAnimation(name);
        if (animation != nullptr) {  //�̹� �ִϸ��̼��� �ִ� ���
            return;
        }

        //������ �ҷ����� ���� API �Լ��� �̿��ϸ� ������ ���⼭�� C++17���� �߰��� filesystem�̶�� ���� ����Ͽ� �ҷ��� ���̴�.
        std::filesystem::path fs(path);  //�ִϸ��̼� ������ ��� ����
        std::vector<graphics::Texture*> images = {};  //��ο� �ִ� �̹����� ������ ����
        int fileCount = 0;  //���� �ȿ� �ִ� ������ ������ Ȯ���� ���� ����

        for (auto& p : std::filesystem::recursive_directory_iterator(fs)) {
            //���� ���� �ִ� �̹������� ����Ű�� �ݺ��ڸ� ��ȯ�ϴ� �Լ��� ���� ���� ��� �̹��� ������ ��ȸ�� �� �ִ�.
            //���� �ý��� ���̺귯���� ����ϴ� ������ �̰��ε� API �Լ��� ����ϸ� �Ʒ��� ���� �͵��� �츮�� ���� �����ؾ� �ϴµ� ���� �ý����� �׷� ���ŷο��� ����.
            std::wstring fileName = p.path().filename();  //���ϸ��� ������ �´�.
            std::wstring fullName = p.path();  //������ ���� ���(���� ��� + ���ϸ�)�� ������ �´�.

            //���� �ش� ������ �̸��� ��θ� ������� �̸� ������ ���ҽ��� �ε����ش�.
            //���ҽ��� �̸��� ���� �̸����� ��δ� ���� ���� ������ ��θ� ã�Ƽ� �ε�
            graphics::Texture* texture = Resources::Load<graphics::Texture>(fileName, fullName);

            //�̹����� �����ϴ� ���Ϳ� ����
            images.push_back(texture);

            fileCount++;
        }

        //��Ʈ�� ũ��
        UINT sheetWidth = images[0]->GetWidth() * fileCount;  //��������Ʈ ��Ʈ�� �̹������� ���η� ����� ���·� ������ ���̱� ������ ���� ������ ���Ѵ�.
        UINT sheetHeight = images[0]->GetHeight();

        //�ִϸ��̼ǿ� ���Ǵ� �̹����� ũ��
        UINT imageWidth = images[0]->GetWidth();
        UINT imageHeight = images[0]->GetHeight();

        graphics::Texture* spriteSheet = graphics::Texture::Create(name, sheetWidth, sheetHeight);  //���ڷ� �ѱ� ũ���� �� �̹��� ���� ����

        //�� �̹��� ���ϱ��� ���������� �ش� �̹����� �ִϸ��̼ǿ� ����� �̹������� ������� ��ġ���� �׷��־�� �Ѵ�.
        for (size_t i = 0; i < images.size(); i++) {
            //�̹����� �����ϴ� �Լ�
            //�� �Լ��� �̹����� ���ϴ� ��ġ�� ���ϴ� ũ�⸸ŭ ������ ���ϴ� �κ��� ������ �� �ֱ� ������ ���� ���� �׸��� �ϳ��� �̹��� ���Ͽ� ������ �� �ִ�.
            BitBlt(spriteSheet->GetHdc(), imageWidth * i, 0, imageWidth, imageHeight, images[i]->GetHdc(), 0, 0, SRCCOPY);
        }

        //��������Ʈ ��Ʈ�� ���� ������ �� ��Ʈ�� �̿��ؼ� �ִϸ��̼Ǹ� ����� �������� �ش� ��Ʈ�� �̿��� �ִϸ��̼��� ���鵵�� �Լ��� ȣ��
        //2D �ִϸ��̼��� ��������Ʈ ��Ʈ�� ������ ������ �ϱ� ������ ��������Ʈ ��Ʈ�� ����� �۾��� �ʿ��ߴ�.
        CreateAnimation(name, spriteSheet, Vector2(0.0f, 0.0f), Vector2(imageWidth, imageHeight), offset, fileCount, duration);
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

        if (mActiveAnimation) {
            Events* currentEvents = FindEvents(mActiveAnimation->GetName());
            if (currentEvents) {
                currentEvents->endEvent();
            }
        }

        Events* nextEvents = FindEvents(animation->GetName());
        if (nextEvents) {
            nextEvents->startEvent();
        }

        mActiveAnimation = animation;
        mActiveAnimation->Reset();  
        mbLoop = loop;  
    }

    Animator::Events* Animator::FindEvents(const std::wstring& name)
    {
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