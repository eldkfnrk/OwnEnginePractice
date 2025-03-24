#pragma once

namespace oep::math {
	//�������� ������ ������ ��Ƴ��� ��� ����
	//���ӽ����̽��� ���� ���� ���� ������ ��Ƴ��´ٴ� �ǹ̷� oep���ӽ����̽� �ȿ� math ���ӽ����̽��� �߰�

	//������Ʈ�� ��ġ ������ ���� ����ü
	struct Vector2
	{
		//���� ���� ���� ���� ����
		static Vector2 One;  //1.0f, 1.0f
		static Vector2 Zero;  //0.0f, 0.0f

		float x;
		float y;

		Vector2() : x(0.0f), y(0.0f) {

		}

		Vector2(float x, float y) : x(x), y(y) {

		}

		//������ �����ε�
		Vector2 operator+(Vector2 other) {
			return Vector2(x + other.x, y + other.y);
		}

		Vector2 operator-(Vector2 other) {
			return Vector2(x - other.x, y - other.y);
		}

		Vector2 operator/(Vector2 other) {
			return Vector2(x / other.x, y / other.y);
		}

		Vector2 operator/(float value) {
			return Vector2(x / value, y / value);
		}
	};
}
