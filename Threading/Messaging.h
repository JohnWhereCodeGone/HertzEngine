#pragma once
#include "iostream"
#include <mutex>

enum MessageType
{
	Default,
	LoadOBJ,
	LoadedResource
};

class Message
{


public:

	Message(const MessageType& type = MessageType::Default) : m_type(type) {};

	virtual ~Message() = default;
	MessageType m_type;
	virtual void QueuePop();

};

