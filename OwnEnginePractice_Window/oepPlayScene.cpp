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
        renderer::mainCamera = cameraComp;  //���� ī�޶�

        mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);

        graphics::Texture* pacmanTex = Resources::Find<graphics::Texture>(L"CHICKEN");
        PlayerScript* playerSc = mPlayer->AddComponent<PlayerScript>();
        Animator* animator = mPlayer->AddComponent<Animator>();

        //��� ���ϸ��̼��� ������ �������� �־�� �Ѵ�.
        animator->CreateAnimation(L"FrontWalk", pacmanTex, Vector2::Zero, Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        animator->CreateAnimation(L"RightWalk", pacmanTex, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        animator->CreateAnimation(L"BackWalk", pacmanTex, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        animator->CreateAnimation(L"LeftWalk", pacmanTex, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        animator->CreateAnimation(L"SitDown", pacmanTex, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        animator->CreateAnimation(L"Grooming", pacmanTex, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        animator->CreateAnimation(L"Sleep", pacmanTex, Vector2(0.0f, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        animator->CreateAnimation(L"WakeUp", pacmanTex, Vector2(0.0f, 226.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        animator->PlayAnimation(L"SitDown", false);
        
        Transform* tr = mPlayer->GetComponent<Transform>();
        tr->SetPosition(Vector2(100.0f, 100.0f));
        tr->SetRotation(0.0f);
        tr->SetScale(Vector2(2.0f, 2.0f));

        //GameObject* map = object::Instantiate<GameObject>(enums::eLayerType::Player);

        //SpriteRenderer* mapSr = map->AddComponent<SpriteRenderer>();
        ////mapSr->SetSize(Vector2(3.0f, 3.0f));  
        //graphics::Texture* mapTex = Resources::Find<graphics::Texture>(L"BUBBLE");
        //mapSr->SetTexture(mapTex);

        //����� npc �߰�
        Cat* cat= object::Instantiate<Cat>(enums::eLayerType::Animal);
        graphics::Texture* catTex = Resources::Find<graphics::Texture>(L"CHICKEN");
        CatScript* catSc = cat->AddComponent<CatScript>();
        Animator* catAnimator = cat->AddComponent<Animator>();

        //��� ���ϸ��̼��� ������ �������� �־�� �Ѵ�.
        catAnimator->CreateAnimation(L"DownMove", catTex, Vector2::Zero, Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        catAnimator->CreateAnimation(L"RightMove", catTex, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        catAnimator->CreateAnimation(L"UpMove", catTex, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        catAnimator->CreateAnimation(L"LeftMove", catTex, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        catAnimator->CreateAnimation(L"SitDown", catTex, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        catAnimator->CreateAnimation(L"Grooming", catTex, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
        catAnimator->CreateAnimation(L"LayDown", catTex, Vector2(0.0f, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);  //lay down - ����
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