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

            //컴포넌트를 수정한 형태로 변경
            Player* bg = new Player();

            Transform* tr = bg->AddComponent<Transform>();
            tr->SetName(L"TR");
            tr->SetPos(Vector2(0,0));

            SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
            sr->SetName(L"SR");
            sr->ImageLoad(L"D:\\OwnEnginePractice\\Resources\\CloudOcean.png");  //이렇게 경로를 문자열로 전달하는 경우에는 \을 2개 사용하여야 한다.

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