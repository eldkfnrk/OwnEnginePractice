#include "oepCollisionManager.h"
#include "oepScene.h"
#include "oepSceneManager.h"
#include "oepGameObject.h"
#include "oepCollider.h"
#include "oepTransform.h"

namespace oep {
	std::bitset<(UINT)eLayerType::Max> CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};
	std::unordered_map<UINT64, bool> CollisionManager::mCollisionMap = {};

	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();  //���� �����ϰ� �ִ� ���� �浹 ���θ� Ȯ���ϴ� ���̱� ������ ���� ���� ���� ���� ������ �´�.
		//matrix�� ��ȸ�Ͽ� true�� ��츸 �浹 ���� �Ǵ��� �ϵ��� �Ѵ�
		for (UINT row = 0; row < (UINT)eLayerType::Max; row++) {
			for (UINT col = 0; col < (UINT)eLayerType::Max; col++) {
				if (mCollisionLayerMatrix[row][col] == true) {
					//��� ���� ��� ���̾� ������Ʈ ���� �浹 ���θ� üũ�ϱ� ���� �̿� ���� ���ڸ� �����Ѵ�.
					LayerCollision(scene, (eLayerType)row, (eLayerType)col);
				}
			}
		}
	}

	void CollisionManager::LateUpdate()
	{
	}

	void CollisionManager::Render(HDC hdc)
	{
	}

	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		//left�� right��� �̸����� ���̾� Ÿ���� �Ű������� �޴� ������ �Ʒ����� �����ϰڴ�.
		//3x3 ũ���� 2���� �迭�� �ִٰ� ������ ����. �׷��� �迭�� �Ʒ��� �������� �ȴ�.
		//  1  2  3
		//1
		//2
		//3
		//���� ���� ����� �迭���� 1���� 3���� �浹�Ѵٰ� �ϸ� 1�� 3���� üũ�� �ǰ� 3�� 1���� üũ�� �Ǵµ� �̴� ��������� ���� �浹�Ѵٴ� ���� �ǹ��Ѵ�.
		//�׷��� ���ʸ� üũ�� ���ָ� �Ǳ� ������ �� ���̾� �� ���� ���̾� �ʿ��ٰ��� ǥ�����ֱ�� ����Ͽ��� ����ϱ� ���� left�� right�� �޾Ƽ� ���� ����
		//������ ū ���� ���� ����Ͽ� �ش� ��Ҹ� üũ�� �ϴ� ����� �����ϱ� ���ؼ��̴�.(�̷��� �ϴ� ������ �ǹ̾��� �޸� ���� ������ �ʱ� �����̴�.)
		//�̷��� �Ʒ��� ���� 3�� 1���� �޸𸮸� ������� ���� �� �ְ� üũ�� Ȯ���� �� �ִ�.
		//  1  2  3                        1  2  3
		//1 x  x  o                      1 x  x  o
		//2 x  x  x         --->         2    x  x
		//3 o  x  x                      3       x
		int row = 0;  //��
		int col = 0;  //��

		if (left <= right) {
			row = (UINT)left;
			col = (UINT)right;
		}
		else {
			row = (UINT)right;
			col = (UINT)left;
		}

		mCollisionLayerMatrix[row][col] = enable;  //�ش� ���ҿ� true�� false�� ����
	}

	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		const std::vector<GameObject*>& lefts = scene->GetLayer(left)->GetGameObjects();
		const std::vector<GameObject*>& rights = scene->GetLayer(right)->GetGameObjects();

		//�� ���̾� ���� ��� ������Ʈ�� �˻�
		for (GameObject* left : lefts) {
			//���� ������Ʈ�� ���°� false��� ���� ȭ�鿡 �� ���̰� �س��Ҵٰų� ����� �����̶�� ������ �浹 �˻縦 �� �ʿ䰡 ������ �Ѿ��.
			if (left->IsActive() == false) {  
				continue;
			}

			Collider* leftCollider = left->GetComponent<Collider>();

			//���� ������Ʈ�� Collider ������Ʈ�� ���ٸ� �� ������Ʈ�� �浹ü�� �ƴϱ� ������ �浹 �˻縦 �� �ʿ䰡 ������ �Ѿ��.
			if (leftCollider == nullptr) {
				continue;
			}

			for (GameObject* right : rights) {
				//left�� ���������� right�� ���� ���� ������ �Ѿ�� �Ѵ�.
				if (right->IsActive() == false) {
					continue;
				}

				Collider* rightCollider = right->GetComponent<Collider>();

				if (rightCollider == nullptr) {
					continue;
				}

				//������ ���̾�� �浹�� üũ�ϴ� ��� ���� ���̾��� �ٸ� ������Ʈ���� üũ�� �ؾ������� ���̾ ��� ��ȸ�� �ϴٺ��� �ᱹ
				//�ڱ��ڽų��� �浹 üũ�� �ϴ� ������ ���� �Ǵµ� �� ���� �翬�� üũ�� �� �ʿ䰡 ���� ������ �Ѿ��.
				if (left == right) {
					continue;
				}

				//�� �浹ü�� �浹�ϴ��� üũ
				ColliderCollision(leftCollider, rightCollider);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		//�浹 üũ ����
		//�� �浹ü�� ID�� Ȯ���ؼ� CollisionID���� ����
		CollisionID id = {};  //�� �������� �� �浹ü �� �浹 ��Ȳ�� ������ ID��
		id.left = left->GetID();
		id.right = right->GetID();

		//�ش� ID�� �浹ü ������ �˻�
		//�ֳ��ϸ�, ���� �浹ü �� �浹 ��Ȳ ������ ���ٸ� �浹 ������ �������־�� �ϱ� �����̴�.
		//unordered_map�� �ش� ������ �ִ��� Ȯ���ϱ� ���� ������ �� Ű���� ���� ������ �ִٸ� second ���� ���ٸ� end()�� ������ ���̴�.
		auto iter = mCollisionMap.find(id.id);  
		if (iter == mCollisionMap.end()) {
			mCollisionMap.insert(std::make_pair(id.id, false));  //�浹�� ���� �� ���´� �ƴϱ� ������ false�� �־ ���� �� �������ش�.
			iter = mCollisionMap.find(id.id);
		}

		//�浹 üũ
		if (Intersect(left, right)) {  //�浹������ true �ƴϸ� false
			//�浹 ���� üũ
			if (iter->second == false) {  //���� �����ӱ����� �浹���� �ʾҴ� ����(���� �浹 ���¸� �ǹ�)
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
			else {  //�浹 ���� ���¸� �ǹ�
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else {
			//�浹 ���� üũ
			if (iter->second == true) {  //���� �����ӱ����� ��� �浹 ���̾��� ����(�浹 ���¿��� ������� �ǹ�)
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				iter->second = false;
			}
		}
	}

	//�� �浹ü �� �浹�� �ϴ����� ���� ���� ����� ǥ���ϱ� ���� �Լ�
	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		//�浹ü���� �浹�ϰ� �ִ��� ���θ� üũ
		//�̶� �簢�� �浹ü �� �浹 ������ AABB��� �ϴ� ���簢�������� �浹 üũ�� ���ִ� �˰����� ���
		//AABB�� Axis-Aligned Bounding Box�� ���Ӹ��� ���� ������ ������ �ڽ��� �����ϸ� �ȴ�. �̴� �ڽ��� �̷�� ��� �簢���� ����� ��ġ�Ѵٴ� �ǹ̷�
		//ȸ���� ���� �簢���� ���� ȸ�������� ������ ũ��� ���ϰ� �Ѵ�. ũ�� ��ȭ�� ��ӵǱ� ������ ū �δ��� �ƴ����� ���� �� �δ��� �� ���� �ִ�.
		//�� ����� �浹 üũ ����� x���� ������ ���غ��� y���� ������ ���ؼ� ��ġ�� �浹 ������ ���� ����̴�. �� �� �����ϱ� ���� ǥ�����ڸ� �簢���� 
		//������ �������� �� �簢���� ������ x�Ÿ��� ���ϰ� �� x�Ÿ��� �� �簢���� x�� ���� 1/2 ���̸� ��ģ ���� ���ؼ� x�Ÿ��� ��� �浹�� �ƴϰ� ���ų� ª���� �浹��
		//�����Ǵ� ���̴�. y�൵ ���������� ���ؼ� x�� �񱳿� y�� �� �� �� �ϳ��� �浹 ������ ���� �浹 ó���� �ϴ� ���̴�.
		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		//�� �簢���� ������ ��ġ ����
		Vector2 leftPos = leftTr->GetPosition() + left->GetOffset();
		Vector2 rightPos = rightTr->GetPosition() + right->GetOffset(); 

		//size�� 1,1�� ��� �⺻ ũ�Ⱑ 100�ȼ��̴�.
		Vector2 leftSize = left->GetSize() * 100.0f;
		Vector2 rightSize = right->GetSize() * 100.0f;

		enums::eColliderType leftType = left->GetColliderType();
		enums::eColliderType rightType = right->GetColliderType();

		//AABB����(fabs()�� �ε��Ҽ��� �μ��� ���밪�� �����ϴ� �Լ� -> ��, �Ǽ��� ���밪�� ��ȯ�ϴ� �Լ�)
		//���簢���� ���簢���� �浹ü �浹 �˻�
		if (leftType == enums::eColliderType::Rect2D && rightType == enums::eColliderType::Rect2D) {
			if (fabs(leftPos.x - rightPos.x) <= fabs(leftSize.x / 2.0f + rightSize.x / 2.0f) 
				&& fabs(leftPos.y - rightPos.y) <= fabs(leftSize.y / 2.0f + rightSize.y / 2.0f)) {
				return true;
			}
		}

		//���� ���� �浹ü �浹 �˻�
		//���� �浹 �˻�� �� ���� ���� ���� �Ÿ��� �� ���� �������� ������ �˻��Ѵ�.(��(shape)�� �Ȱ����� �� ����� ��Ȯ������ ������ ���� ���� ����̴�.)
		if (leftType == enums::eColliderType::Circle2D && rightType == enums::eColliderType::Circle2D) {
			//�� ���� ���� ��ġ�� ã�Ƽ� ����
			Vector2 leftCirclePos = leftPos + (leftSize / 2.0f);
			Vector2 rightCirclePos = rightPos + (rightSize / 2.0f);

			float distance = (leftCirclePos - rightCirclePos).Length();
			if (distance <= (leftSize.x / 2.0f + rightSize.x / 2.0f)) {  //���� ���� �� �Ÿ��� �� ���� �������� ���� ��
				return true;
			}
		}

		//���� �簢���� �浹ü �浹 �˻�
		//�� ��쿡�� ���ݱ����ʹ� ��¦ �ٸ� ����� ����Ͽ��� �Ѵ�. �簢���� �״�� ����ϴ� ���� �ƴ϶� �����¿�� ���� ��������ŭ Ű�� ������ �簢��
		if ((leftType == enums::eColliderType::Circle2D && rightType == enums::eColliderType::Rect2D)
			|| (leftType == enums::eColliderType::Rect2D && rightType == enums::eColliderType::Circle2D)) {
			Vector2 rectPos;
			Vector2 circlePos;
			Vector2 rectSize;
			Vector2 circleSize;

			if (leftType == enums::eColliderType::Rect2D) {
				rectPos = leftPos;  
				circlePos = rightPos + (rightSize / 2.0f);  //���� ����
				rectSize = leftSize;
				circleSize = rightSize;
			}
			else {
				rectPos = rightPos;  
				circlePos = leftPos + (leftSize / 2.0f);  //���� ����
				rectSize = rightSize;
				circleSize = leftSize;
			}

			//���� �簢���� �浹�� ���� ��������ŭ �簢���� ũ�⸦ Ű��� ���� �߽��� �� �簢�� �ȿ� �� �ִ����� �ΰ� �浹�� �����Ѵ�.
			//�׷��� ���������� �� ���������� ���� ������ ���־�� �ϴµ� �� ������ ������ �αٿ����� ���� ������ �ȿ� �� �־ �����δ� ����
			//���� ��찡 �ֱ� �����̴�. �׷��� �������� ���� �������� �Ÿ��� ����ϴ� ������� ���� ������ ���־�� �Ѵ�.
			//�׷��� ����� �� ������ �� �����̴�. �װ��� ���� ������ �簢���� ���� ��������ŭ Ȯ���� �簢�� �ȿ� �ִ����� üũ�ϴ� �Ͱ� 
			//�� �������� ���� ������ �Ÿ��� ���������� ������ üũ�ϴ� ���̴�.
			float radius = circleSize.x / 2.0f;  //���� ������
			Vector2 leftTop;
			Vector2 leftBottom;
			Vector2 rightTop;
			Vector2 rightBottom;
			
			leftTop = rectPos;

			leftBottom.x = rectPos.x;
			rightTop.x = rectPos.x + rectSize.x;
			rightBottom.x = rectPos.x + rectSize.x;
			
			leftBottom.y = rectPos.y + rectSize.y;
			rightTop.y = rectPos.y;
			rightBottom.y = rectPos.y + rectSize.y;

			float leftTopDistance = (circlePos - leftTop).Length();
			float leftBottomDistance = (circlePos - leftBottom).Length();
			float rightTopDistance = (circlePos - rightTop).Length();
			float rightBottomDistance = (circlePos - rightBottom).Length();

			if (radius >= leftTopDistance ||
				radius >= leftBottomDistance ||
				radius >= rightTopDistance ||
				radius >= rightBottomDistance) {
				//�������� ���� �߽� ���� �Ÿ��� ���� ���������� ������ Ȯ���Ͽ� ������ true�� ��ȯ���ش�.
				return true;
			}

			if ((circlePos.x >= leftTop.x - radius
				&& circlePos.x <= rightTop.x + radius) &&
				(circlePos.y >= leftTop.y - radius
				&& circlePos.y <= rightBottom.y + radius)) {
				//���� ��������ŭ Ȯ���� �簢�� �ȿ� ���� ������ �ִ��� Ȯ���Ͽ� �ȿ� ������ true�� ��ȯ���ش�.
				return true;
			}
		}

		return false;
	}
}