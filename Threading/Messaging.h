#pragma once
#include "iostream"

enum MessageType
{
	Default,
	LoadOBJ,
};

class Message
{


public:
	virtual ~Message() = default;
	MessageType type;

};

