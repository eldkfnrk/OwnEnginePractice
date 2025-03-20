#include "oepPlayScene.h"
//#include "oepGameObject.h"
#include "..\OwnEnginePractice_SOURCE\oepTransform.h"
#include "..\OwnEnginePractice_SOURCE\oepSpriteRenderer.h"
#include "oepPlayer.h"

namespace oep {
    PlayScene::PlayScene()
    {
    }

    void PlayScene::Initialize()
    {
        //for (size_t i = 0; i < 10; i++) {
        //    GameObject* obj = new GameObject();
        //    obj->SetPosition(rand() % 1600, rand() % 900);
        //    AddGameObject(obj);
        //}

        //이렇게 {}로 묶으면 함수로 묶은 것처럼 개별적으로 동작(함수로 묶은 것처럼 동작한다는 것은 {}안에서의 변수는 {}안에만 있고 이외에는 없다는 것을 의미한다.)
        //그렇기 때문에 동일한 이름을 써도 중복으로 인한 오류없이 동작이 가능한 것이다.
        //총 3개의 플레이어 오브젝트 추가(씬을 구성해보는 예제)
        {
            Player* pl = new Player();
            
            //컴포넌트 추가(각 초기 설정까지 진행)
            Transform* tr = pl->AddComponent<Transform>();
            tr->SetName(L"TR");
            tr->SetPos(rand() % 1600, rand() % 900);

            SpriteRenderer* sr = pl->AddComponent<SpriteRenderer>();
            sr->SetName(L"SR");

            //씬에 게임 오브젝트 추가
            AddGameObject(pl);
        }

        {
            Player* pl = new Player();

            Transform* tr = pl->AddComponent<Transform>();
            tr->SetName(L"TR");
            tr->SetPos(rand() % 1600, rand() % 900);

            SpriteRenderer* sr = pl->AddComponent<SpriteRenderer>();
            sr->SetName(L"SR");

            AddGameObject(pl);
        }

        {
            Player* pl = new Player();

            Transform* tr = pl->AddComponent<Transform>();
            tr->SetName(L"TR");
            tr->SetPos(rand() % 1600, rand() % 900);

            SpriteRenderer* sr = pl->AddComponent<SpriteRenderer>();
            sr->SetName(L"SR");

            AddGameObject(pl);
        }
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