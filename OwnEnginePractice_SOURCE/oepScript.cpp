#include "oepScript.h"
#include "oepCollider.h"

namespace oep {
	Script::Script() : Component(enums::eComponentType::Script)
	{
	}

	void Script::Initialize()
	{
	}

	void Script::Update()
	{
	}

	void Script::LateUpdate()
	{
	}

	void Script::Render(HDC hdc)
	{
	}

	void Script::OnCollisionEnter(Collider* other)
	{

	}

	void Script::OnCollisionStay(Collider* other)
	{

	}

	void Script::OnCollisionExit(Collider* other)
	{

	}

	Script::~Script()
	{
	}
}