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

		//Collider를 투명하게 설정
		//많이 사용되는 색들은 StockObject에 미리 저장되어 있다. 그리고 투명 브러쉬는 NULL_BRUSH라는 이름으로 저장되어 있다.
		//도형 오브젝트를 투명하게 설정
		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);  
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		//도형의 테두리를 투명하게 설정
		//HPEN transparentPen = (HPEN)GetStockObject(NULL_PEN);  //펜 또한 투명 펜은 NULL_PEN이다.
		//HPEN oldPen = (HPEN)SelectObject(hdc, transparentPen);

		//도형의 테두리가 회색 배경에서 더 잘 보이도록 초록색으로 설정(유니티에서 테두리는 보통 초록색으로 하여 잘 보이게 끔 한다.)
		HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));  //첫 번째 인자는 선의 스타일, 두 번째 인자는 선의 굵기(픽셀 단위), 세 번쨰 인자는 색
		HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);

		if (mSize == Vector2::Zero) {
			Rectangle(hdc, pos.x + offset.x, pos.y + offset.y, pos.x + offset.x + 100, pos.y + offset.y + 100);
		}
		else {
			Rectangle(hdc, pos.x + offset.x, pos.y + offset.y, pos.x + offset.x + mSize.x, pos.y + offset.y + mSize.y);
		}

		//브러쉬를 비롯한 dc관련 모든 오브젝트들은 사용한 이후에는 원상태로 돌린 후 메모리 삭제를 해주어야 한다.(안 그러면 잘못된 결과를 도출할 수도 있다.)
		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
		
		//StockObject는 dc에 내장되어 있는 것을 가져와 사용하는 것이기 때문에 따로 DeleteObject를 해줄 필요가 없다.
		//그렇기에 새로 생성한 Object들만 Delete해주면 된다.
		DeleteObject(greenPen);
	}

	BoxCollider2D::~BoxCollider2D() {

	}
}