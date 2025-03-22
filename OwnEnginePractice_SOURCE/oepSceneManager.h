#pragma once
#include "oepScene.h"

namespace oep {
	class SceneManager
	{
	public:
		template <typename T>
		static Scene* CreateScene(const std::wstring& name) { 
			T* scene = new T();
		
			scene->SetName(name);  //�̸� ����
			scene->Initialize();  //���� �ʱ�ȭ
			
			mScenes.insert(std::make_pair(name, scene));

			return scene;
		}

		static Scene* LoadScene(const std::wstring& name) {  
			//���� ����Ǹ鼭 ���� ������ Ż���� �� ���� ������ �̷������ �ϴ� ������ ����
			if (mActiveScene) {  //�������� ���� nullptr�� �ƴϸ� true�� nullptr�̸� false�� ��ȯ(���� ���� �ÿ��� �ƹ� ���� �����ϰ� ���� ���� �����̱� ������ �̷��� ���� ������ ������ �߻��� �� �ִ�.)
				mActiveScene->OnExit();
			}

			std::map<std::wstring, Scene*>::iterator iter = mScenes.find(name);

			if (iter == mScenes.end()) {
				return nullptr;  
			}

			mActiveScene = iter->second;  

			//�ٲ� ������ ���鼭 �ش� ���� ����Ǿ�� �� ������ ����
			mActiveScene->OnEnter();

			return iter->second;
		}

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

	private:
		static std::map<std::wstring, Scene*> mScenes;  

		static Scene* mActiveScene;
	};
}