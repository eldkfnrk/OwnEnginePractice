#include "oepTexture.h"
#include "oepApplication.h"
#include "oepResources.h"

extern oep::Application application;  

namespace oep::graphics {
	Texture* Texture::Create(const std::wstring& name, UINT width, UINT height) {
		Texture* image = Resources::Find<Texture>(name);  //Ȥ�� ������ �̸��� �̹��� ������ �ε�Ǿ� �ִ��� Ȯ���ϱ� ���� Find�� ���ش�.

		if (image) {  //������ �̸��� �̹��� ������ �ִٸ� �ش� �̹��� ���� ��ȯ
			return image;
		}

		image = new Texture();

		image->SetName(name);
		image->SetWidth(width);
		image->SetHeight(height);

		HDC hdc = application.GetHdc();
		HWND hwnd = application.GetHwnd();

		//�̹����� ����� ���� ��Ʈ�ʰ� DC ����
		//�ڵ带 �̿��Ͽ� ���� ��Ʈ���� ����� 24��Ʈ¥�� ��Ʈ���� ����(�׷��� AlphaBlend �Լ��δ� ����� �� �ǰ� TransParentBlt �Լ��� ����Ͽ� ����Ͽ��� �Ѵ�.)
		//���� ������ �������� ������ �ִϸ��̼��� ����� ������� ���ϴ� ��찡 �߻��� �� �ִ�.
		image->mBitmap = CreateCompatibleBitmap(hdc, width, height);  
		image->mHdc = CreateCompatibleDC(hdc);  

		//�ִϸ��̼� ���� �� �߻��ϴ� ��� ����� �����ϰ� �ϴ� �۾�(�ִϸ��̼��� ���� �� �翬�� ����� ������ �� �Ǳ⿡ �ʿ��� �۾�)
		//��Ʈ�� ���� �ִϸ��̼� �̹����� ���� ���̱� ������ �ִϸ��̼� �̹��� ���� ����� �Ǵ� ��Ʈ���� �����ϰ� ������־�� �Ѵ�.
		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		//�̹��� ũ�⺸�� �� Ŀ�������� �ʹ� ũ�� �ϸ� �� �Ǳ� ������ �̷��� ũ�⸦ ����
		Rectangle(hdc, -1, -1, image->GetWidth() + 1, image->GetHeight() + 1);

		//���� ���� DC�� ��Ʈ���� �����ֱ� ���� �۾�(DC�� �� ��Ʈ�� ������ �����ϰ� DC�� ��������鼭 ������ ����Ʈ ��Ʈ���� �޸� ������ �����ش�.)
		HBITMAP oldBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);

		SelectObject(hdc, oldBrush);
		
		DeleteObject(oldBitmap);

		image->SetTextureType(eTextureType::Bmp);

		Resources::Insert(name + L"Image", image);  //Ȥ�ö� �̸��� ��ġ�� ��찡 �߻��� �� �ֱ� ������ key���� Image��� ���ڸ� �߰����ش�.

		return image;
	}

	Texture::Texture() : Resource(enums::eResourceType::Texture), mbAlpha(false), mType(eTextureType::None), mImage(nullptr), mBitmap(nullptr)
		, mHdc(nullptr), mWidth(0), mHeight(0)
	{
		
	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

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