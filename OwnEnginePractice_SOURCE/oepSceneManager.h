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

		static void Release();  //이 클래스는 객체를 만들지 않고 전역 함수처럼 사용할 수 있도록 정의했기 때문에 딱히 소멸자가 없어서 직접 메모리 해제를 할 함수 생성

	private:
		static std::map<std::wstring, Scene*> mScenes;  

		static Scene* mActiveScene;
	};

	//우리가 만든 이 클래스는 멤버들을 전역으로 사용할 것인데 캡슐화시킬 것은 캡슐화시키기 위해 만든 것으로 따로 객체를 생성해서 사용할 목적이 있지 않다.

	//싱글톤이라는 개념이 있다.
	//싱글톤은 객체 생성을 클래스 안에서 진행하기 때문에 프로그램에서 객체가 단 하나만 있을 수 있게 한다. 그리고 그것은 클래스 내부에서 아래와 같이 static으로 생성한다.
	//그리고 객체가 하나만 있을 수 있도록 생성자 소멸자를 private 멤버로 선언하여 객체 생성을 제한한다. 이렇게 하면 객체는 단 하나가 되고 이를 사용하도록 설계하는 것이 싱글톤이다.
	//그러나 단점으로는 소멸자 호출이 불가능하다 보니 메모리 관리를 따로 하는 것이 불가능하다. 그래서 개발자들의 사용 여부는 취향 차이로 장점과 단점이 있으니 편한대로 사용할지 결정하면 된다.
	//static SceneManager sceneManager;

	//싱글톤은 코드를 작성하는데 이점을 주는 대신에 메모리를 마음대로 컨트롤할 수 없고 우리가 만든 클래스는 우리 마음대로 메모리 할당 해제를 할 수 있지만 싱글톤의 이점은 없다.
	//두 방법 모두 메모리 릭은 없기 때문에 선호하는 방법을 사용하면 되는 것이다.
}