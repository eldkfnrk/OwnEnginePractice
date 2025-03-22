#pragma once

#include "..\OwnEnginePractice_SOURCE\oepSceneManager.h"
#include "oepPlayScene.h"
#include "oepTitleScene.h"
#include "oepEndScene.h"

namespace oep {
	void LoadScenes() {
		//씬의 추가 순서도 맞춰주는 것이 좋다.(초기화 과정에서 생기는 문제를 방지할 수 있기 때문이다.)
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<EndScene>(L"EndScene");

		//SceneManager::LoadScene(L"PlayScene");
		SceneManager::LoadScene(L"TitleScene");  //게임 시작 시에 제일 먼저 나오는 씬은 타이틀 씬이기 때문에 이것은 변경될 일이 없다.
	}
}