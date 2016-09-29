#include "Stack.h"

void Stack::push(Node val)
{
    st.push(val);
}

Node Stack::top()
{
    if (st.empty())
    {
        std::cerr << "top() Stack empty";
        return Node();
    }
    else
    {
        return st.top();
    }
}

Node Stack::pop()
{
    if (st.empty())
    {
        std::cerr << "pop() Stack empty";
        return Node();
    }
    else
    {
        Node ans = st.top();
        st.pop();
        return ans;
    }
}

bool Stack::empty()
{
    return st.empty();
}