#include "Queue.h"

void Queue::push(Node val)
{
    q.push(val);
}

Node Queue::top()
{
    if (q.empty())
    {
        std::cerr << "top() Queue empty\n";
        return Node();
    }
    else
    {
        return q.front();
    }
}

Node Queue::pop()
{
    if (q.empty())
    {
        std::cerr << "pop() Queue empty\n";
        return Node();
    }
    else
    {
        Node ans = q.front();
        q.pop();
        return ans;
    }
}

bool Queue::empty()
{
    return q.empty();
}