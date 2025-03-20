#pragma once

#include "..\OwnEnginePractice_SOURCE\oepSceneManager.h"
#include "oepPlayScene.h"

namespace oep {
	void LoadScenes() {
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		//���� �߰��� ����
		//SceneManager::CreateScene<PlayScene>(L"TitleScene");
		//SceneManager::CreateScene<PlayScene>(L"EndScene");

		SceneManager::LoadScene(L"PlayScene");
	}
}