#include "oepSpriteRenderer.h"
#include "oepGameObject.h"
#include "oepTransform.h"
#include "oepTexture.h"
#include "oepRenderer.h"
#include "oepCamera.h"

namespace oep {
	SpriteRenderer::SpriteRenderer() : Component(enums::eComponentType::SpriteRenderer), mTexture(nullptr), mSize(math::Vector2::One)
	{
		
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
		if (mTexture == nullptr) { 
			assert(false);  
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();	
		Vector2 pos = tr->GetPosition();  //������Ʈ�� ��ġ ����
		float rotation = tr->GetRotation();  //������Ʈ�� ����
		Vector2 scale = tr->GetScale();  //������Ʈ�� ũ��

		pos = renderer::mainCamera->CalculatePosition(pos);  //ī�޶� �̵��� ��ŭ ������Ʈ�鵵 ��� �̵�

		if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp) {  //�̹��� ������ bmp�� ���
			//https://blog.naver.com/power2845/50147965306
			if (mTexture->IsAlpha()) {
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 225;  //0(transparent-����) ~ 255(Opaque-������) �� ������ ���� ����

				AlphaBlend(hdc, pos.x, pos.y
					, mTexture->GetWidth() * mSize.x * scale.x, mTexture->GetHeight() * mSize.y * scale.y, mTexture->GetHdc()
					, 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), func);
			}
			else {
				TransparentBlt(hdc, pos.x, pos.y, mTexture->GetWidth() * mSize.x * scale.x, mTexture->GetHeight() * mSize.y * scale.y
					, mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), RGB(255, 0, 255));
			}
		}
		else if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Png) {  //�̹��� ������ png�� ���
			//�ִϸ��̼��� ����ȭ�� �� �� �ְ� ���������� ��������Ʈ�������� ����ȭ�� �����ϵ��� ����
			Gdiplus::ImageAttributes imgAttributes = {};  //�̹����� �Ӽ��� �����ϴ� ����ü

			imgAttributes.SetColorKey(Gdiplus::Color(100, 100, 100), Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphics(hdc);  

			//�̹����� ������ŭ �������� �ϴ� ����
			graphics.TranslateTransform(pos.x, pos.y);  //ȸ���� �� �߽��� �Ǵ� ��ǥ ����
			graphics.RotateTransform(rotation);  //���ڷ� �������� ���� ������ ���� ����ŭ ȸ��
			graphics.TranslateTransform(-pos.x, -pos.y);

			//graphics.DrawImage(mTexture->GetImage(), Gdiplus::Rect(pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y));
			//������ ����ȭ�ϰ� ����� �� �ֵ��� ���� �ڵ带 ����
			//ȭ�鿡 ����ϴ� ������� �̹����� ����� �Բ� �����־� ȭ�鿡 ��½����ش�.(�ؽ����� ũ��� ��� ũ��� ����)
			graphics.DrawImage(mTexture->GetImage(), Gdiplus::Rect(pos.x, pos.y, mTexture->GetWidth() * mSize.x * scale.x, mTexture->GetHeight() * mSize.y * scale.y)
				, 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), Gdiplus::UnitPixel, nullptr);
		}
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}
}