#include "oepPlayScene.h" 
#include "..\OwnEnginePractice_SOURCE\oepTransform.h"
#include "..\OwnEnginePractice_SOURCE\oepSpriteRenderer.h"
#include "..\OwnEnginePractice_SOURCE\oepInput.h"
#include "..\OwnEnginePractice_SOURCE\oepSceneManager.h"
#include "..\OwnEnginePractice_SOURCE\oepObject.h"
#include "..\OwnEnginePractice_SOURCE\oepTexture.h" 
#include "..\OwnEnginePractice_SOURCE\oepResources.h"  
#include "..\OwnEnginePractice_SOURCE\oepRenderer.h"
#include "..\OwnEnginePractice_SOURCE\oepAnimator.h"
#include "..\OwnEnginePractice_SOURCE\oepAnimation.h"
#include "oepPlayer.h"
#include "oepPlayerScript.h"

namespace oep {
    PlayScene::PlayScene() : mPlayer(nullptr)
    {
    }

    void PlayScene::Initialize()
    {
        GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(336.0f, 423.0f));
        Camera* cameraComp = camera->AddComponent<Camera>();
        renderer::mainCamera = cameraComp;  //���� ī�޶�

        mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);

        //�ִϸ��̼��� ����Ͽ� �������� ǥ���ؾ� �ϴ� ������Ʈ���� ���ݺ��� SpriteRenderer�� �ƴ� Animator�� ȭ�� ����� �ϰ� �ȴ�.
        //SpriteRenderer�� ��氰�� �����ִ� ���� �׸� �� ����ϰ� Animator�� �÷��̾� ���� �����̴� �͵��� �׸� �� ����Ѵ�.

        //SpriteRenderer* sr = mPlayer->AddComponent<SpriteRenderer>();
        //sr->SetName(L"SR");
        //sr->SetSize(Vector2(3.0f, 3.0f));  //������ ũ�Ⱑ Ŀ������ �̿� ���� ũ�⸦ 3��� Ű���־���
        graphics::Texture* pacmanTex = Resources::Find<graphics::Texture>(L"CHICKEN");
        //sr->SetTexture(pacmanTex);
        PlayerScript* playerSc = mPlayer->AddComponent<PlayerScript>();
        Animator* animator = mPlayer->AddComponent<Animator>();
        
        animator->CreateAnimation(L"CatFrontMove", pacmanTex, Vector2::Zero, Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.2f);
        animator->PlayAnimation(L"CatFrontMove", true);

        GameObject* map = object::Instantiate<GameObject>(enums::eLayerType::BackGround);

        SpriteRenderer* mapSr = map->AddComponent<SpriteRenderer>();
        mapSr->SetSize(Vector2(3.0f, 3.0f));  //������ ũ�Ⱑ Ŀ������ �̿� ���� ũ�⸦ 3��� Ű���־���
        graphics::Texture* mapTex = Resources::Find<graphics::Texture>(L"MAP");
        mapSr->SetTexture(mapTex);
        
        //���� ������Ʈ ���� �� ���̾�� ���� ������Ʈ���� init �Լ� ȣ��
        Scene::Initialize();
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

        //���� �÷��� ���� �������� ������ �� ������ ����
        //wchar_t name_str[50] = L"PlayScene";
        //int len = wcsnlen_s(name_str, 50);

        //TextOut(hdc, 0, 0, name_str, len);
    }

    void PlayScene::OnEnter()
    {
        
    }

    void PlayScene::OnExit()
    {
        Transform* tr = mPlayer->GetComponent<Transform>();
        tr->SetPosition(Vector2(0, 0));
    }

    PlayScene::~PlayScene()
    {
    }
}