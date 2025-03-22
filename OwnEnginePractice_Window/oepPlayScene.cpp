#include "oepPlayScene.h"
#include "..\OwnEnginePractice_SOURCE\oepTransform.h"
#include "..\OwnEnginePractice_SOURCE\oepSpriteRenderer.h"
#include "..\OwnEnginePractice_SOURCE\oepInput.h"
#include "..\OwnEnginePractice_SOURCE\oepSceneManager.h"
#include "oepPlayer.h"

namespace oep {
    PlayScene::PlayScene() : bg(nullptr)
    {
    }

    void PlayScene::Initialize()
    {
        {
            //Player* bg = new Player();  //�̷��� ���� ������ �� �Լ� �������� �� �� �ֱ� ������ ��� ������ ����
            bg = new Player();

            Transform* tr = bg->AddComponent<Transform>();
            tr->SetName(L"TR");
            tr->SetPos(Vector2(0,0));

            SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
            sr->SetName(L"SR");
            //sr->ImageLoad(L"D:\\OwnEnginePractice\\Resources\\CloudOcean.png");  //�̷��� �ۼ��� ��θ� ���� ��ζ�� �Ѵ�.(�������� ���� ��ǻ�Ϳ����� ������ �Ŷ�� ���x)

            //���� ��δ� ���� ���̴� ��ó�� ��ǻ�� ���� ������ ��Ȯ�� ��ġ ��θ� ���ϴ� ������ �� ��� ��ο� ��Ȯ�� ��ġ�ؾ����� ������ ã�� �� �ִ�. 
            //�׷��� ���ӿ����� ���� ��θ� ����ϸ� �� �Ǵ� ������ �ִµ� �װ��� �ٷ� ������ ������ �ϰ� �ǰ� ������ ������ �ٸ� ��ǻ�� ȯ�濡�� �ٿ��� �޾Ƽ� �ϴ� ���̱� ������
            //���ҽ��� ��ΰ� ��Ȯ�ϰ� ��ġ�� ���� ��� ���ҽ��� ã�� ���ؼ� ������ �÷������� ���ϴ� ������ �߻��� �� �ֱ� �����̴�. ��� ��ǻ�Ͱ� ��ΰ� �Ȱ��� ���� ���⿡ �̷� ������
            //�߻��ϴ� ������ �̸� �����ϱ� ���ؼ� �츮�� ��� ��ζ�� ���� ����Ͽ��� �Ѵ�. ��� ��δ� ���ҽ��� ��Ȯ�� ��ġ�� �ƴ� ������� ��ġ ��θ� ���Ѵ�.
            //�̰� ���� �Ҹ��� �ϸ� ���� ���ó�� ���ҽ��� ��Ȯ�� ��ġ�� �ƴ� ���ҽ��� ��ġ�� ���������� ǥ�����ִ� ������ �������� ��ġ ����� ����� ���¸� ���δ�.(���� - ..\\������\\���ҽ� ���ϸ�)
            //�̷��� ��� ��θ� ����ϰ� �Ǹ� ���� �̸��� ���ҽ� ������ �̸��� �ٲٴ� ���� �ƴ� �̻� ��� ��ǻ�� ȯ�濡���� ������ ã�� �� �ִ�.

            sr->ImageLoad(L"..\\Resources\\CloudOcean.png");  //��� ���

            AddGameObject(bg, eLayerType::BackGround);
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

        //���� �����ϱ� ���� ȭ�鿡 ��� ������ ���(���� ���� ����� �������� �ʾ� �� ���� ������ ��Ʊ� ������ ���� ��� Ȥ�� ������ ����� �̷�������� ���� ���� �׽�Ʈ �ڵ�)
        wchar_t name_str[50] = L"PlayScene";
        int len = wcsnlen_s(name_str, 50);

        TextOut(hdc, 0, 0, name_str, len);
    }

    void PlayScene::OnEnter()
    {
        
    }

    void PlayScene::OnExit()
    {
        //���� ���� �� ���� ��ġ�� ������Ʈ���� �ʱ� ���·� �������´�.
        Transform* tr = bg->GetComponent<Transform>();
        tr->SetPos(Vector2(0, 0));
    }

    PlayScene::~PlayScene()
    {
    }
}