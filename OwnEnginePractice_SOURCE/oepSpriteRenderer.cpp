#include "oepSpriteRenderer.h"
#include "oepGameObject.h"
#include "oepTransform.h"
#include "oepTexture.h"

namespace oep {
	SpriteRenderer::SpriteRenderer() : mTexture(nullptr), mSize(math::Vector2::One) /* mImage(nullptr), mWidth(0), mHeight(0)*/
	{
		//mSize�� 1.0f, 1.0f�� �ʱ� ���� �� ������ �ƹ� ���� ���� ������ 0.0f, 0.0f�� ���� ���� �ֱ� ������ �̹��� ����� �� �� ���̱� �����̴�.
	}

	void SpriteRenderer::Initialize()
	{
	}

	void SpriteRenderer::Update()
	{
	}

	void SpriteRenderer::LateUpdate()
	{
	}

	void SpriteRenderer::Render(HDC hdc)
	{
		if (mTexture == nullptr) {  //�ؽ�ó ������ �� �� ���(���⿡ �ɸ��� �ؽ�ó ������ �� �� ���̴� �ؽ�ó ������ Ȯ���ؾ� �Ѵ�.)
			assert(false);  //return;���� �Լ� ���Ḧ �ص� ������ �׷��� ����� �� ���� ������ �߻����� �ľ��� ��Ʊ� ������ assert�� ���
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		//�� ������ ������ �Ʒ����� ����
		//Gdiplus::Graphics graphics(hdc);
		//graphics.DrawImage(mTexture->mImage(, Gdiplus::Rect(pos.x, pos.y, mWidth, mHeight));

		if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp) {  //�̹��� ������ bmp�� ���
			//�� �Լ��� ��Ʈ���� ȭ�鿡 ����� �� ����ϴ� �Լ��� ���ڿ� ���� ��Ȯ�� ������ �Ʒ� ��ũ�� ��α׸� ���� �� �� �ִ�.
			//https://blog.naver.com/power2845/50147965306
			//bmp ������ ���� ���� ����. �̰� ���� �ǹ��̳� �ϸ� ��Ʈ�� �̹����� �ݵ�� ������ �־ �׳� ����ϸ� ������ ���� ��µȴٴ� �ǹ��̴�.
			//���� ��� �������� �ִٰ� �����غ��� �̶� �������� bmp �����̰� ������ ����ε� ������ ���ΰ� �׳� ����ߴ��ϸ� ������ �̹��� ������ ������ ���� ��µȴ�.
			//�׷��� ȭ�鿡 �������� ���;� �ϴµ� �ڿ� ��� ��浵 ���� ������ �Ǿ ���� �÷��̿� ������ �ְ� �ȴ�. �׷��� bmp ������ ����� �� �� ������ ����ȭ��Ű�� ����Ѵ�.
			//�׸��� �� �Լ��� ������ ���ڴ� bmp ���Ͽ��� ����ȭ��ų ���� �����ϴ� ������ �׷��� �ش� ������ ��� �� ��� ����ȭ�ȴ�.
			//�׷��� ���� bmp������ ������ ����� ���ҽ� �̹������� ������� �ʴ� ������ ������ ���´�.
			//�׷��� ���� ��Ʈ�� ������ ������ ������ ���ҽ� �̹����� �� ������� �ʴ� RGB(255, 0, 255) ����Ÿ ���� ���� ����.
			TransparentBlt(hdc, pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y
				, mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), RGB(255, 0, 255));
		}
		else if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Png) {  //�̹��� ������ png�� ���
			Gdiplus::Graphics graphics(hdc);  
			graphics.DrawImage(mTexture->GetImage(), Gdiplus::Rect(pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y));
		}
	}

	//void SpriteRenderer::ImageLoad(const std::wstring& path)
	//{
	//	mImage = Gdiplus::Image::FromFile(path.c_str());  //�� �������� �̹��� ������ �츮 ���α׷��� �޸� ������ �÷��ش�.
	//	mWidth = mImage->GetWidth();  
	//	mHeight = mImage->GetHeight(); 
	//}

	SpriteRenderer::~SpriteRenderer()
	{
	}
}