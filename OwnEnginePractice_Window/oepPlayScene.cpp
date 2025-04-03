#include "oepPlayScene.h" 
#include "..\OwnEnginePractice_SOURCE\oepTransform.h"
#include "..\OwnEnginePractice_SOURCE\oepSpriteRenderer.h"
#include "..\OwnEnginePractice_SOURCE\oepInput.h"
#include "..\OwnEnginePractice_SOURCE\oepSceneManager.h"
#include "..\OwnEnginePractice_SOURCE\oepObject.h"
#include "..\OwnEnginePractice_SOURCE\oepTexture.h" 
#include "..\OwnEnginePractice_SOURCE\oepResources.h"  
#include "..\OwnEnginePractice_SOURCE\oepRenderer.h"
#include "..\OwnEnginePractice_SOURCE\oepAnimator.h"
#include "..\OwnEnginePractice_SOURCE\oepAnimation.h"
#include "oepPlayer.h"
#include "oepPlayerScript.h"
#include "oepCat.h"
#include "oepCatScript.h"

namespace oep {
    PlayScene::PlayScene() : mPlayer(nullptr)
    {
    }

    void PlayScene::Initialize()
    {
        GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(336.0f, 423.0f));
        Camera* cameraComp = camera->AddComponent<Camera>();
        renderer::mainCamera = cameraComp;  //메인 카메라

        mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);

        graphics::Texture* playerTex = Resources::Find<graphics::Texture>(L"Player");
        Animator* playerAnimator = mPlayer->AddComponent<Animator>();
        PlayerScript* playerScript = mPlayer->AddComponent<PlayerScript>();

        playerAnimator->CreateAnimation(L"Idle", playerTex, Vector2(2000.0f, 250.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 1, 0.1f);
        playerAnimator->CreateAnimation(L"RightWalk", playerTex, Vector2::Zero, Vector2(250.0f, 250.0f), Vector2::Zero, 6, 0.1f);
        playerAnimator->CreateAnimation(L"LeftWalk", playerTex, Vector2(1500.0f, 0.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 6, 0.1f);
        playerAnimator->CreateAnimation(L"FrontGiveWater", playerTex, Vector2(0.0f, 2000.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 12, 0.1f);
        playerAnimator->PlayAnimation(L"Idle");
        
        //함수 포인터를 사용할 때는 함수와 연결을 시켜주어야 한다.
        //보통 이벤트 관련 함수는 해당 이벤트가 일어낧 오브젝트의 스크립트를 통해 구현이 될 것이다. 함수 포인터를 배울 때 예시는 전역 함수를 가지고 와서 사용하는 것이었는데
        //지금은 스크립트의 멤버 함수를 애니메이터의 함수 포인터 STL 객체에 연결시키려는 것이기 때문에 std::bind 함수를 사용하여 함수 포인터와 함수를 연결시켜 주어야 한다.
        //std::bind는 1번쨰 인자로 함수명을 받아서 함수 포인터에 연결할 함수를 결정하고 2번째 인자로 그 함수를 호출할 객체의 주소를 받는다.
        //아래의 구문을 설명하면 playerScript 객체의 AttackEffect 함수를 함수 포인터에 연결하겠다는 의미
        //이벤트 함수의 위치는 이 이벤트가 적용될 오브젝트 객체에 있을 수도 있고 오브젝트의 행동을 결정하는 스크립트 객체에 있을 수도 있다.
        //1번째 인자에 &를 쓰는 이유는 여러 번 설명했지만 &가 없으면 복사본을 넘기는 것이어서 속도가 느리지만 &를 써서 원본을 직접 넘기면 복사를 할 필요가 없으니 속도가 빠르기 때문이다.
        //만약 전역 함수를 std::bind하려 하면 2번째 인자가 필요 없다.(왜냐하면, 모두 접근이 가능하기 때문에 그냥 연결만 하면 되기 때문이다.)
        playerAnimator->GetCompleteEvent(L"FrontGiveWater") = std::bind(&PlayerScript::AttackEffect, playerScript);  //해당 애니메이션의 컴플리트 이벤트 설정
        
        Transform* tr = mPlayer->GetComponent<Transform>();
        tr->SetPosition(Vector2(100.0f, 100.0f));
        tr->SetRotation(0.0f);
        //tr->SetScale(Vector2(2.0f, 2.0f));  //크기는 게임에 알맞게 알아서 조절하면 된다.


        //고양이 npc 추가
        Cat* cat= object::Instantiate<Cat>(enums::eLayerType::Animal);
        graphics::Texture* catTex = Resources::Find<graphics::Texture>(L"Cat");
        CatScript* catSc = cat->AddComponent<CatScript>();
        Animator* catAnimator = cat->AddComponent<Animator>();

        //모든 에니메이션을 가지고 만들어놓고 있어야 한다.
        catAnimator->CreateAnimation(L"DownMove", catTex, Vector2::Zero, Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        catAnimator->CreateAnimation(L"RightMove", catTex, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        catAnimator->CreateAnimation(L"UpMove", catTex, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        catAnimator->CreateAnimation(L"LeftMove", catTex, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        catAnimator->CreateAnimation(L"SitDown", catTex, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        catAnimator->CreateAnimation(L"Grooming", catTex, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        catAnimator->CreateAnimation(L"LayDown", catTex, Vector2(0.0f, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);  //lay down - 눕다
        catAnimator->CreateAnimation(L"WakeUp", catTex, Vector2(0.0f, 226.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        catAnimator->PlayAnimation(L"SitDown", false);

        Transform* tr1 = cat->GetComponent<Transform>();
        tr1->SetPosition(Vector2(200.0f, 200.0f));
        tr1->SetRotation(0.0f);
        tr1->SetScale(Vector2(2.0f, 2.0f));
        
        Scene::Initialize();
    }

    void PlayScene::Update()
    {
        Scene::Update();
    }

    void PlayScene::LateUpdate()
    {
        Scene::LateUpdate();
        if (Input::GetKeyDown(eKeyCode::N)) {
            SceneManager::LoadScene(L"EndScene");
        }
    }

    void PlayScene::Render(HDC hdc)
    {
        Scene::Render(hdc);
    }

    void PlayScene::OnEnter()
    {
        
    }

    void PlayScene::OnExit()
    {
        Transform* tr = mPlayer->GetComponent<Transform>();
        tr->SetPosition(Vector2(0, 0));
    }

    PlayScene::~PlayScene()
    {
    }
}