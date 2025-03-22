#pragma once

#include "..\OwnEnginePractice_SOURCE\oepSceneManager.h"
#include "oepPlayScene.h"
#include "oepTitleScene.h"
#include "oepEndScene.h"

namespace oep {
	void LoadScenes() {
		//���� �߰� ������ �����ִ� ���� ����.(�ʱ�ȭ �������� ����� ������ ������ �� �ֱ� �����̴�.)
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<EndScene>(L"EndScene");

		//SceneManager::LoadScene(L"PlayScene");
		SceneManager::LoadScene(L"TitleScene");  //���� ���� �ÿ� ���� ���� ������ ���� Ÿ��Ʋ ���̱� ������ �̰��� ����� ���� ����.
	}
}