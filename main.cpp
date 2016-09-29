#include <bits/stdc++.h>
#include "Node.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;

Stack HelpStack;
Queue MyQueue;

void removespaces()
{
    while (cin.peek() == ' ') cin.get();
}

long long get_priority(string s)
{
    if (s == "(") return 0;
    else if (s == "+" || s == "-") return 1;
    else if (s == "*" || s == "/") return 2;
    else if (s == "^") return 3;
    else if (s == "(-)" || s == "(+)") return 4;
    return -1;
}

void read()
{
    bool isstart = true;
    bool isoperation = false;
    long long curpos = 0;
    while (cin.peek() != '\n' && !cin.eof())
    {
        curpos++;
        removespaces();
        if (isstart)
        {
            // унарная операция или число или скобка или функция
            if (cin.peek() == '(')
            {
                cin.get();
                HelpStack.push(Node("("));
            }
            else if (cin.peek() == '+' || cin.peek() == '-')
            {
                if (cin.peek() == '+')
                    HelpStack.push(Node("(+)"));
                else if (cin.peek() == '-')
                    HelpStack.push(Node("(-)"));
                cin.get();
            }
            else if (isdigit(cin.peek()))
            {
                long double val = 1;
                if (!(cin >> val))
                {
                    cerr << "Error at" << curpos << " elem(1st case read number)\n";
                }
                MyQueue.push(Node(val));
                isstart = false;
                isoperation = true;
            }
            else
            {
                cerr << "Error at " << curpos << " elem(1st case)\n";
            }
        }
        else if (isoperation)
        {
            // операция, либо закрывающая скобка и операция
            string nxt = "";
            nxt.push_back(cin.peek());
            if (get_priority(nxt) != -1)
            {
                cin.get();
                if (nxt == "^")// right-associate
                {
                    while (!HelpStack.empty() && get_priority(HelpStack.top().name) > get_priority(nxt))
                    {
                        MyQueue.push(HelpStack.pop());
                    }
                    HelpStack.push(Node(nxt));
                }
                else
                {
                    while (!HelpStack.empty() && get_priority(HelpStack.top().name) >= get_priority(nxt))
                    {
                        MyQueue.push(HelpStack.pop());
                    }
                    HelpStack.push(Node(nxt));
                }
                isoperation = false;
            }
            else if (nxt == ")")
            {
                cin.get();
                bool tmpflag = false;
                while (!HelpStack.empty())
                {
                    if (HelpStack.top().name == "(")
                    {
                        tmpflag = true;
                        HelpStack.pop();
                        break;
                    }
                    else
                    {
                        MyQueue.push(Node(HelpStack.pop()));
                    }
                }
                if (!tmpflag)
                {
                    cerr << "Error, don't find ')' \n";
                }
            }
            else
            {
                cerr << "Error at " << curpos << " elem(2nd case)\n";
            }
        }
        else
        {
            // число или скобка или функция
            if (cin.peek() == '(')
            {
                HelpStack.push(Node("("));
                isstart = true;
                cin.get();
            }
            else if (isdigit(cin.peek()))
            {
                long double val = 1;
                if (!(cin >> val))
                {
                    cerr << "Error at" << curpos << " elem(3rd case read number)\n";
                }
                MyQueue.push(Node(val));
                isoperation = true;
            }
            else
            {
                cerr << "Error at " << curpos << " elem(3rd case)\n";
            }
        }
        removespaces();
        if (cin.peek() == '\n' || cin.eof())
        {
            bool tmpflag = false;
            while (!HelpStack.empty())
            {
                if (HelpStack.top().name == "(")
                {
                    tmpflag = true;
                    HelpStack.pop();
                    break;
                }
                else
                {
                    MyQueue.push(Node(HelpStack.pop()));
                }
            }
            if (!tmpflag)
            {
                cerr << "Error, don't find at end ')' \n";
            }
            break;
        }
    }
}

void dumpqueue()
{
    Queue tmp = MyQueue;
    cerr << "Queue dump: ";
    while (!tmp.empty())
    {
        if (tmp.top().name == "Noname")
        {
            cerr << tmp.pop().val << ", ";
        }
        else
        {
            cerr << tmp.pop().name << ", ";
        }
    }
    cerr << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    HelpStack.push(Node("("));
    read();
    dumpqueue();
    return 0;
}