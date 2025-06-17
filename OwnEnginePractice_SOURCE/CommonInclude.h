#pragma once

//이 헤더 파일은 자주 사용할 헤더 파일들을 모아놓고 어느 파일에서든 가져다가 쓸 수 있도록 하기 위한 파일이다.

#include <Windows.h>
#include <assert.h>  //assert 함수를 사용하기 위한 헤더 파일 추가

#include <vector>
#include <algorithm>  //for_each문 사용을 위한 헤더 파일 추가
#include <string>  //wstring을 사용하기 위한 헤더 파일 추가
#include <map>  //map(트리)를 사용하기 위한 헤더 파일 추가
#include <bitset>  //비트 연산을 조금 더 편히 이용할 수 있도록 추가된 stl
#include <functional>  //함수 포인터를 보다 쉽게 사용하기 위해 정의된 클래스를 사용하기 위한 헤더 파일 추가(함수 포인터 관련 라이브러리)
#include <filesystem>  //파일 시스템을 사용하기 위한 헤더 파일 추가

#include "oepMath.h"  //수학적인 정보나 연산을 사용하기 위한 파일 추가

//아래의 헤더 파일들과 라이브러리들은 GDI의 기능 추가를 위한 것들로 대략 이런 것들이 있다라고 알고 넘어가면 좋다.
#include <mmsystem.h>  //색과 브금을 넣는 기능을 하는 파일 추가
#include <dinput.h>  //다이렉트 인풋을 위한 파일 추가(다이렉트 인풋이란 키보드, 마우스, 게임 패드 등 여러 기기의 입력을 사용할 수 있는 인터페이스이다.)

//후에 리소스 출력을 위한 라이브러리 추가
#pragma comment(lib,"Msimg32.lib");  //GDI 컴포넌트 추가(후에 비트맵을 출력할 때 배경 투명화 등을 할 때 사용하기 위한 라이브러리)
#pragma comment(lib,"winmm.lib");  //후에 사운드를 출력하기 위한 라이브러리 추가

//png 파일을 불러오기 위한 헤더 파일과 해당 라이브러리를 링크시켜 준다.
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib");  //명시적 라이브러리 링크 방법(프로젝트에서 속성에 들어가 라이브러리를 추가할 필요없이 라이브러리 추가를 프로그램 파일 안에서 코드로 추가 할 수 있는 방법)

#include "oepEnums.h"  //열거형을 모아놓은 헤더 파일

#include <time.h>
#include <math.h>  //수학 관련 함수들을 사용하기 위한 헤더 파일