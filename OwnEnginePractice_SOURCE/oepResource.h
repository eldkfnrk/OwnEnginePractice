#pragma once
#include "oepEntity.h"
#include "CommonInclude.h"

namespace oep {
	class Resource : public Entity  //추상 클래스
	{
	public:
		Resource(enums::eResourceType type); 

		virtual HRESULT Load(const std::wstring& path) = 0;  //순수 가상 함수

		void SetPath(const std::wstring& path) {
			mPath = path;
		}

		const std::wstring& GetPath() {
			return mPath;
		}

		virtual ~Resource();

	private:
		const enums::eResourceType mType;
		std::wstring mPath;  
	};
}
