#pragma once
#include "oepScene.h"

namespace oep {
	class SceneManager
	{
	public:
		template <typename T>
		static Scene* CreateScene(const std::wstring& name) { 
			T* scene = new T();
		
			scene->SetName(name);  //이름 설정
			//씬의 초기화 과정에서 오브젝트를 추가할 때 사용하기 위해서 현재 활성화된 씬을 이 씬으로 설정(오브젝트의 추가는 씬의 초기화 과정에서 일어나기 때문에 반드시 씬의 초기화보다 먼저 나와야 한다.)
			mActiveScene = scene;  
			scene->Initialize();  //씬의 초기화
			
			mScenes.insert(std::make_pair(name, scene));

			return scene;
		}

		static Scene* LoadScene(const std::wstring& name);

		static Scene* GetActiveScene() {
			return mActiveScene;
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