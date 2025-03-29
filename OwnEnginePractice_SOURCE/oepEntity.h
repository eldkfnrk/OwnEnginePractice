#pragma once
#include "CommonInclude.h"

using namespace oep::math;

namespace oep {
	class Entity
	{
	public:
		Entity();

		void SetName(const std::wstring& name) {
			mName = name;
		}

		std::wstring& GetName() {
			return mName;
		}

		virtual ~Entity();  

	private:
		std::wstring mName;  //¿Ã∏ß
	};
}
