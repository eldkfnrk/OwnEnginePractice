#include "oepSceneManager.h"

namespace oep {
	//���� ��� �����̱� ������ �ݵ�� cpp���Ͽ��� �ʱ�ȭ�� �Ǿ�� �Ѵ�.
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
	}

	void SceneManager::Update()
	{
		//������ �÷����� �� �� ���� ���� Update�ϸ� �Ǳ� ������ �̿� ���� ���� ���� ���� ���� Update
		//���������� LateUpdate�� Render ���� ���� ���� ���� ���� �����ϰ� �ǵ��� �Ѵ�.
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