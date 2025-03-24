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

            //이제 리소스들을 로드하는 것은 따로 함수에서 한 번에 로드를 할 것이니 여기서는 로드된 리소스 중 알맞는 것을 찾아서 사용하면 된다.
            //graphics::Texture* tex = new graphics::Texture();  //텍스쳐 리소스 추가
            //tex->Load(L"..\\Resources\\CloudOcean.png");  //텍스쳐 리소스의 이미지 로드

            SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
            sr->SetName(L"SR");
            //sr->ImageLoad(L"..\\Resources\\CloudOcean.png");  //상대 경로

            //이제 리소스 로드까지 끝내놓았다면 그 리소스를 가지고 오는 작업이 필요한데 텍스쳐는 화면 출력이 되는 리소스이기 때문에 출력을 담당하는 SpriteRenderer 컴포넌트가
            //가지고 있어야 한다.
            graphics::Texture* bg = Resources::Find<graphics::Texture>(L"BG");   //이때 리소스의 키값을 정확히 알고 사용해야지 아니면 리소스를 못찾는 등의 문제가 발생
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