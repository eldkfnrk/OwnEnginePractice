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
		Vector2 pos = tr->GetPosition();

		pos = renderer::mainCamera->CalculatePosition(pos);  //ī�޶� �̵��� ��ŭ ������Ʈ�鵵 ��� �̵�

		if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp) {  //�̹��� ������ bmp�� ���
			//https://blog.naver.com/power2845/50147965306
			TransparentBlt(hdc, pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y
				, mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), RGB(255, 0, 255));
		}
		else if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Png) {  //�̹��� ������ png�� ���
			Gdiplus::Graphics graphics(hdc);  
			graphics.DrawImage(mTexture->GetImage(), Gdiplus::Rect(pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y));
		}
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}
}