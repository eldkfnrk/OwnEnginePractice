#pragma once
#include <cmath>

#define PI 3.141592f

namespace oep::math {
	static float ConvertDegree(float radian) {  //라디안 값을 각도로 변환하는 함수
		//"라디안 = (각도 / 180) * PI" 라는 공식을 이용하여 라디안을 활용한 각도 구하는 공식으로 바꾸면 "각도 = 라디안 * 180 / PI"가 된다.
		return radian * (180 / PI);
	}

	struct Vector2
	{
		static Vector2 Rotate(Vector2 vector, float degree) {  //호도법을 사용한 벡터의 회전
			//라디안 = (각도 / 180) * PI
			float radian = (degree / 180.0f) * PI;  //PI=180도, 2PI=360도

			vector.Normalize();

			//(a,b) 벡터를 각도 A만큼 회전시킨 벡터의 좌표는 (a * cosA - b * sinA, a * sinA + b * cosA)이 된다.
			float x = cosf(radian) * vector.x - sinf(radian) * vector.y;
			float y = sinf(radian) * vector.x + cosf(radian) * vector.y;

			return Vector2(x, y);
		}

		static float Dot(Vector2& v1, Vector2& v2) {  //벡터의 내적
			return v1.x * v2.x + v1.y * v2.y;
		}

		static float Cross(Vector2& v1, Vector2& v2) {  //벡터의 외적
			return v1.x * v2.x - v1.y * v2.y;
		}

		static Vector2 One;  //1.0f, 1.0f
		static Vector2 Zero;  //0.0f, 0.0f

		//자주 사용되는 방향과 관련된 값을 저장
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

		//연산자 오버로딩
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

		float Length() {  //벡터의 길이
			//sqrtf - 제곱근을 구하는 함수로 매개변수의 제곱근(루트)를 반환한다.(sqrt - double형, sqrtf - float형, sqrtl - long double형)
			//삼각형의 빗변의 길이를 구할 떄 등의 경우에서 사용 가능
			return sqrtf(x * x + y * y);
		}

		Vector2 Normalize() {  //벡터의 일반화 - 벡터의 길이를 1로 만드는 작업(각 좌표에 벡터의 길이를 나눈다.)
			float len = Length();
			x /= len;
			y /= len;

			return *this;
		}
	};
}
