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
        //카메라 스크립트를 만들고 왜 카메라 게임 오브젝트를 만드냐면 영화를 생각해보면 편한데 영화를 촬영하는 카메라가 있다 이걸 게임에서는 카메라 컴포넌트로 볼 수 있다.
        //그러나 카메라만 가만히 두고 찍을 수도 있지만 영화를 만들 때 카메라를 움직이면서 주인공이나 환경 등을 담는데 이런 걸 카메라에 담기 위해선 카메라 감독이 필요하다.
        //그리고 그 카메라 감독이 게임에선 오브젝트인 것이다. 그래서 카메라 오브젝트를 만들어야 하는 것이다. 그리고 카메라는 화면에 출력않아야 하기 때문에 레이어가 None이다.
        GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None);
        Camera* cameraComp = camera->AddComponent<Camera>();

        renderer::mainCamera = cameraComp;  //메인 카메라

        PlayerScript* sc = camera->AddComponent<PlayerScript>();

        bg = object::Instantiate<Player>(enums::eLayerType::BackGround);
        
        SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
        sr->SetName(L"SR");
        graphics::Texture* tex = Resources::Find<graphics::Texture>(L"BG");   
        sr->SetTexture(tex);
        
        //스크립트 로직에 맞게 동작하는지 즉, 스크립트 컴포넌트가 잘 동작하는지 확인하는 테스트 코드
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