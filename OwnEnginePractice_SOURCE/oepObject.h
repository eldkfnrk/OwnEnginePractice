#pragma once
#include "oepLayer.h"
#include "oepGameObject.h"
#include "oepScene.h"
#include "oepSceneManager.h"
#include "oepTransform.h"

namespace oep::object {
	//���ݱ����� ���α׷��� ������Ʈ�� ���� ������ ������Ʈ�� ������ �־�� �ϴ� ������Ʈ���� ������ �߰����־���.
	//���� ������ �ڵ�� ������Ʈ�� �����ϴ� ���� �ƴ϶� �Լ��� �ϳ� ���� �̸� ȣ���ϴ� ������ �˾Ƽ� ������Ʈ�� ������ �� �ֵ��� �����Ѵ�.
	//�̶� �⺻������ ������ �ִ� ������Ʈ�� ���� �ʱ�ȭ ���ִ� �͵� ���� �� ������ �Լ� ȣ�� �ϳ��� ������Ʈ ������ �⺻������ �ִ� ������Ʈ�� �� �������� �� �� �־� �ڵ带 �����ϰ� ���� �� �ִ�.
	//�� �Լ��� ���� ���� �� ���� �����ϰ� ���� ������Ʈ�� ������ �� �ֱ� ������ ������ ������ ����Ƽ���� ������ �̸��� �Լ��� ����Ͽ� ������Ʈ�� �����ϵ��� �ϰ� �ִ�.

	//�׷��� ���ؼ��� �Լ��� ��� ������Ʈ�� ������ �� �־�� �ϱ� ������ ���ø� �Լ��� �Լ��� ����� �ȴ�.
	//�̶� static���� ����� ������ ���� �Լ��ν� ���� ������ �����Ӱ� �Լ��� ȣ���� �� �ֵ��� �ϱ� ���ؼ��̴�.
	template <typename T>
	static T* Instantiate(enums::eLayerType type) {  //������Ʈ�� ���̾ �޾Ƽ� �ش� ���̾ �߰�
		T* gameObj = new T();
		Scene* activeScene = SceneManager::GetActiveScene();  //���� ��� ���� ������Ʈ������ ���ڸ� ���� �ʿ���� ���� �����Ǵ� �������� Ȱ��ȭ�� ���� �ش� ������ �����ϰ� �̸� ������ �ȴ�.
		Layer* layer = activeScene->GetLayer(type);

		//��ġ ���� ����x -> 0,0���� ����
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(0.0f, 0.0f));

		layer->AddGameObject(gameObj);
		
		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, math::Vector2 position) {  //������Ʈ�� ��ġ�� �����ϸ鼭 �߰��� �� �ֵ��� �������̵�
		T* gameObj = new T();
		//���� ������Ʈ�� �߰��Ǵ� �ñ�� ������Ʈ�� �ҼӵǴ� ���� Ȱ��ȭ�Ǵ� �ñ��̱� ������ ���� � ������ ������Ʈ�� �߰��ϴ��� ������ �ʿ���� 
		//���� Ȱ��ȭ�� ���� �������� �ڿ������� �ش� ������ ������Ʈ�� ������ �� �ֱ� ������ ���� Ȱ��ȭ�� ���� �������� ���̴�.
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);

		//��ġ ���� ����o -> �ش� ��ġ ������ ����
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(position);

		layer->AddGameObject(gameObj);

		return gameObj;
	}
}