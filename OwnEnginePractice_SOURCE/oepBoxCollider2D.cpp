#include "oepBoxCollider2D.h"
#include "oepTransform.h"
#include "oepGameObject.h"

namespace oep {
	BoxCollider2D::BoxCollider2D() 
		: Collider(), mSize(Vector2::Zero)
	{

	}

	void BoxCollider2D::Initialize() {

	}

	void BoxCollider2D::Update() {

	}

	void BoxCollider2D::LateUpdate() {

	}
	
	void BoxCollider2D::Render(HDC hdc) {
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		
		Vector2 offset = GetOffset();

		//Collider�� �����ϰ� ����
		//���� ���Ǵ� ������ StockObject�� �̸� ����Ǿ� �ִ�. �׸��� ���� �귯���� NULL_BRUSH��� �̸����� ����Ǿ� �ִ�.
		//���� ������Ʈ�� �����ϰ� ����
		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);  
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		//������ �׵θ��� �����ϰ� ����
		//HPEN transparentPen = (HPEN)GetStockObject(NULL_PEN);  //�� ���� ���� ���� NULL_PEN�̴�.
		//HPEN oldPen = (HPEN)SelectObject(hdc, transparentPen);

		//������ �׵θ��� ȸ�� ��濡�� �� �� ���̵��� �ʷϻ����� ����(����Ƽ���� �׵θ��� ���� �ʷϻ����� �Ͽ� �� ���̰� �� �Ѵ�.)
		HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));  //ù ��° ���ڴ� ���� ��Ÿ��, �� ��° ���ڴ� ���� ����(�ȼ� ����), �� ���� ���ڴ� ��
		HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);

		if (mSize == Vector2::Zero) {
			Rectangle(hdc, pos.x + offset.x, pos.y + offset.y, pos.x + offset.x + 100, pos.y + offset.y + 100);
		}
		else {
			Rectangle(hdc, pos.x + offset.x, pos.y + offset.y, pos.x + offset.x + mSize.x, pos.y + offset.y + mSize.y);
		}

		//�귯���� ����� dc���� ��� ������Ʈ���� ����� ���Ŀ��� �����·� ���� �� �޸� ������ ���־�� �Ѵ�.(�� �׷��� �߸��� ����� ������ ���� �ִ�.)
		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
		
		//StockObject�� dc�� ����Ǿ� �ִ� ���� ������ ����ϴ� ���̱� ������ ���� DeleteObject�� ���� �ʿ䰡 ����.
		//�׷��⿡ ���� ������ Object�鸸 Delete���ָ� �ȴ�.
		DeleteObject(greenPen);
	}

	BoxCollider2D::~BoxCollider2D() {

	}
}