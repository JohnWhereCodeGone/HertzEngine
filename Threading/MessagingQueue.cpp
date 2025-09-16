#include "MessagingQueue.h"



void MessagingQueue::Push(std::shared_ptr<Message> msg)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        this->queue.push(msg);
    }
    m_cond.notify_one();
}


std::shared_ptr<Message> MessagingQueue::PopBlock()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cond.wait(lock, [&] {return !queue.empty();}); //thread sleeps until the queue has a message.
    
    if (queue.empty())
    {
        return nullptr;
    }
    auto msg = queue.front();
    queue.pop();
    return msg;
}

std::shared_ptr<Message> MessagingQueue::Pop()
{
    //m_cond.wait(lock, [&] {return !queue.empty();}); //thread sleeps until the queue has a message.
    std::unique_lock<std::mutex> lock(m_mutex);

    if (queue.empty())
    {
        return nullptr;
    }
    auto msg = queue.front();
    queue.pop();
    return msg;
}

const std::queue<std::shared_ptr<Message>>& MessagingQueue::GetQueue()
{
        return queue;
}
