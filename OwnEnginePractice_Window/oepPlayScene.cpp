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

        //�̷��� {}�� ������ �Լ��� ���� ��ó�� ���������� ����(�Լ��� ���� ��ó�� �����Ѵٴ� ���� {}�ȿ����� ������ {}�ȿ��� �ְ� �̿ܿ��� ���ٴ� ���� �ǹ��Ѵ�.)
        //�׷��� ������ ������ �̸��� �ᵵ �ߺ����� ���� �������� ������ ������ ���̴�.
        //�� 3���� �÷��̾� ������Ʈ �߰�(���� �����غ��� ����)
        {
            Player* pl = new Player();
            
            //������Ʈ �߰�(�� �ʱ� �������� ����)
            Transform* tr = pl->AddComponent<Transform>();
            tr->SetName(L"TR");
            tr->SetPos(rand() % 1600, rand() % 900);

            SpriteRenderer* sr = pl->AddComponent<SpriteRenderer>();
            sr->SetName(L"SR");

            //���� ���� ������Ʈ �߰�
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