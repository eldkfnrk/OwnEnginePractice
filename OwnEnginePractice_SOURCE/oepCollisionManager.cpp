#include "oepCollisionManager.h"
#include "oepScene.h"
#include "oepSceneManager.h"
#include "oepGameObject.h"
#include "oepCollider.h"

namespace oep {
	std::bitset<(UINT)eLayerType::Max> CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};

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

	}
}