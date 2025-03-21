#include "oepPlayScene.h"
#include "..\OwnEnginePractice_SOURCE\oepTransform.h"
#include "..\OwnEnginePractice_SOURCE\oepSpriteRenderer.h"
#include "oepPlayer.h"

namespace oep {
    PlayScene::PlayScene()
    {
    }

    void PlayScene::Initialize()
    {
        {
            //Player* pl = new Player();
            //
            //Transform* tr = pl->AddComponent<Transform>();
            //tr->SetName(L"TR");
            //tr->SetPos(rand() % 1600, rand() % 900);

            //SpriteRenderer* sr = pl->AddComponent<SpriteRenderer>();
            //sr->SetName(L"SR");

            //AddGameObject(pl);

            //������Ʈ�� ������ ���·� ����
            Player* bg = new Player();

            Transform* tr = bg->AddComponent<Transform>();
            tr->SetName(L"TR");
            tr->SetPos(Vector2(0,0));

            SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
            sr->SetName(L"SR");
            sr->ImageLoad(L"D:\\OwnEnginePractice\\Resources\\CloudOcean.png");  //�̷��� ��θ� ���ڿ��� �����ϴ� ��쿡�� \�� 2�� ����Ͽ��� �Ѵ�.

            AddGameObject(bg);
        }

        //{
        //    Player* pl = new Player();

        //    Transform* tr = pl->AddComponent<Transform>();
        //    tr->SetName(L"TR");
        //    tr->SetPos(rand() % 1600, rand() % 900);

        //    SpriteRenderer* sr = pl->AddComponent<SpriteRenderer>();
        //    sr->SetName(L"SR");

        //    AddGameObject(pl);
        //}

        //{
        //    Player* pl = new Player();

        //    Transform* tr = pl->AddComponent<Transform>();
        //    tr->SetName(L"TR");
        //    tr->SetPos(rand() % 1600, rand() % 900);

        //    SpriteRenderer* sr = pl->AddComponent<SpriteRenderer>();
        //    sr->SetName(L"SR");

        //    AddGameObject(pl);
        //}
    }

    void PlayScene::Update()
    {
    }

    void PlayScene::LateUpdate()
    {
        Scene::LateUpdate();
    }

    void PlayScene::Render(HDC hdc)
    {
        Scene::Render(hdc);
    }

    PlayScene::~PlayScene()
    {
    }
}