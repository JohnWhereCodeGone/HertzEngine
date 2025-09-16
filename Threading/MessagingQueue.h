#pragma once
#include "Messaging.h"
#include "ObjMessage.h"
#include <queue>
#include <memory>
#include <mutex>


//use pop-block for worker thread, as it'll sleep in the background.
// use pop to cehc

class MessagingQueue
{
public:
	
	const std::queue<std::shared_ptr<Message>> &GetQueue();

	void Push(std::shared_ptr<Message> msg);


	std::shared_ptr<Message> PopBlock();
	std::shared_ptr<Message> Pop();
	

private:
	
	std::queue<std::shared_ptr<Message>> queue;
	std::mutex m_mutex;
	std::condition_variable m_cond;
};

