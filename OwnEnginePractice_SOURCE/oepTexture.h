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

		//새 이미지를 만드는 함수(전역 함수처럼 사용하도록 static 선언)
		static Texture* Create(const std::wstring& name, UINT width, UINT height);

		Texture();

		HRESULT Load(const std::wstring& path) override;
		
		void SetWidth(UINT width) {
			mWidth = width;
		}

		UINT GetWidth() {
			return mWidth;
		}

		void SetHeight(UINT height) {
			mHeight = height;
		}

		UINT GetHeight() {
			return mHeight;
		}

		HDC GetHdc() {
			return mHdc;
		}

		void SetTextureType(eTextureType type) {
			mType = type;
		}

		eTextureType GetTextureType() {
			return mType;
		}

		Gdiplus::Image* GetImage() {
			return mImage;
		}

		bool IsAlpha() {
			return mbAlpha;
		}

		~Texture();

	private:
		bool mbAlpha;  //알파 채널이 있는지 없는지 확인하는 변수

		eTextureType mType;  

		Gdiplus::Image* mImage; 
		HBITMAP mBitmap; 
		HDC mHdc;  

		UINT mWidth;
		UINT mHeight;
	};
}
