#pragma once

#include "..\OwnEnginePractice_SOURCE\oepSceneManager.h"
#include "oepPlayScene.h"

namespace oep {
	void LoadScenes() {
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		//추후 추가될 씬들
		//SceneManager::CreateScene<PlayScene>(L"TitleScene");
		//SceneManager::CreateScene<PlayScene>(L"EndScene");

		SceneManager::LoadScene(L"PlayScene");
	}
}