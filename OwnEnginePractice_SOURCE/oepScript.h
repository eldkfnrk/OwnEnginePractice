#pragma once
#include "oepComponent.h"

namespace oep {
	class Script : public Component
	{
	public:
		Script();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		~Script();

	private:

	};
}
