#include "oepEndScene.h"
#include "..\OwnEnginePractice_SOURCE\oepInput.h"
#include "..\OwnEnginePractice_SOURCE\oepSceneManager.h"

namespace oep {
	EndScene::EndScene()
	{
	}

	void EndScene::Initialize()
	{
		Scene::Initialize();
	}

	void EndScene::Update()
	{
		Scene::Update();
	}

	void EndScene::LateUpdate()
	{
		Scene::LateUpdate();
		if (Input::GetKeyDown(eKeyCode::N)) {
			SceneManager::LoadScene(L"TitleScene");
		}
	}

	void EndScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		//씬을 구별하기 위해 화면에 어느 씬인지 출력(아직 씬을 제대로 구성하지 않아 씬 간의 구분이 어렵기 때문에 씬의 출력 혹은 변경이 제대로 이루어지는지 보기 위한 테스트 코드)
		wchar_t name_str[50] = L"EndScene";
		int len = wcsnlen_s(name_str, 50);

		TextOut(hdc, 0, 0, name_str, len);
	}

	void EndScene::OnEnter()
	{
	}

	void EndScene::OnExit()
	{
	}

	EndScene::~EndScene()
	{
	}
}