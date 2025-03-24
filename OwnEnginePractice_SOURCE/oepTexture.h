#pragma once
#include "oepResource.h"

namespace oep::graphics {  
	class Texture : public Resource
	{
	public:
		enum class eTextureType {  //텍스쳐 파일의 종류를 구분하기 위한 열거형
			Png,  //png파일인 경우
			Bmp,  //bmp파일인 경우
			None,  //아무것도 아닌 경우
		};

		Texture();

		HRESULT Load(const std::wstring& path) override;
		
		UINT GetWidth() {
			return mWidth;
		}

		UINT GetHeight() {
			return mHeight;
		}

		HDC GetHdc() {
			return mHdc;
		}

		eTextureType GetTextureType() {
			return mType;
		}

		Gdiplus::Image* GetImage() {
			return mImage;
		}

		~Texture();

	private:
		eTextureType mType;  

		Gdiplus::Image* mImage; 
		HBITMAP mBitmap; 
		HDC mHdc;  

		UINT mWidth;
		UINT mHeight;
	};
}
