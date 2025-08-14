#include "Component.h"
#include "../Objects/VirtualObject.h"

Component::Component()
{
	m_isAttached = false;
}

void Component::Attach(VirtualObject& obj)
{
	std::cout << "Base attach" << std::endl;
}
