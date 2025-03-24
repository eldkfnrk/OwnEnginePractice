#pragma once
#include "oepEntity.h"
#include "CommonInclude.h"

namespace oep {
	class Resource : public Entity  //�߻� Ŭ����
	{
	public:
		Resource(enums::eResourceType type); 

		virtual HRESULT Load(const std::wstring& path) = 0;  //���� ���� �Լ�

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
