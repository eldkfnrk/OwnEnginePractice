#pragma once
#include "oepResource.h"

namespace oep::graphics {  
	class Texture : public Resource
	{
	public:
		enum class eTextureType {  //�ؽ��� ������ ������ �����ϱ� ���� ������
			Png,  //png������ ���
			Bmp,  //bmp������ ���
			None,  //�ƹ��͵� �ƴ� ���
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
