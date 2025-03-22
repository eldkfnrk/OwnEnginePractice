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
            //Player* bg = new Player();  //이러면 지역 변수로 이 함수 내에서만 쓸 수 있기 때문에 멤버 변수로 변경
            bg = new Player();

            Transform* tr = bg->AddComponent<Transform>();
            tr->SetName(L"TR");
            tr->SetPos(Vector2(0,0));

            SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
            sr->SetName(L"SR");
            //sr->ImageLoad(L"D:\\OwnEnginePractice\\Resources\\CloudOcean.png");  //이렇게 작성한 경로를 절대 경로라고 한다.(배포없이 개인 컴퓨터에서만 돌려볼 거라면 상관x)

            //절대 경로는 위에 보이는 것처럼 컴퓨터 내에 파일의 정확한 위치 경로를 말하는 것으로 이 경우 경로와 정확히 일치해야지만 파일을 찾을 수 있다. 
            //그러나 게임에서는 절대 경로를 사용하면 안 되는 이유가 있는데 그것은 바로 게임은 배포를 하게 되고 배포한 게임을 다른 컴퓨터 환경에서 다운을 받아서 하는 것이기 때문에
            //리소스의 경로가 정확하게 일치할 수가 없어서 리소스를 찾지 못해서 게임을 플레이하지 못하는 문제가 발생할 수 있기 때문이다. 모든 컴퓨터가 경로가 똑같을 수는 없기에 이런 문제가
            //발생하는 것으로 이를 방지하기 위해서 우리는 상대 경로라는 것을 사용하여야 한다. 상대 경로는 리소스의 정확한 위치가 아닌 상대적인 위치 경로를 말한다.
            //이게 무슨 소리냐 하면 절대 경로처럼 리소스의 정확한 위치가 아닌 리소스가 위치한 폴더까지만 표현해주는 것으로 리눅스의 위치 변경과 비슷한 형태를 보인다.(예시 - ..\\폴더명\\리소스 파일명)
            //이렇게 상대 경로를 사용하게 되면 폴더 이름과 리소스 파일의 이름을 바꾸는 것이 아닌 이상 어느 컴퓨터 환경에서도 파일을 찾을 수 있다.

            sr->ImageLoad(L"..\\Resources\\CloudOcean.png");  //상대 경로

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

        //씬을 구별하기 위해 화면에 어느 씬인지 출력(아직 씬을 제대로 구성하지 않아 씬 간의 구분이 어렵기 때문에 씬의 출력 혹은 변경이 제대로 이루어지는지 보기 위한 테스트 코드)
        wchar_t name_str[50] = L"PlayScene";
        int len = wcsnlen_s(name_str, 50);

        TextOut(hdc, 0, 0, name_str, len);
    }

    void PlayScene::OnEnter()
    {
        
    }

    void PlayScene::OnExit()
    {
        //씬을 나갈 때 씬에 배치된 오브젝트들을 초기 상태로 돌려놓는다.
        Transform* tr = bg->GetComponent<Transform>();
        tr->SetPos(Vector2(0, 0));
    }

    PlayScene::~PlayScene()
    {
    }
}