#pragma once
//CommonInclude ��� ����ó�� �η� ���Ǵ� ���ϵ��� ���� #include�Ǵ� ���� �ߺ��� �Ǵ� ��찡 ������ #pragma once ��ɾ� ���п� �Ű��� ���� �ʾƵ� �ȴ�.
//�׷��� ���� �ð����� ������ �� ���� �־ ���� �ð� ���� ���� �ߺ��� ã�� ����� ���̴�.
#include "CommonInclude.h"  
#include "oepGameObject.h"

namespace oep {
	class Application
	{
	public:
		Application();  

		void Initialize(HWND hwnd);  
		void Run();  
		void Update();  
		void LateUpdate();  
		void Render();  

		~Application();  //�Ҹ���

	private:
		HWND mHwnd;  
		HDC mHdc;  

		//float mSpeed;

		//����(������Ʈ)�� ��ǥ
		//float mX;
		//float mY;

		GameObject mPlayer;  //���� ������ �����Ͽ� ������ ���� ������Ʈ
	};
}
