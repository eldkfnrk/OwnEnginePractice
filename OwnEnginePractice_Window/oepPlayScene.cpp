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

namespace oep {
    PlayScene::PlayScene() : mPlayer(nullptr)
    {
    }

    void PlayScene::Initialize()
    {
        GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(336.0f, 423.0f));
        Camera* cameraComp = camera->AddComponent<Camera>();
        renderer::mainCamera = cameraComp;  //���� ī�޶�

        mPlayer = object::Instantiate<Player>(enums::eLayerType::Particle);

        //����� �ִϸ��̼��� �����ϴ��� ������ ����Ǵ��� ���� Ȯ���ϱ� ���� �׽�Ʈ �ڵ�
        //graphics::Texture* pacmanTex = Resources::Find<graphics::Texture>(L"MapleEffect");
        //PlayerScript* playerSc = mPlayer->AddComponent<PlayerScript>();
        //Animator* animator = mPlayer->AddComponent<Animator>();
        //
        //animator->CreateAnimation(L"CatFrontMove", pacmanTex, Vector2::Zero, Vector2(386.0f, 246.0f), Vector2::Zero, 8, 0.1f);
        //animator->PlayAnimation(L"CatFrontMove", true);

        //Transform* tr = mPlayer->GetComponent<Transform>();
        //tr->SetPosition(Vector2(100.0f, 100.0f));
        //tr->SetRotation(30.0f);
        //tr->SetScale(Vector2(1.0f, 1.0f));

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

        GameObject* map = object::Instantiate<GameObject>(enums::eLayerType::Player);

        SpriteRenderer* mapSr = map->AddComponent<SpriteRenderer>();
        //mapSr->SetSize(Vector2(3.0f, 3.0f));  
        graphics::Texture* mapTex = Resources::Find<graphics::Texture>(L"BUBBLE");
        mapSr->SetTexture(mapTex);
        
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