#pragma once
#include "oepComponent.h"

namespace oep {
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void ImageLoad(const std::wstring& path);  

		~SpriteRenderer();

	private:
		Gdiplus::Image* mImage;  
		UINT mWidth;  
		UINT mHeight;  
	};
}
