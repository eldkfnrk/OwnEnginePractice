#pragma once
#include "CommonInclude.h"
#include "oepResource.h"

namespace oep {
	class Resources
	{
	public:
		template <typename T>
		static T* Find(const std::wstring& key) {  
			auto iter = mResources.find(key);

			if (iter == mResources.end()) {  
				return nullptr;
			}

			return dynamic_cast<T*>(iter->second);
		}

		template <typename T>
		static T* Load(const std::wstring& key, const std::wstring& path) {
			T* resource = Resources::Find<T>(key);  

			if (resource != nullptr) {  
				return resource;
			}

			resource = new T();
			if (FAILED(resource->Load(path))) {
				assert(false);  
			}

			resource->SetName(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));

			return resource;
		}

		//SceneManager클래스처럼 이 클래스도 따로 객체를 만드는 클래스가 아니기 때문에 소멸자가 없으니 따로 메모리 해제를 시킬 함수 생성
		static void Release();

	private:
		static std::map<std::wstring, Resource*> mResources;  
	};
}
