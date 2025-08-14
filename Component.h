#pragma once


class VirtualObject;


class Component
{
public:

	Component();

	virtual void Attach(VirtualObject& obj);
	virtual ~Component() = default;
	bool m_isAttached;


};

