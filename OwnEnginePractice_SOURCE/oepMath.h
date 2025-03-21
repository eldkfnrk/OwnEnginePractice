#pragma once

namespace oep::math {
	//�������� ������ ������ ��Ƴ��� ��� ����
	//���ӽ����̽��� ���� ���� ���� ������ ��Ƴ��´ٴ� �ǹ̷� oep���ӽ����̽� �ȿ� math ���ӽ����̽��� �߰�

	//������Ʈ�� ��ġ ������ ���� ����ü
	struct Vector2
	{
		float x;
		float y;

		Vector2() : x(0.0f), y(0.0f) {

		}

		Vector2(float x, float y) : x(x), y(y) {

		}
	};
}
