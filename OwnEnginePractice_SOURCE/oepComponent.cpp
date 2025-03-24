#include "oepComponent.h"

namespace oep {
	Component::Component(enums::eComponentType type) : mOwner(nullptr), mType(type)
	{
	}

	void Component::Initialize()
	{
	}

	void Component::Update()
	{
	}

	void Component::LateUpdate()
	{
	}

	void Component::Render(HDC hdc)
	{
	}

	Component::~Component()
	{
	}
}