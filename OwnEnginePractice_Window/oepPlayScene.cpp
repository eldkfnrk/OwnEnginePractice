#include "oepPlayScene.h"
#include "..\OwnEnginePractice_SOURCE\oepTransform.h"
#include "..\OwnEnginePractice_SOURCE\oepSpriteRenderer.h"
#include "..\OwnEnginePractice_SOURCE\oepInput.h"
#include "..\OwnEnginePractice_SOURCE\oepSceneManager.h"
#include "..\OwnEnginePractice_SOURCE\oepObject.h"
#include "oepPlayer.h"

namespace oep {
    PlayScene::PlayScene() : bg(nullptr)
    {
    }

    void PlayScene::Initialize()
    {
        {
            //bg = new Player();

            //Transform* tr = bg->AddComponent<Transform>();
            //tr->SetName(L"TR");
            //tr->SetPosition(Vector2(0,0));

            //SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
            //sr->SetName(L"SR");
            //sr->ImageLoad(L"..\\Resources\\CloudOcean.png");  //상대 경로

            //AddGameObject(bg, enums::eLayerType::BackGround);

            //bg = object::Instantiate<Player>(enums::eLayerType::BackGround, Vector2(100.0f, 100.0f));
            bg = object::Instantiate<Player>(enums::eLayerType::BackGround);

            //각 오브젝트가 사용할 컴포넌트는 직접 하나하나 추가해주어야 한다.(각 오브젝트마다 컴포넌트가 다르기 때문으로 공통 컴포넌트를 제외하고는 모두 따로 추가해주어야 한다.)
            //주의해야 할 점은 컴포넌트를 추가할 때 각 컴포넌트를 저장할 변수의 이름이 중복되면 안 된다.
            SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
            sr->SetName(L"SR");
            sr->ImageLoad(L"..\\Resources\\CloudOcean.png");  //상대 경로
        }
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

        wchar_t name_str[50] = L"PlayScene";
        int len = wcsnlen_s(name_str, 50);

        TextOut(hdc, 0, 0, name_str, len);
    }

    void PlayScene::OnEnter()
    {
        
    }

    void PlayScene::OnExit()
    {
        Transform* tr = bg->GetComponent<Transform>();
        tr->SetPosition(Vector2(0, 0));
    }

    PlayScene::~PlayScene()
    {
    }
}