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
			scene->Initialize();  //씬의 초기화
			
			mScenes.insert(std::make_pair(name, scene));

			return scene;
		}

		static Scene* LoadScene(const std::wstring& name) {  
			//씬이 변경되면서 기존 씬에서 탈출할 때 기존 씬에서 이루어져야 하는 동작을 수행
			if (mActiveScene) {  //포인터의 값이 nullptr이 아니면 true를 nullptr이면 false를 반환(게임 시작 시에는 아무 씬도 시작하고 있지 않은 상태이기 때문에 이렇게 하지 않으면 오류가 발생할 수 있다.)
				mActiveScene->OnExit();
			}

			std::map<std::wstring, Scene*>::iterator iter = mScenes.find(name);

			if (iter == mScenes.end()) {
				return nullptr;  
			}

			mActiveScene = iter->second;  

			//바뀐 씬으로 들어가면서 해당 씬에 선행되어야 할 동작을 수행
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