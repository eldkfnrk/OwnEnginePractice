#pragma once
#include "oepResource.h"

namespace oep::graphics {  //�׷��Ƚ��� ���õ� �͵��� �и��ϱ� ���� oep���ӽ����̽� �ȿ� graphics���ӽ����̽� �ϳ��� �� �߰� 
	class Texture : public Resource
	{
	public:
		//oepEnums ���Ͽ� �߰����� �ʴ� ������ �� Ŭ���������� ����� ���̱� �����̴�. oepEnums�� ���� ���Ͽ��� �����ؼ� ����� �� �ֵ��� �� ������ ������ ����ϴ�.
		enum class eTextureType {  //�ؽ��� ������ ������ �����ϱ� ���� ������
			Png,  //png������ ���
			Bmp,  //bmp������ ���
			None,  //�ƹ��͵� �ƴ� ���
		};

		Texture();

		//�� �Լ��� �θ� Ŭ������ ���� ���� �Լ��̱� ������ �ݵ�� ������ ���־�� �Ѵ�.
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
		eTextureType mType;  //�ؽ��� Ÿ���� ���� ����

		Gdiplus::Image* mImage;  //png�� jpg���� �̹��� ������ ������ �� �ִ� ����
		HBITMAP mBitmap;  //���ҽ� �߿��� bmp(��Ʈ��)���ϵ鵵 �ֱ� ������ �� ���ϵ��� ������ �� �ִ� ����
		HDC mHdc;  //��Ʈ�ʰ� ����Ǽ� ����� dc�� ���� ������ �־�� �Ѵ�.(��Ʈ���� dc�� ¦�� �̷��߸� ����� �� �ִ�.)
		//���� �˰����� ��Ʈ���� ����ϴ� ���� ������ ��ٷӴ�. �׷��� �߰��� ���� Gdiplus(Gdi�� ��� �߰�)�̰� ��Ʈ�� ���� �׳� Gdi�� �Ѵ�.

		UINT mWidth;
		UINT mHeight;
	};
}
