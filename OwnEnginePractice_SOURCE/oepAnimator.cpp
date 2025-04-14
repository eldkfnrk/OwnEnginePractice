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

    void Animator::CreateAnimationByFolder(const std::wstring& name, const std::wstring& path, Vector2 offset, float duration)
    {
        Animation* animation = nullptr;
        animation = FindAnimation(name);
        if (animation != nullptr) {  //이미 애니메이션이 있는 경우
            return;
        }

        //파일을 불러오는 것은 API 함수를 이용하면 되지만 여기서는 C++17에서 추가한 filesystem이라는 것을 사용하여 불러올 것이다.
        std::filesystem::path fs(path);  //애니메이션 폴더의 경로 저장
        std::vector<graphics::Texture*> images = {};  //경로에 있는 이미지를 저장할 벡터
        int fileCount = 0;  //폴더 안에 있는 파일의 개수를 확인을 위한 변수

        for (auto& p : std::filesystem::recursive_directory_iterator(fs)) {
            //폴더 내에 있는 이미지들을 가리키는 반복자를 반환하는 함수로 폴더 내에 모든 이미지 파일을 순회할 수 있다.
            //파일 시스템 라이브러리를 사용하는 이유가 이것인데 API 함수를 사용하면 아래와 같은 것들을 우리가 직접 정의해야 하는데 파일 시스템은 그런 번거로움이 없다.
            std::wstring fileName = p.path().filename();  //파일명을 가지고 온다.
            std::wstring fullName = p.path();  //파일의 실제 경로(폴더 경로 + 파일명)를 가지고 온다.

            //이제 해당 파일의 이름과 경로를 얻었으니 이를 가지고 리소스를 로드해준다.
            //리소스의 이름은 파일 이름으로 경로는 구한 실제 파일의 경로를 찾아서 로드
            graphics::Texture* texture = Resources::Load<graphics::Texture>(fileName, fullName);

            //이미지를 저장하는 벡터에 삽입
            images.push_back(texture);

            fileCount++;
        }

        //시트의 크기
        UINT sheetWidth = images[0]->GetWidth() * fileCount;  //스프라이트 시트는 이미지들이 가로로 연결된 상태로 생성될 것이기 때문에 파일 갯수를 곱한다.
        UINT sheetHeight = images[0]->GetHeight();

        //애니메이션에 사용되는 이미지의 크기
        UINT imageWidth = images[0]->GetWidth();
        UINT imageHeight = images[0]->GetHeight();

        graphics::Texture* spriteSheet = graphics::Texture::Create(name, sheetWidth, sheetHeight);  //인자로 넘긴 크기의 빈 이미지 파일 생성

        //빈 이미지 파일까지 생성했으니 해당 이미지에 애니메이션에 사용할 이미지들을 순서대로 배치시켜 그려주어야 한다.
        for (size_t i = 0; i < images.size(); i++) {
            //이미지를 복사하는 함수
            //이 함수는 이미지를 원하는 위치에 원하는 크기만큼 원본에 원하는 부분을 복사할 수 있기 때문에 여러 개의 그림을 하나의 이미지 파일에 복사할 수 있다.
            BitBlt(spriteSheet->GetHdc(), imageWidth * i, 0, imageWidth, imageHeight, images[i]->GetHdc(), 0, 0, SRCCOPY);
        }

        //스프라이트 시트를 만든 이유는 이 시트를 이용해서 애니메이션를 만들기 위함으로 해당 시트를 이용해 애니메이션을 만들도록 함수를 호출
        //2D 애니메이션은 스프라이트 시트를 가지고 만들어야 하기 때문에 스프라이트 시트를 만드는 작업이 필요했다.
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

        if (animation == nullptr) {  //애니메이션이 없는 경우
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