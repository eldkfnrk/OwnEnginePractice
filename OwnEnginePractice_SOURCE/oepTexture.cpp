#include "oepTexture.h"
#include "oepApplication.h"

extern oep::Application application;  //extern - ���α׷��� ����� ���� ������ �� ������ �𸣴� ��� ���� ������ ������ �˷��ְ� �� ������ ����� �� �ְ� ���ִ� Ű����


namespace oep::graphics {
	Texture::Texture() : Resource(enums::eResourceType::Texture), mType(eTextureType::None), mImage(nullptr), mBitmap(nullptr), mHdc(nullptr), mWidth(0), mHeight(0)
	{
		
	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		//Gdiplus�� ���� Gdi���� ����� �߰��ؼ� �ٷ��� ���ߴ� ���ϵ��� �ٷ� �� �ְ� �ٲ��־��ٰ� �����Ͽ��µ� �׷��� Gdiplus�� �ӵ��� ���� Gdi���� ������.
		//�׷��ٸ� �ִϸ��̼��� �ʿ��� �÷��̾ ���� ������Ʈ ���� ��Ʈ���� �̿��ϴ°� API������ ���� �� �����ϴ�.
		//�̰��� GPU�� ����ϴ� ���̺귯�� DirectX�� ����� ��쿣 �Ű� ���� �ʾƵ� ������ �׷� �� ������� �ʴ� ���� ����� API ���������� �����ؾ� �Ѵ�.
		if (ext == L"bmp") {  //bmp�� ���
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
		else if (ext == L"png") {  //png�� ���
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