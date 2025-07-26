#pragma once
#include <cmath>

#define PI 3.141592f

namespace oep::math {
	static float ConvertDegree(float radian) {  //���� ���� ������ ��ȯ�ϴ� �Լ�
		//"���� = (���� / 180) * PI" ��� ������ �̿��Ͽ� ������ Ȱ���� ���� ���ϴ� �������� �ٲٸ� "���� = ���� * 180 / PI"�� �ȴ�.
		return radian * (180 / PI);
	}

	struct Vector2
	{
		static Vector2 Rotate(Vector2 vector, float degree) {  //ȣ������ ����� ������ ȸ��
			//���� = (���� / 180) * PI
			float radian = (degree / 180.0f) * PI;  //PI=180��, 2PI=360��

			vector.Normalize();

			//(a,b) ���͸� ���� A��ŭ ȸ����Ų ������ ��ǥ�� (a * cosA - b * sinA, a * sinA + b * cosA)�� �ȴ�.
			float x = cosf(radian) * vector.x - sinf(radian) * vector.y;
			float y = sinf(radian) * vector.x + cosf(radian) * vector.y;

			return Vector2(x, y);
		}

		static float Dot(Vector2& v1, Vector2& v2) {  //������ ����
			return v1.x * v2.x + v1.y * v2.y;
		}

		static float Cross(Vector2& v1, Vector2& v2) {  //������ ����
			return v1.x * v2.x - v1.y * v2.y;
		}

		static Vector2 One;  //1.0f, 1.0f
		static Vector2 Zero;  //0.0f, 0.0f

		//���� ���Ǵ� ����� ���õ� ���� ����
		static Vector2 Right;  //1.0f, 0.0f
		static Vector2 Left;  //-1.0f, 0.0f
		static Vector2 Up;  //0.0f, -1.0f
		static Vector2 Down;  //0.0f, 1.0f

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

		Vector2 operator*(Vector2 other) {
			return Vector2(x * other.x, y * other.y);
		}

		Vector2 operator*(float value) {
			return Vector2(x * value, y * value);
		}

		void operator+=(Vector2 other) {
			x += other.x;
			y += other.y;
		}

		bool operator==(Vector2 other) {
			if (x == other.x && y == other.y) {
				return true;
			}

			return false;
		}

		float Length() {  //������ ����
			//sqrtf - �������� ���ϴ� �Լ��� �Ű������� ������(��Ʈ)�� ��ȯ�Ѵ�.(sqrt - double��, sqrtf - float��, sqrtl - long double��)
			//�ﰢ���� ������ ���̸� ���� �� ���� ��쿡�� ��� ����
			return sqrtf(x * x + y * y);
		}

		Vector2 Normalize() {  //������ �Ϲ�ȭ - ������ ���̸� 1�� ����� �۾�(�� ��ǥ�� ������ ���̸� ������.)
			float len = Length();
			x /= len;
			y /= len;

			return *this;
		}
	};
}
