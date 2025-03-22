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
            //sr->ImageLoad(L"..\\Resources\\CloudOcean.png");  //��� ���

            //AddGameObject(bg, enums::eLayerType::BackGround);

            //bg = object::Instantiate<Player>(enums::eLayerType::BackGround, Vector2(100.0f, 100.0f));
            bg = object::Instantiate<Player>(enums::eLayerType::BackGround);

            //�� ������Ʈ�� ����� ������Ʈ�� ���� �ϳ��ϳ� �߰����־�� �Ѵ�.(�� ������Ʈ���� ������Ʈ�� �ٸ��� �������� ���� ������Ʈ�� �����ϰ�� ��� ���� �߰����־�� �Ѵ�.)
            //�����ؾ� �� ���� ������Ʈ�� �߰��� �� �� ������Ʈ�� ������ ������ �̸��� �ߺ��Ǹ� �� �ȴ�.
            SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
            sr->SetName(L"SR");
            sr->ImageLoad(L"..\\Resources\\CloudOcean.png");  //��� ���
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