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

		void ImageLoad(const std::wstring& path);  //인자로 경로를 받아 해당 경로에 있는 이미지 파일을 불러오는 함수

		~SpriteRenderer();

	private:
		Gdiplus::Image* mImage;  //GDIPLUS는 기존 GDI에 추가적인 기능을 가진 것으로 Image는 이미지 파일을 저장하는 자료형이다.
		UINT mWidth;  //이미지의 너비
		UINT mHeight;  //이미지의 높이
	};
}
