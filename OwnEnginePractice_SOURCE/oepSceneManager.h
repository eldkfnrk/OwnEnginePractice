#pragma once
#include "oepScene.h"

namespace oep {
	class SceneManager
	{
	public:
		template <typename T>
		static Scene* CreateScene(const std::wstring& name) { 
			T* scene = new T();
		
			scene->SetName(name);  //�̸� ����
			mActiveScene = scene;  
			scene->Initialize();  //���� �ʱ�ȭ
			
			mScenes.insert(std::make_pair(name, scene));

			return scene;
		}

		static Scene* LoadScene(const std::wstring& name);

		static Scene* GetActiveScene() {
			return mActiveScene;
		}

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

		static void Release();  //�� Ŭ������ ��ü�� ������ �ʰ� ���� �Լ�ó�� ����� �� �ֵ��� �����߱� ������ ���� �Ҹ��ڰ� ��� ���� �޸� ������ �� �Լ� ����

	private:
		static std::map<std::wstring, Scene*> mScenes;  

		static Scene* mActiveScene;
	};

	//�츮�� ���� �� Ŭ������ ������� �������� ����� ���ε� ĸ��ȭ��ų ���� ĸ��ȭ��Ű�� ���� ���� ������ ���� ��ü�� �����ؼ� ����� ������ ���� �ʴ�.

	//�̱����̶�� ������ �ִ�.
	//�̱����� ��ü ������ Ŭ���� �ȿ��� �����ϱ� ������ ���α׷����� ��ü�� �� �ϳ��� ���� �� �ְ� �Ѵ�. �׸��� �װ��� Ŭ���� ���ο��� �Ʒ��� ���� static���� �����Ѵ�.
	//�׸��� ��ü�� �ϳ��� ���� �� �ֵ��� ������ �Ҹ��ڸ� private ����� �����Ͽ� ��ü ������ �����Ѵ�. �̷��� �ϸ� ��ü�� �� �ϳ��� �ǰ� �̸� ����ϵ��� �����ϴ� ���� �̱����̴�.
	//�׷��� �������δ� �Ҹ��� ȣ���� �Ұ����ϴ� ���� �޸� ������ ���� �ϴ� ���� �Ұ����ϴ�. �׷��� �����ڵ��� ��� ���δ� ���� ���̷� ������ ������ ������ ���Ѵ�� ������� �����ϸ� �ȴ�.
	//static SceneManager sceneManager;

	//�̱����� �ڵ带 �ۼ��ϴµ� ������ �ִ� ��ſ� �޸𸮸� ������� ��Ʈ���� �� ���� �츮�� ���� Ŭ������ �츮 ������� �޸� �Ҵ� ������ �� �� ������ �̱����� ������ ����.
	//�� ��� ��� �޸� ���� ���� ������ ��ȣ�ϴ� ����� ����ϸ� �Ǵ� ���̴�.
}