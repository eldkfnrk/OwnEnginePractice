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