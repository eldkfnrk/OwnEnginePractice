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
        renderer::mainCamera = cameraComp;  //메인 카메라

        mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);

        //애니메이션을 사용하여 움직임을 표현해야 하는 오브젝트들은 지금부터 SpriteRenderer가 아닌 Animator가 화면 출력을 하게 된다.
        //SpriteRenderer는 배경같은 멈춰있는 것을 그릴 때 사용하고 Animator는 플레이어 같은 움직이는 것들을 그릴 때 사용한다.

        //SpriteRenderer* sr = mPlayer->AddComponent<SpriteRenderer>();
        //sr->SetName(L"SR");
        //sr->SetSize(Vector2(3.0f, 3.0f));  //윈도우 크기가 커졌으니 이에 맞춰 크기를 3배로 키워주었다
        graphics::Texture* pacmanTex = Resources::Find<graphics::Texture>(L"CHICKEN");
        //sr->SetTexture(pacmanTex);
        PlayerScript* playerSc = mPlayer->AddComponent<PlayerScript>();
        Animator* animator = mPlayer->AddComponent<Animator>();
        
        animator->CreateAnimation(L"CatFrontMove", pacmanTex, Vector2::Zero, Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        animator->PlayAnimation(L"CatFrontMove", true);

        GameObject* map = object::Instantiate<GameObject>(enums::eLayerType::BackGround);

        SpriteRenderer* mapSr = map->AddComponent<SpriteRenderer>();
        mapSr->SetSize(Vector2(3.0f, 3.0f));  //윈도우 크기가 커졌으니 이에 맞춰 크기를 3배로 키워주었다
        graphics::Texture* mapTex = Resources::Find<graphics::Texture>(L"MAP");
        mapSr->SetTexture(mapTex);
        
        //게임 오브젝트 생성 후 레이어와 게임 오브젝트들의 init 함수 호출
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

        //이젠 플레이 씬이 무엇인지 구분할 수 있으니 삭제
        //wchar_t name_str[50] = L"PlayScene";
        //int len = wcsnlen_s(name_str, 50);

        //TextOut(hdc, 0, 0, name_str, len);
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