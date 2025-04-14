#include "oepTexture.h"
#include "oepApplication.h"
#include "oepResources.h"

extern oep::Application application;  

namespace oep::graphics {
	Texture* Texture::Create(const std::wstring& name, UINT width, UINT height) {
		Texture* image = Resources::Find<Texture>(name);  //혹시 동일한 이름의 이미지 파일이 로드되어 있는지 확인하기 위해 Find를 해준다.

		if (image) {  //동일한 이름의 이미지 파일이 있다면 해당 이미지 파일 반환
			return image;
		}

		image = new Texture();

		image->SetName(name);
		image->SetWidth(width);
		image->SetHeight(height);

		HDC hdc = application.GetHdc();
		HWND hwnd = application.GetHwnd();

		//이미지를 만들기 위한 비트맵과 DC 저장
		//코드를 이용하여 직접 비트맵을 만들면 24비트짜리 비트맵을 생성(그러면 AlphaBlend 함수로는 출력이 안 되고 TransParentBlt 함수를 사용하여 출력하여야 한다.)
		//위의 사항을 주의하지 않으면 애니메이션을 만들고 사용하지 못하는 경우가 발생할 수 있다.
		image->mBitmap = CreateCompatibleBitmap(hdc, width, height);  //빈 비트맵 만들기(빈 비트맵을 만들 때도 DC가 필요하다.)
		image->mHdc = CreateCompatibleDC(hdc);  //새 DC 만들기(DC를 만들 때는 기반이 되는 DC가 있어야 한다.)

		//새로 만든 DC와 비트맵을 엮어주기 위한 작업(DC에 빈 비트맵 파일을 적용하고 DC가 만들어지면서 생성된 디폴트 비트맵은 메모리 해제를 시켜준다.)
		HBITMAP oldBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(oldBitmap);

		image->SetTextureType(eTextureType::Bmp);

		Resources::Insert(name + L"Image", image);  //혹시라도 이름이 겹치는 경우가 발생할 수 있기 때문에 key값에 Image라는 문자를 추가해준다.

		return image;
	}

	Texture::Texture() : Resource(enums::eResourceType::Texture), mbAlpha(false), mType(eTextureType::None), mImage(nullptr), mBitmap(nullptr)
		, mHdc(nullptr), mWidth(0), mHeight(0)
	{
		
	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

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

			if (info.bmBitsPixel == 32) {
				mbAlpha = true;
			}
			else if (info.bmBitsPixel == 24) {
				mbAlpha = false;
			}

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