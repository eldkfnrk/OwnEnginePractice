#pragma once

namespace oep::enums {
	enum class eLayerType {  //���̾�
		None,  //�⺻ Ÿ��
		BackGround,
		//Ground,
		//Tree,
		//Rock,
		Animal,
		Player,
		Particle,  //����Ʈ
		Max = 16,  //���̾�� �ʹ� ũ�� �������� �ʰ� ���ӿ� �°� �ʿ��� ��ŭ�� ����ϸ� �ȴ�.
	};

	enum class eResourceType {  //���ҽ��� ����
		Texture,  //�̹��� ����
		Audio,  //���� ����
		Animation,  //�ִϸ��̼�
		Prefab,  //���� ������Ʈ�� ������ �����͸� ����Ƽ���� �������̶� �Ѵ�.(�𸮾󿡼� �������Ʈ�� �Ѵ�.)
		End,
	};

	enum class eComponentType {  //������Ʈ�� ����
		//������Ʈ�� ������ �þ�� �þ ��ŭ �߰�(�̶� �߰��� ��ġ�� ���� ������ �˸°� ��ġ)
		Transform,
		Collider,
		Script,
		SpriteRenderer,
		Animator,
		Camera,
		End,
	};

	enum class eColliderType {
		Rect2D,
		Circle2D,
		End,
	};
}