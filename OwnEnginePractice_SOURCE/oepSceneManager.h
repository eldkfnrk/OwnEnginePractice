#pragma once
#include "oepScene.h"

namespace oep {
	//SceneManager 클래스 - 여러 씬들을 관리해주는 클래스
	//게임에는 많은 씬들이 있고 이들을 유기적으로 연결하여 동작하는데 이때 이 씬들을 한 번에 관리해 줄 수 있도록 관리자 역할을 하는 클래스가 필요하기 때문에 이 클래스를 구성한다.
	//씬의 이동에도 관여할 수도 있고 하니 곳곳에서 사용할 수 있도록 전역 혹은 정적 변수로 만들으면 된다.
	//보통 씬은 하나만 업데이트가 된다. 왜냐하면, 실제 플레이에서 플레이할 수 있는 씬은 최대 1개이기 때문이다. 롤을 예시로 보면 로비에서는 로비 씬만 로딩에서는 로딩 씬만 협곡에서는 해당 씬만 업데이트되는 것을 알 수 있다.
	class SceneManager
	{
	public:
		//씬을 생성하는 템플릿 함수(씬 클래스를 상속받아 만들어지는 수많은 씬들이 있을 것이기 때문에 템플릿 함수를 사용하여 모든 자료형들에 대응할 수 있도록 한다.)
		template <typename T>
		static Scene* CreateScene(const std::wstring& name) {  //반환형이 Scene*인 이유는 모든 씬은 Scene 클래스를 상속받기 때문에 부모 클래스 자료형으로 반환하고 사용할 때 알맞게 수정하여 사용하면 되기 때문이다.
			//인자로는 씬의 이름을 받아 이를 트리의 노드의 키 값으로 활용
			T* scene = new T();
		
			scene->SetName(name);  //이름 설정
			scene->Initialize();  //씬의 초기화(이는 만들어짐과 동시에 이루어져야 하기 때문에 여기서 호출)
			
			//insert 함수는 map(트리)의 삽입 함수이다.
			mScenes.insert(std::make_pair(name, scene)); //make_pair는 pair를 만들어주는 함수로 map(트리)에는 키값 쌍이 이루어진 pair가 구성 요소로써 삽입 가능하기 때문에 해당 함수로 pair로 만들어 삽입 

			return scene;
		}

		//실행하는 씬을 설정하는 함수(실제로 동작하는 씬은 하나 뿐이니 해당 씬이 있는지를 찾고 해당 씬을 활성화해 동작하도록 설정하는 함수)
		//반환형을 준 이유는 혹시나 실행 씬을 활성화하면서 이 씬을 활용해야 하는 등의 상황에 대응할 수 있도록 확장성을 높이기 위해 추가해준 것으로 필요하지 않다면 반환형을 안 줄 수도 있다.(그러나, 확장성이 높다는 측면에서 쓰는 게 좋다.)
		static Scene* LoadScene(const std::wstring& name) {  
			//find() 함수는 트리에서 특정 키 값을 가진 노드를 찾는 함수로 찾은 노드의 반복자를 반환한다.
			//반복자라는 것은 C++ 라이브러리가 제공하는 것으로 포인터와 비슷하며 컨테이너에 저장되어 있는 원소들을 참조할 때 사용한다.
			//간단히 말하면 원소의 위치를 갖고 있는 포인터와 비슷한 형태라는 것이다.
			std::map<std::wstring, Scene*>::iterator iter = mScenes.find(name);

			//find() 함수는 해당 키 값을 가진 노드를 찾지 못하면 컨테이너(map)의 end()를 반환한다.(컨테이너는 vector, 트리 같은 자료 구조들을 의미한다. 하나의 커다란 보관소로 보면 된다.)
			//end() 함수는 컨테이너(map)의 맨 마지막 주소 즉, 마지막 원소의 끝 주소를 반환한다. 컨테이너의 끝을 의미하는 것이다.
			if (iter == mScenes.end()) {
				return nullptr;  //해당 씬은 없으니 아무 것도 없다는 nullptr을 반환
			}

			mActiveScene = iter->second;  //실행하고 있는 씬을 설정 

			//반복자는 원소 위치를 갖고 있는 포인터와 비슷한 형태라 했으니 해당 반복자가 가리키는 노드가 있을 것이다.
			//그렇기 때문에 반복자는 first는 노드의 키 값을 second는 노드의 실제 값을 가리킨다.
			return iter->second;
		}

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

	private:
		//static std::vector<Scene*> mScenes;  //모든 씬을 관리하기 위해 모든 씬을 vector에 저장
		//그러나 씬은 많은데 찾는 씬이 vector 끝에 있으면 검색 시간이 증가하게 되는데 이런 단점을 보완하기 위해서 vector가 아닌 트리를 사용
		static std::map<std::wstring, Scene*> mScenes;  //트리는 노드로 구성되어 있고 그 노드는 씬의 이름과 실제 씬 데이터로 구성(키값 쌍 구성)

		static Scene* mActiveScene;  //실제 실행하는 씬은 하나이기 때문에 실제 실행되고 있는 씬이 어떤 씬인지 저장하기 위한 변수
	};
}