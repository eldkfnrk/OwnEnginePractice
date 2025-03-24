#pragma once

namespace oep::enums {
	enum class eLayerType {  //���̾�
		None,  //�⺻ Ÿ��
		BackGround,
		//�ʿ信 ���� ���̾ �߰����ָ� �ȴ�.
		//Ground,
		//Tree,
		//Rock,
		//Character,
		Player,
		Max = 16,  //���̾�� �ʹ� ũ�� �������� �ʰ� ���ӿ� �°� �ʿ��� ��ŭ�� ����ϸ� �ȴ�.
	};

	enum class eResourceType {  //���ҽ�
		//���ҽ� ���� ���������� �ʿ信 ���� �˸°� Ÿ���� �߰����ָ� �ȴ�.
		Texture,  //�̹��� ���� ������ �ؽ��ķ� ���
		Audio,  //���� ���� ������ ����� Ŭ������ ���
		Prefab,  //������ ������ �� ���
		End,
	};
}