#pragma once

namespace oep::math {
	//수학적인 정보나 연산을 모아놓을 헤더 파일
	//네임스페이스도 따로 수학 관련 내용을 모아놓는다는 의미로 oep네임스페이스 안에 math 네임스페이스를 추가

	//오브젝트의 위치 정보를 갖는 구조체
	struct Vector2
	{
		//많이 사용될 값을 따로 저장
		static Vector2 One;  //1.0f, 1.0f
		static Vector2 Zero;  //0.0f, 0.0f

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
	};
}
