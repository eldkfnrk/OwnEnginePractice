#pragma once
#include "oepResource.h"

namespace oep::graphics {  //그래픽스와 관련된 것들을 분리하기 위해 oep네임스페이스 안에 graphics네임스페이스 하나를 더 추가 
	class Texture : public Resource
	{
	public:
		//oepEnums 파일에 추가하지 않는 이유는 이 클래스에서만 사용할 것이기 떄문이다. oepEnums는 여러 파일에서 접근해서 사용할 수 있도록 한 것으로 전역과 비슷하다.
		enum class eTextureType {  //텍스쳐 파일의 종류를 구분하기 위한 열거형
			Png,  //png파일인 경우
			Bmp,  //bmp파일인 경우
			None,  //아무것도 아닌 경우
		};

		Texture();

		//이 함수는 부모 클래스의 순수 가상 함수이기 때문에 반드시 재정의 해주어야 한다.
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
		eTextureType mType;  //텍스쳐 타입이 뭔지 저장

		Gdiplus::Image* mImage;  //png나 jpg등의 이미지 파일을 저장할 수 있는 변수
		HBITMAP mBitmap;  //리소스 중에는 bmp(비트맵)파일들도 있기 때문에 이 파일들을 저장할 수 있는 변수
		HDC mHdc;  //비트맵과 연결되서 사용할 dc를 따로 가지고 있어야 한다.(비트맵은 dc와 짝을 이루어야만 사용할 수 있다.)
		//보면 알겠지만 비트맵을 사용하는 것은 굉장히 까다롭다. 그래서 추가된 것이 Gdiplus(Gdi에 기능 추가)이고 비트맵 등은 그냥 Gdi라 한다.

		UINT mWidth;
		UINT mHeight;
	};
}
