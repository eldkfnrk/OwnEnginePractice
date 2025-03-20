#include "oepSceneManager.h"

namespace oep {
	//정적 멤버 변수이기 때문에 반드시 cpp파일에서 초기화가 되어야 한다.
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
	}

	void SceneManager::Update()
	{
		//게임을 플레이할 때 한 개의 씬만 Update하면 되기 때문에 이와 같이 지금 실행 중인 씬만 Update
		//마찬가지로 LateUpdate와 Render 또한 현재 실행 중인 씬만 동작하게 되도록 한다.
		mActiveScene->Update();
	}

	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}
}