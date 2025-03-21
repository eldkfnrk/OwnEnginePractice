#include "oepSpriteRenderer.h"
#include "oepGameObject.h"
#include "oepTransform.h"

namespace oep {
	SpriteRenderer::SpriteRenderer() : mImage(nullptr), mWidth(0), mHeight(0)
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
		//HBRUSH randomBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand()%255));
		//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, randomBrush);

		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//Ellipse(hdc, tr->GetX(), tr->GetY(), 100 + tr->GetX(), 100 + tr->GetY());
		//
		//SelectObject(hdc, oldBrush);
		//
		//DeleteObject(randomBrush); 

		//���ݱ����� ȭ�鿡 ������ �׸��� ������ ������Ʈ�� ����Ͽ� ����Ͽ��µ� ������ ������Ʈ�� �̹��� ���ҽ��� ������ �ְ� �̸� ����� �� �ֵ��� ����
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		Gdiplus::Graphics graphics(hdc);  //�̹����� ȭ�鿡 �׸��� ���� dc����
		graphics.DrawImage(mImage, Gdiplus::Rect(pos.x, pos.y, mWidth, mHeight));  //ȭ�鿡 �̹����� �׸��� �Լ� ���(2��° ���ڷ� �̹����� ���·� ���⼱ �׸� ���¿� ������Ʈ ���� ��ǥ���� �ʺ�, ���� ũ��� �̹��� ���)
	}

	void SpriteRenderer::ImageLoad(const std::wstring& path)
	{
		mImage = Gdiplus::Image::FromFile(path.c_str());  //����� �̹��� ������ �����ͷ� ����
		mWidth = mImage->GetWidth();  //�̹����� �ʺ� �״�� �ʺ�� ���
		mHeight = mImage->GetHeight();  //�̹����� ���̸� �״�� �ʺ�� ���
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}
}