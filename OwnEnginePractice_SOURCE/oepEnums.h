#pragma once

//�� ��� ������ ����� ���������� �ϳ��� ���Ϸ� ��Ƽ� �����ϱ� ���� ����
//�����ΰ� �ʿ������ �����ϴ� cpp������ ����.

namespace oep::enums {
	enum class eLayerType {  //���̾�
		None,  //�⺻ Ÿ��
		BackGround,
		Ground,
		Tree,
		Rock,
		//Character,
		Player,
		Max = 16,  //���̾�� �ʹ� ũ�� �������� �ʰ� ���ӿ� �°� �ʿ��� ��ŭ�� ����ϸ� �ȴ�.
	};
}