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
		//기존에 게임 오브젝트가 하던 것을 이제는 SpriteRenderer 컴포넌트가 담당
		HBRUSH randomBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand()%255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, randomBrush);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Ellipse(hdc, tr->GetX(), tr->GetY(), 100 + tr->GetX(), 100 + tr->GetY());
		
		SelectObject(hdc, oldBrush);
		
		DeleteObject(randomBrush);  //메모리 삭제
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}
}