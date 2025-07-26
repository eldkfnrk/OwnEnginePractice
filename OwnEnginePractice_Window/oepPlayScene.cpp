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
#include "..\OwnEnginePractice_SOURCE\oepBoxCollider2D.h"
#include "..\OwnEnginePractice_SOURCE\oepCollisionManager.h"

namespace oep {
    PlayScene::PlayScene() : mPlayer(nullptr)
    {
    }

    void PlayScene::Initialize()
    {
        //이런 식으로 레이어 간 충돌 여부를 정함으로써 최대한 모든 충돌체의 충돌을 나누어서 사용하고자 한다.
        CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, true);  

        GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(336.0f, 423.0f));
        Camera* cameraComp = camera->AddComponent<Camera>();
        renderer::mainCamera = cameraComp;  //메인 카메라

        mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);

        CircleCollider2D*playerCollider = mPlayer->AddComponent<CircleCollider2D>();
        playerCollider->SetOffset(Vector2(-50.0f, -50.0f));

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
        tr->SetPosition(Vector2::Zero);
        tr->SetRotation(0.0f);

        Cat* cat = object::Instantiate<Cat>(enums::eLayerType::Animal);
        CatScript* catSc = cat->AddComponent<CatScript>();
        graphics::Texture* catTex = Resources::Find<graphics::Texture>(L"Cat");
        BoxCollider2D* catCollider = cat->AddComponent<BoxCollider2D>();
        catCollider->SetOffset(Vector2(-50.0f, -50.0f));
        Animator* catAnimator = cat->AddComponent<Animator>();
        catAnimator->CreateAnimationByFolder(L"MushroomIdle", L"..\\Resources\\Mushroom", Vector2::Zero, 0.1f);
        catAnimator->PlayAnimation(L"MushroomIdle");
        cat->GetComponent<Transform>()->SetPosition(Vector2(200.0f, 200.0f));
        cat->GetComponent<Transform>()->SetScale(Vector2(1.0f, 1.0f));
        
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
        Scene::OnEnter();
    }

    void PlayScene::OnExit()
    {
        Scene::OnExit();
    }

    PlayScene::~PlayScene()
    {
    }
}