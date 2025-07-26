#include "oepBoxCollider2D.h"
#include "oepTransform.h"
#include "oepGameObject.h"
#include "oepRenderer.h"

namespace oep {
	BoxCollider2D::BoxCollider2D() 
		: Collider(enums::eColliderType::Rect2D)
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

		if(renderer::mainCamera) {
			pos = renderer::mainCamera->CalculatePosition(pos);
		}
		
		Vector2 offset = GetOffset();

		Vector2 size = GetSize();

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

		Rectangle(hdc, pos.x + offset.x, pos.y + offset.y, pos.x + offset.x + 100 * size.x, pos.y + offset.y + 100 * size.y);

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