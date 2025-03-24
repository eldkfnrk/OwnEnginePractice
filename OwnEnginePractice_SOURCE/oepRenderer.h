#pragma once
#include "oepCamera.h"

//renderer와 관련된 것을 모아놓을 파일

namespace oep::renderer {
	extern Camera* mainCamera;  //cpp파일에서 전역으로 선언한 변수가 있음을 알려 이 파일을 참조하는 모든 파일에서 접근이 가능하도록 extern 사용
}