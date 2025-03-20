#include "oepPlayScene.h"
#include "oepGameObject.h"

namespace oep {
    PlayScene::PlayScene()
    {
    }

    void PlayScene::Initialize()
    {
        //이런 식으로 씬에 오브젝트 추가
        //GameObject* obj = new GameObject();
        //AddGameObject(obj);

        //이번에는 씬에 여러 오브젝트를 추가해 보는 예제를 수행(10개만 진행)
        for (size_t i = 0; i < 10; i++) {
            GameObject* obj = new GameObject();
            obj->SetPosition(rand() % 1600, rand() % 900);
            AddGameObject(obj);
        }
    }

    void PlayScene::Update()
    {
        //해당 씬의 오브젝트들을 Update
        //for (GameObject* gameObj : mGameObjects) {  //GameObject*는  auto로 수정해도 된다.
        //    //(auto는 자동으로 알맞는 자료형을 맞춰주는 것으로 자료형이 길거나 가독성을 해치면 사용. 그러나, 무슨 자료형인지 알 수 없는 상황이 발생할 수 있어 유의해서 사용해야 한다.)
        //    gameObj->Update();
        //}

        //그러나 문제점은 이 씬은 상속을 받았는데 게임 오브젝트는 private 멤버로 선언되어 있어서 직접 접근이 불가능하다.
        //그렇기에 이러한 경우 부모의 함수를 호출해 와서 그대로 사용하면 원하는 동작을 간단하게 할 수 있는데 부모의 함수 호출은 다음과 같다.
        Scene::Update();  //이렇게 범위 지정 연산자로 부모의 멤버 함수임을 알려주면 부모의 public 멤버 함수를 그대로 호출해 와서 사용할 수 있다.
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