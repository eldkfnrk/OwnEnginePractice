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

		static void Destroy();
		static void Release();  //이 클래스는 객체를 만들지 않고 전역 함수처럼 사용할 수 있도록 정의했기 때문에 딱히 소멸자가 없어서 직접 메모리 해제를 할 함수 생성

	private:
		static std::map<std::wstring, Scene*> mScenes;  

		static Scene* mActiveScene;
	};
}