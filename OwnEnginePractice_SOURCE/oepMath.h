#pragma once

namespace oep::math {
	//수학적인 정보나 연산을 모아놓을 헤더 파일
	//네임스페이스도 따로 수학 관련 내용을 모아놓는다는 의미로 oep네임스페이스 안에 math 네임스페이스를 추가

	//오브젝트의 위치 정보를 갖는 구조체
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
