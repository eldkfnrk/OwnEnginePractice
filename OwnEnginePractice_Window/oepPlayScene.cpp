#include "oepPlayScene.h"
#include "oepGameObject.h"

namespace oep {
    PlayScene::PlayScene()
    {
    }

    void PlayScene::Initialize()
    {
        //�̷� ������ ���� ������Ʈ �߰�
        //GameObject* obj = new GameObject();
        //AddGameObject(obj);

        //�̹����� ���� ���� ������Ʈ�� �߰��� ���� ������ ����(10���� ����)
        for (size_t i = 0; i < 10; i++) {
            GameObject* obj = new GameObject();
            obj->SetPosition(rand() % 1600, rand() % 900);
            AddGameObject(obj);
        }
    }

    void PlayScene::Update()
    {
        //�ش� ���� ������Ʈ���� Update
        //for (GameObject* gameObj : mGameObjects) {  //GameObject*��  auto�� �����ص� �ȴ�.
        //    //(auto�� �ڵ����� �˸´� �ڷ����� �����ִ� ������ �ڷ����� ��ų� �������� ��ġ�� ���. �׷���, ���� �ڷ������� �� �� ���� ��Ȳ�� �߻��� �� �־� �����ؼ� ����ؾ� �Ѵ�.)
        //    gameObj->Update();
        //}

        //�׷��� �������� �� ���� ����� �޾Ҵµ� ���� ������Ʈ�� private ����� ����Ǿ� �־ ���� ������ �Ұ����ϴ�.
        //�׷��⿡ �̷��� ��� �θ��� �Լ��� ȣ���� �ͼ� �״�� ����ϸ� ���ϴ� ������ �����ϰ� �� �� �ִµ� �θ��� �Լ� ȣ���� ������ ����.
        Scene::Update();  //�̷��� ���� ���� �����ڷ� �θ��� ��� �Լ����� �˷��ָ� �θ��� public ��� �Լ��� �״�� ȣ���� �ͼ� ����� �� �ִ�.
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