#pragma once
#include "CommonInclude.h"
#include "oepBoxCollider2D.h"
#include "oepCircleCollider2D.h"

namespace oep {
	using namespace enums;

	//union�� ����ü��� ������ �����ϰ� �����ϸ� �����͸� ��� ����ϴ� �͵� �����ϰ� �ɰ��� ����ϴ� �͵� ������ �����̴�.
	//���� �� �ڼ��ϰ� �����ϸ� ����ü�� ����ü�� ���� ���������� ��� ��� ������ �ϳ��� �޸� ������ �����Ѵٴ� �������� �ִµ� �̴� ���ο� ����
	//Ÿ�� ���� ������ �� �� ������ ���� ��� �ÿ��� �ϳ��� ��� ������ ����� �� �ִ� ���̴�.
	//����ü�� ũ��� ��� ���� �� ���� ũ�Ⱑ ū ������ ũ��� �ƹ��� ���� Ÿ���� ������ �����ص� ũ��� Ŀ���� �ʱ� ������ �޸� ������ �������� ����Ѵ�.
	//��, ����ü�� �ϳ��� ���������� ������ �� �ְ� �ٸ� Ÿ���� ��� ������ �� ���� ����� �� �� ������ ũ�⸸ŭ�� �����͸� ������ ����ϴ� ���̴�.
	//�׷��� ������ ����ü�� �����͸� ����� ����� �� �ְ� �и��ؼ��� ����� �� �ִ� ������� �� �� �ִ�.
	union CollisionID {
		struct {  //�� ����ü�� �ϳ��� ��� �����̴�.
			//left�� right�� ���� ������Ʈ�� ID
			UINT32 left;
			UINT32 right;
		};

		//id�� left�� right�� ���� ������ ���� �� ���̰� �� �� �浹ü ���� �浹 ��Ȳ�� �����ϴ� ID�� ����� ���̴�.
		UINT64 id;
	};

	//�浹ü�� �浹 ���� �����ϴ� Ŭ����
	class CollisionManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

		static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable);
		static void LayerCollision(class Scene* scene, eLayerType left, eLayerType right);
		static void ColliderCollision(Collider* left, Collider* right);
		static bool Intersect(Collider* left, Collider* right);

	private:
		//��� �浹ü�� ��� üũ�� �� ���� ������ ��� ���������� ���̾� �� �浹 ���θ� ����� �浹 Ȯ��
		//�׸��� �� �浹 ���δ� 2���� �迭�� �̿��Ͽ� �����ϰ� ���
		//�̶� �迭 �� ��ҵ��� ��Ʈ ������ �ɰ��� ����� �� �ֵ��� ��Ʈ ������ Ȱ��
		//matrix�� ����̶�� ���̴�(��, ���̾� �� �浹 ���� ����̶�� ��)
		//bitset�� ���� ���ϰ� ��Ʈ�� Ȱ���� �迭 ������ �����ϵ��� �߰��� stl�� ���� �ϳ��� 1��Ʈ ũ���̱� ������ �̷� üũ�ƴ��� Ȯ�θ� �ϴ�
		//������ �迭���� �Ϳ��� ����ϱ� �����ϴ�.(�̰� �����ٸ� ��� ���ɼ��� Ȯ���ϱ� ���� ������ �ʿ����� ���ε� �� �۾��� �ٿ��־���.)
		//�Ʒ��� ���� ���� ���� 2���� �迭�� []�� ������� ������ 1���� �迭�� ���̴�.
		static std::bitset<(UINT)eLayerType::Max> mCollisionLayerMatrix[(UINT)eLayerType::Max];  

		//������Ʈ �� �浹 ������ üũ�ϱ� ���� bool ������ �ʿ��� ���̰� �̸� �����ϱ� ���� unordered_map�� �ϳ� ����
		static std::unordered_map<UINT64, bool> mCollisionMap;
	};
}
