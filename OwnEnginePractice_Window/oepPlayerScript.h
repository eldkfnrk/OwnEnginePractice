#pragma once
#include "..\OwnEnginePractice_SOURCE\oepScript.h"

namespace oep {
	//이 클래스는 스크립트 컴포넌트인데 플레이어에 로직을 수행할 컴포넌트로 각 오브젝트마다 동직이 다르기 때문에 스크립트 컴포넌트는 여러 개가 존재한다.
	class PlayerScript : public Script
	{
	public:
		PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		~PlayerScript();

	private:

	};
}
