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
		//�� �Լ��� �Ҹ��ڰ� ������ �̸� ��ü�Ͽ� �޸� ������ �ϱ� ���� �Լ�
		//�޸� ������ �ϰ��� �ϴ� ��ġ���� ȣ���Ͽ��� ����ϵ��� �Ѵ�.
		for (auto& iter : mScenes) {
			delete iter.second;
			iter.second = nullptr;
		}
	}
}