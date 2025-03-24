#include "oepPlayScene.h"
#include "..\OwnEnginePractice_SOURCE\oepTransform.h"
#include "..\OwnEnginePractice_SOURCE\oepSpriteRenderer.h"
#include "..\OwnEnginePractice_SOURCE\oepInput.h"
#include "..\OwnEnginePractice_SOURCE\oepSceneManager.h"
#include "..\OwnEnginePractice_SOURCE\oepObject.h"
#include "..\OwnEnginePractice_SOURCE\oepTexture.h" 
#include "..\OwnEnginePractice_SOURCE\oepResources.h"  
#include "oepPlayer.h"

namespace oep {
    PlayScene::PlayScene() : bg(nullptr)
    {
    }

    void PlayScene::Initialize()
    {
        {
            bg = object::Instantiate<Player>(enums::eLayerType::BackGround);

            //���� ���ҽ����� �ε��ϴ� ���� ���� �Լ����� �� ���� �ε带 �� ���̴� ���⼭�� �ε�� ���ҽ� �� �˸´� ���� ã�Ƽ� ����ϸ� �ȴ�.
            //graphics::Texture* tex = new graphics::Texture();  //�ؽ��� ���ҽ� �߰�
            //tex->Load(L"..\\Resources\\CloudOcean.png");  //�ؽ��� ���ҽ��� �̹��� �ε�

            SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
            sr->SetName(L"SR");
            //sr->ImageLoad(L"..\\Resources\\CloudOcean.png");  //��� ���

            //���� ���ҽ� �ε���� �������Ҵٸ� �� ���ҽ��� ������ ���� �۾��� �ʿ��ѵ� �ؽ��Ĵ� ȭ�� ����� �Ǵ� ���ҽ��̱� ������ ����� ����ϴ� SpriteRenderer ������Ʈ��
            //������ �־�� �Ѵ�.
            graphics::Texture* bg = Resources::Find<graphics::Texture>(L"BG");   //�̶� ���ҽ��� Ű���� ��Ȯ�� �˰� ����ؾ��� �ƴϸ� ���ҽ��� ��ã�� ���� ������ �߻�
            sr->SetTexture(bg);
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