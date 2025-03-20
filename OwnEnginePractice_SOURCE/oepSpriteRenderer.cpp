#include "oepSpriteRenderer.h"
#include "oepGameObject.h"
#include "oepTransform.h"

namespace oep {
	SpriteRenderer::SpriteRenderer()
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
		//������ ���� ������Ʈ�� �ϴ� ���� ������ SpriteRenderer ������Ʈ�� ���
		HBRUSH randomBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand()%255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, randomBrush);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Ellipse(hdc, tr->GetX(), tr->GetY(), 100 + tr->GetX(), 100 + tr->GetY());
		
		SelectObject(hdc, oldBrush);
		
		DeleteObject(randomBrush);  //�޸� ����
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}
}