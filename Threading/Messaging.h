#pragma once
#include "iostream"
#include <mutex>

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
	virtual void QueuePop();

};

