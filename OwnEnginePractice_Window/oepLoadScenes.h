#pragma once

#include "..\OwnEnginePractice_SOURCE\oepSceneManager.h"
#include "oepPlayScene.h"

namespace oep {
	void LoadScenes() {
		//이 함수 내에서 게임의 여러 씬들을 SceneManager에 추가하게 된다.
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		//SceneManager::CreateScene<PlayScene>(L"TitleScene");
		//SceneManager::CreateScene<PlayScene>(L"EndScene");

		SceneManager::LoadScene(L"PlayScene");
	}
}