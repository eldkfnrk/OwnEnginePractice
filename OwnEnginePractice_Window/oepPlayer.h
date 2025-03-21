#pragma once
#include "..\OwnEnginePractice_SOURCE\oepGameObject.h"

namespace oep {
	class Player : public GameObject
	{
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:

	};
}
