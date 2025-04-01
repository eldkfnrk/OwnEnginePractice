#pragma once
#include "..\OwnEnginePractice_SOURCE\oepGameObject.h"

namespace oep {
	class Cat : public GameObject
	{
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:

	};
}