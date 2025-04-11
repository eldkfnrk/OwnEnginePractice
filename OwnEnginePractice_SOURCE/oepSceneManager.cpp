#include "oepSceneManager.h"

namespace oep {
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	Scene* SceneManager::LoadScene(const std::wstring& name) {
		if (mActiveScene) {  
			mActiveScene->OnExit();
		}

		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(name);

		if (iter == mScenes.end()) {
			return nullptr;
		}

		mActiveScene = iter->second;

		mActiveScene->OnEnter();

		return iter->second;
	}

	void SceneManager::Initialize()
	{
	}

	void SceneManager::Update()
	{
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

	void SceneManager::Destroy() {
		mActiveScene->Destroy();
	}

	void SceneManager::Release() {
		//이 함수는 소멸자가 없으니 이를 대체하여 메모리 해제를 하기 위한 함수
		//메모리 해제를 하고자 하는 위치에서 호출하여서 사용하도록 한다.
		for (auto& iter : mScenes) {
			delete iter.second;
			iter.second = nullptr;
		}
	}
}