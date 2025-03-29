#include "oepTexture.h"
#include "oepApplication.h"

extern oep::Application application;  //extern - 프로그램에 선언된 전역 변수를 이 파일이 모르는 경우 전역 변수가 있음을 알려주고 이 변수를 사용할 수 있게 해주는 키워드


namespace oep::graphics {
	Texture::Texture() : Resource(enums::eResourceType::Texture), mType(eTextureType::None), mImage(nullptr), mBitmap(nullptr), mHdc(nullptr), mWidth(0), mHeight(0)
	{
		
	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		//Gdiplus는 기존 Gdi에서 기능을 추가해서 다루지 못했던 파일들을 다룰 수 있게 바꿔주었다고 설명하였는데 그래서 Gdiplus의 속도는 기존 Gdi보다 느리다.
		//그렇다면 애니메이션이 필요한 플레이어나 몬스터 오브젝트 등은 비트맵을 이용하는게 API에서는 조금 더 유리하다.
		//이것은 GPU를 사용하는 라이브러리 DirectX를 사용할 경우엔 신경 쓰지 않아도 되지만 그런 걸 사용하지 않는 지금 만드는 API 엔진에서는 유의해야 한다.
		if (ext == L"bmp") {  //bmp일 경우
			mType = eTextureType::Bmp;

			mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (mBitmap == nullptr) {
				return S_FALSE;  
			}

			BITMAP info = {};  

			GetObject(mBitmap, sizeof(BITMAP), &info);

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			HDC mainDC = application.GetHdc();
			mHdc = CreateCompatibleDC(mainDC);  

			HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);  
			DeleteObject(oldBitmap); 
		} 
		else if (ext == L"png") {  //png일 경우
			mType = eTextureType::Png;
			mImage = Gdiplus::Image::FromFile(path.c_str());  

			if (mImage == nullptr) {
				return S_FALSE;
			}

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}
		
		return S_OK;  
	}

	Texture::~Texture()
	{
	}
}