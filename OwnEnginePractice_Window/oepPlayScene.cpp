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
    PlayScene::PlayScene() : bg(nullptr)
    {
    }

    void PlayScene::Initialize()
    {
        //ī�޶� ��ũ��Ʈ�� ����� �� ī�޶� ���� ������Ʈ�� ����ĸ� ��ȭ�� �����غ��� ���ѵ� ��ȭ�� �Կ��ϴ� ī�޶� �ִ� �̰� ���ӿ����� ī�޶� ������Ʈ�� �� �� �ִ�.
        //�׷��� ī�޶� ������ �ΰ� ���� ���� ������ ��ȭ�� ���� �� ī�޶� �����̸鼭 ���ΰ��̳� ȯ�� ���� ��µ� �̷� �� ī�޶� ��� ���ؼ� ī�޶� ������ �ʿ��ϴ�.
        //�׸��� �� ī�޶� ������ ���ӿ��� ������Ʈ�� ���̴�. �׷��� ī�޶� ������Ʈ�� ������ �ϴ� ���̴�. �׸��� ī�޶�� ȭ�鿡 ��¾ʾƾ� �ϱ� ������ ���̾ None�̴�.
        GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None);
        Camera* cameraComp = camera->AddComponent<Camera>();

        renderer::mainCamera = cameraComp;  //���� ī�޶�

        PlayerScript* sc = camera->AddComponent<PlayerScript>();

        bg = object::Instantiate<Player>(enums::eLayerType::BackGround);
        
        SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
        sr->SetName(L"SR");
        graphics::Texture* tex = Resources::Find<graphics::Texture>(L"BG");   
        sr->SetTexture(tex);
        
        //��ũ��Ʈ ������ �°� �����ϴ��� ��, ��ũ��Ʈ ������Ʈ�� �� �����ϴ��� Ȯ���ϴ� �׽�Ʈ �ڵ�
        //PlayerScript* sc = bg->AddComponent<PlayerScript>();
        //sc->SetName(L"SC");
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