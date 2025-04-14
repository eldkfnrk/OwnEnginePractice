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

		//�� �̹����� ����� �Լ�(���� �Լ�ó�� ����ϵ��� static ����)
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
		bool mbAlpha;  //���� ä���� �ִ��� ������ Ȯ���ϴ� ����

		eTextureType mType;  

		Gdiplus::Image* mImage; 
		HBITMAP mBitmap; 
		HDC mHdc;  

		UINT mWidth;
		UINT mHeight;
	};
}
