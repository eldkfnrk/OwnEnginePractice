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
        
        playerAnimator->GetCompleteEvent(L"FrontGiveWater") = std::bind(&PlayerScript::AttackEffect, playerScript);  //해당 애니메이션의 컴플리트 이벤트 설정
        
        Transform* tr = mPlayer->GetComponent<Transform>();
        tr->SetPosition(Vector2(300.0f, 250.0f));
        tr->SetRotation(0.0f);

        //고양이 npc 추가
        //Cat* cat= object::Instantiate<Cat>(enums::eLayerType::Animal);
        //graphics::Texture* catTex = Resources::Find<graphics::Texture>(L"Cat");
        //CatScript* catSc = cat->AddComponent<CatScript>();
        //Animator* catAnimator = cat->AddComponent<Animator>();

        //모든 에니메이션을 가지고 만들어놓고 있어야 한다.
        //catAnimator->CreateAnimation(L"DownMove", catTex, Vector2::Zero, Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        //catAnimator->CreateAnimation(L"RightMove", catTex, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        //catAnimator->CreateAnimation(L"UpMove", catTex, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        //catAnimator->CreateAnimation(L"LeftMove", catTex, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        //catAnimator->CreateAnimation(L"SitDown", catTex, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        //catAnimator->CreateAnimation(L"Grooming", catTex, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        //catAnimator->CreateAnimation(L"LayDown", catTex, Vector2(0.0f, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);  //lay down - 눕다
        //catAnimator->CreateAnimation(L"WakeUp", catTex, Vector2(0.0f, 226.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        //catAnimator->PlayAnimation(L"SitDown", false);

        //catAnimator->CreateAnimationByFolder(L"MushroomIdle", L"..\\Resources\\Mushroom", Vector2::Zero, 0.1f);
        //catAnimator->PlayAnimation(L"MushroomIdle");

        //cat->GetComponent<Transform>()->SetPosition(Vector2(300.0f, 300.0f));

        //GameObject* sheet = object::Instantiate<GameObject>(enums::eLayerType::Player);
        //SpriteRenderer* sheetSR = sheet->AddComponent<SpriteRenderer>();

        //graphics::Texture* mushroomTex = Resources::Find<graphics::Texture>(L"MushroomIdleImage");
        //sheetSR->SetTexture(mushroomTex);

        //Transform* tr1 = cat->GetComponent<Transform>();
        //tr1->SetPosition(Vector2(200.0f, 200.0f));
        //tr1->SetRotation(0.0f);
        //tr1->SetScale(Vector2(2.0f, 2.0f));
        
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