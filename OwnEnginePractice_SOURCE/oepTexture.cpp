#include "oepTexture.h"
#include "oepApplication.h"

//�̷��� ���� ������ ���� ���� ����� �Ұ����ϴ�.
extern oep::Application application;  //�� ���Ͽ����� main �Լ��� ����� ���� ������ �𸣱� ������ extern Ű���带 ���� �� ���� ������ ������ �� ���Ͽ� �˷��ش�.


namespace oep::graphics {
	Texture::Texture() : Resource(enums::eResourceType::Texture), mType(eTextureType::None), mImage(nullptr), mBitmap(nullptr), mHdc(nullptr), mWidth(0), mHeight(0)
	{
		//�θ� Ŭ������ ����Ʈ ������ ���� ���� ������ �����ڰ� �ִٸ� �θ� �����ڸ� ���� ȣ�����־�� �ϴµ� �� ȣ���� ������ �ʱ�ȭ �κп��� �̷������ �ȴ�.(���� �κп��� �ص� �ȴ�.)
	}

	//void Texture::ImageLoad(const std::wstring& path)
	//{
	//	mImage = Gdiplus::Image::FromFile(path.c_str());  //�� �������� �̹��� ������ �츮 ���α׷��� �޸� ������ �÷��ش�.
	//	mWidth = mImage->GetWidth();
	//	mHeight = mImage->GetHeight();
	//}

	HRESULT Texture::Load(const std::wstring& path)
	{
		//����� Ȯ���ڸ��� ������ �ͼ� ����(Ȯ���ڸ��� ���� �� �̹��� ������ ������ �������� �� �� �ֱ� ������ �̸� �����;� �Ѵ�.)
		//substr �Լ��� ���ڿ��� �Ϻθ� �������� �Լ��̴�.
		//�׸��� find_last_of �Լ��� ���ڿ��� �� �ں��� ���ڷ� ���޹��� ���ڸ� ã�� �Լ��̴�.(������ ���ڰ� �� ���̵� �� �ڿ������� ã�Ƽ� ���� ���� ã�� ���ڿ��� �����.)
		//�׷��� path.substr(path.find_last_of(L".")); �� ���� ���ڿ�(path)�� �ں��� ���� "."�� ã�� �� �� ���ں��� ���ڿ� ������ �����´ٴ� �ǹ��̴�.
		//���⼭ +1�� ���� �ǹ̳� �ϸ� find_last_of �Լ��� ���� "."�� ã���� "." �ٷ� ���� ���ڸ� ã����� �ǹ��̴�.
		//��, path.find_last_of(L".") + 1 �� �� �ڿ������� ���� "."�� ã�� �� ������ �ٷ� �ڿ� �ִ� ���ڸ� ��ȯ�Ѵٴ� �ǹ��̴�.
		//�׷��� path.substr(path.find_last_of(L".") + 1); �� ��ο��� "." �ٷ� �� ���ں��� �������� Ȯ���ڸ��� ������ �� �ִ� ���̴�.
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		if (ext == L"bmp") {  //bmp�� ���
			mType = eTextureType::Bmp;

			//LoadImageW�� ��ο� �ִ� ��Ʈ�� ������ �̹����� �������� �Լ��̴�.
			//1��° ���ڴ� �ν��Ͻ��� �׳� nullptr�� �־��ָ� �ǰ� 2��° ���ڴ� ��е� �ڷ����� wchar_t�� ������ ��, ���ݱ��� wstring�� ������� �� �����δ� Wchar_t�� �迭��
			//������ ��ü�� ����� ���̱� ������ �ش� ��ü�� ����� ���� �迭�� �ּҸ� �־��ָ� �ȴ�. �׸��� 3��° ���ڴ� ������ �̹��� Ÿ���ε� �̴� ������ IMAGE_BITMAP�� �־��ش�.
			//4~5��° ���ڴ� ��𼭺��� ���������� �����ϴ� ������ �̹��� ���� ������ ���̱� ������ 0,0���� ���� ���������� 0�� �����Ѵ�. ������ ���ڴ� �׳� �̰Ŷ�� ��︸ ����.
			//�� �Լ��� ��ȯ���� HANDLE�̱� ������ ��Ʈ�� �ڷ����� �°� �� ��ȯ�� ���־�� �Ѵ�.
			//�̹����� �� �ε�Ǿ��ٸ� ������ ������������ �ε尡 �� �ƴٸ� ��, �ε尡 �����ߴٸ� �Լ��� nullptr�� ��ȯ�Ѵ�.
			//�̷��� ��Ʈ�� ����� ���������� png���Ϻ��� �ӵ��� �ణ ������.
			mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (mBitmap == nullptr) {
				return S_FALSE;  //false�� ���� ���ε� HRESULT���� ���� ��ȯ�ؾ� �ϱ� ������ S_FALSE�� ��ȯ
				//�� �ڷ����� S_OK�� S_FALSE��� ���� ���µ� S_OK�� 0, S_FALSE�� 1�� ������ �ִ�.(������ true, false�� �ݴ��̴�.)
			}

			BITMAP info = {};  //������ ��Ʈ���� ������ ������ ��ü

			//��Ʈ���� ������ ����
			//HBITMAP���� BITMAP�� ũ�⸸ŭ �����͸� �����ͼ� info�� �����Ϳ��ٰ� ����(�����͸� �������� ���̴� ���ο��� ���� �ٲ�� �ش� �������� ���� �ٲ�� ���� Ȱ���Ѵٴ� ���� �� �� �ִ�.)
			GetObject(mBitmap, sizeof(BITMAP), &info);

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			//��Ʈ���� �ݵ�� dc�� ¦�� �̷�� ������ ��Ʈ�� ������ŭ dc�� �־�� �Ѵ�.
			//�׷��� ��Ʈ�ʿ� �����ϴ� dc�� �ݵ�� �����ϰ� �����Ͽ��� �Ѵ�.
			HDC mainDC = application.GetHdc();

			//dc�� ����� ���ؼ� ���� dc�� �ʿ��ϱ� ������ �� ���α׷��� ���� dc�� �����ͼ� �� dc ����
			mHdc = CreateCompatibleDC(mainDC);  //�̷��� dc�� ����� �� dc �ȿ��� ����Ʈ ��Ʈ��(���Ͼ� ��ȭ��)�� ���� ���������.

			//����Ʈ ��Ʈ���� �ֱ� ������ �̸� ����� ������ ��Ʈ�ʰ� ��������־�� �Ѵ�.
			HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);  //SelectObject�� �ϸ� ������ ������ �ִ� ������Ʈ�� ����ش�.
			DeleteObject(oldBitmap);  //�̸� �޸� �󿡼� �������� ������ �޸� ���� �߻�. �׷��� �� ���Ŷ�� �ݵ�� ������� �Ѵ�.
		} 
		else if (ext == L"png") {  //png�� ���
			mType = eTextureType::Png;

			//png�� ��� �ܼ��ϰ� SpriteRenderer ������Ʈ���� ������ �̹����� �ε��ϴ� ��� �״�� �ε��ϸ� �ȴ�.
			mImage = Gdiplus::Image::FromFile(path.c_str());  //�� �������� �̹��� ������ �츮 ���α׷��� �޸� ������ �÷��ش�.

			if (mImage == nullptr) {
				return S_FALSE;
			}

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}
		
		return S_OK;  //�������� ������ �ε�Ǿ��ٸ� S_OK�� ��ȯ
	}

	Texture::~Texture()
	{
	}
}