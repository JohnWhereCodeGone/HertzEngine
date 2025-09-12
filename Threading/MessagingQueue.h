#pragma once
#include "Messaging.h"
#include "ObjMessage.h"
#include <queue>
#include <memory>
#include <mutex>

class MessagingQueue
{
public:
	
	const std::queue<std::shared_ptr<Message>> &GetQueue();

	void Push(std::shared_ptr<Message> msg);


	std::shared_ptr<Message> PopTest();
	

private:
	
	std::queue<std::shared_ptr<Message>> queue;
	std::mutex m_mutex;
	std::condition_variable m_cond;
};

