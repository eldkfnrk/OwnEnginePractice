#include "oepPlayScene.h" 
#include "..\OwnEnginePractice_SOURCE\oepTransform.h"
#include "..\OwnEnginePractice_SOURCE\oepSpriteRenderer.h"
#include "..\OwnEnginePractice_SOURCE\oepInput.h"
#include "..\OwnEnginePractice_SOURCE\oepSceneManager.h"
#include "..\OwnEnginePractice_SOURCE\oepObject.h"
#include "..\OwnEnginePractice_SOURCE\oepTexture.h" 
#include "..\OwnEnginePractice_SOURCE\oepResources.h"  
#include "..\OwnEnginePractice_SOURCE\oepRenderer.h"
#include "oepPlayer.h"
#include "oepPlayerScript.h"

namespace oep {
    PlayScene::PlayScene() : mPlayer(nullptr)
    {
    }

    void PlayScene::Initialize()
    {
        //GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None);
        //Camera* cameraComp = camera->AddComponent<Camera>();

        //renderer::mainCamera = cameraComp;  //메인 카메라

        //PlayerScript* sc = camera->AddComponent<PlayerScript>();

        //bg = object::Instantiate<Player>(enums::eLayerType::BackGround);
        //
        //SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
        //sr->SetName(L"SR");
        //graphics::Texture* tex = Resources::Find<graphics::Texture>(L"BG");   
        //sr->SetTexture(tex);

        //팩맨 기본 구성(맵과 플레이어 띄워보기)
        //위치 값을 이와 같이 주는 이유는 카메라가 바라보는 위치 0,0으로 냅두면 맵이 잘려서 보일테고 다른 값을 넣으면 맵이 중앙에 안 올 것이기 때문에 해상도의 절반
        //즉, 카메라가 화면의 중앙을 보게 하기 위해 이와 같이 위치 정보를 전달
        GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(336.0f, 423.0f));
        Camera* cameraComp = camera->AddComponent<Camera>();
        renderer::mainCamera = cameraComp;  //메인 카메라

        mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);

        SpriteRenderer* sr = mPlayer->AddComponent<SpriteRenderer>();
        sr->SetName(L"SR");
        sr->SetSize(Vector2(3.0f, 3.0f));  //윈도우 크기가 커졌으니 이에 맞춰 크기를 3배로 키워주었다
        graphics::Texture* pacmanTex = Resources::Find<graphics::Texture>(L"PACMAN0");
        sr->SetTexture(pacmanTex);
        PlayerScript* playerSc = mPlayer->AddComponent<PlayerScript>();

        //팩맨은 전체 화면을 그대로 출력하면서 플레이어는 캐릭터를 다른 몬스터들을 피해서 점수를 주는 구슬을 먹는 게임이기 때문에 따로 카메라에 타겟을 주지 않아도 된다.

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