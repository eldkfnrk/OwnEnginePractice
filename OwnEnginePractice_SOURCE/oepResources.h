#pragma once
#include "CommonInclude.h"
#include "oepResource.h"

namespace oep {
	//Resources 클래스 - 게임에 사용되는 모든 리소스들을 관리하는 클래스
	//씬매니저처럼 리소스들을 모아서 관리하여 리소스 사용 시의 번거러움을 줄여준다.
	class Resources
	{
	public:
		Resources();

		//원하는 리소스를 찾는 함수
		//리소스의 형태가 다양하기 때문에 모든 리소스에 대응할 수 있도록 템플릿 함수로 작성
		//이 함수 또한 여러 파일에서 접근할 수 있어야 하니 static 선언을 해준다.
		template <typename T>
		static T* Find(const std::wstring& key) {  //키를 입력받아 쌍을 이루는 값을 찾는 함수
			//STL은 원소를 찾거나 접근하면 해당 데이터에 접근할 수 있는 포인터 변수를 가지고 있는 iterator(반복자)를 반환해준다.
			//std::map<std::wstring, Resource*>::iterator iter = mResources.find(key);
			auto iter = mResources.find(key);  //위의 자료형처럼 자료형의 이름이 길어서 가독성을 해치는 경우 값의 자료형에 맞춰 변수의 자료형을 정하는 auto라는 것을 사용하면 좋다.
			//보통 맵에서 원소를 찾을 때 auto를 자주 쓴다. 그러나, auto가 편리하긴 하지만 무조건 auto를 쓰면 무슨 자료형인지 헷갈리 수 있는 문제가 있으니 적절히 사용하여야 한다.

			if (iter == mResources.end()) {  //find함수는 찾는 원소가 없으면 트리의 end()값을 반환하기 때문에 이는 찾는 값이 없다는 의미이다.
				return nullptr;
			}

			return dynamic_cast<T*>(iter->second);
		}

		//리소스를 Load해주는 함수(리소스를 프로그램에 가지고 와서 저장하는 함수)
		template <typename T>
		static T* Load(const std::wstring& key, const std::wstring& path) {
			T* resource = Resources::Find<T>(key);  //만약 Load를 하려는 리소스가 이미 트리에 저장되어 있는지 확인하기 위한 변수

			if (resource != nullptr) {  //리소스를 찾았는데 값이 있다면 굳이 추가할 필요가 없기 때문에 찾은 리소스를 반환
				return resource;
			}

			//동일한 리소스가 없다면 해당 리소스를 Load해주어야 한다.
			resource = new T();
			if (FAILED(resource->Load(path))) {  //이 Load 함수는 Resource 클래스의 순수 가상 함수로 그렇다면 T에 들어오는 값에 맞게 알맞은 클래스에서 재정의한 함수를 호출(반환 값은 HRESULT)
				//FAILED는 HRESULT값을 사용할 때 사용할 수 있는 것으로 인자 값이 S_FALSE면 if문에 걸리고 S_OK면 if문을 벗어날 것이다.
				//즉, FAILED는 리소스 로드의 실패 여부를 확인할 수 있는 것이다.(굳이 비교문을 사용하지 않아도 되고 쉽게 읽고 그 의도를 파악할 수 있어서 좋다)
				//MessageBox(nullptr, L"Resource Load Failed!", L"Error", MB_OK);  //리소스 로드에 실패했다는 메시지 박스 출력
				
				//메시지 박스 대신 assert 함수 사용
				//왜냐하면, assert를 사용하면 문제 발생 시 assert 함수가 호출된 위치로 이동하기 때문에 무슨 문제가 발생한 것인지 빠르게 파악할 수 있기 때문이다.
				assert(false);  //프로그램을 강제 종료시키는 함수(그리고 프로그램 종료와 동시에 함수가 호출된 위치로 이동시켜준다.)

				//assert함수가 호출되면 프로그램이 종료되기 때문에 굳이 assert함수 밑에 코드를 작성할 필요가 없다.(어차피 코드가 동작하지 않을 것이기 떄문이다.)
				//return nullptr;  //리소스 로드를 실패한 경우 nullptr 반환
			}

			resource->SetName(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));

			return resource;
		}

		~Resources();

	private:
		//모든 리소스들을 관리하기 위해선 모든 리소스를 가지고 있어야 한다. 그러나, 리소스의 종류가 적다면 상관없지만 많다면 벡터나 리스트 같은 구조를 사용하면
		//원하는 리소스를 찾는 시간이 커지기 때문에 이들보다 조금 더 빠르게 원소를 찾을 수 있는 트리 구조를 사용하여 리소스들을 저장해놓는다.
		//그리고 이 트리는 여러 씬에서 접근해서 사용할 것이기 때문에 전역 변수처럼 사용할 수 있는 정적 변수로 선언(데이터 영역에 올라가기 때문에 다른 곳에서도 접근이 가능)
		static std::map<std::wstring, Resource*> mResources;  //키-값 쌍으로 이루어진 트리 구조 map	
	};
}
