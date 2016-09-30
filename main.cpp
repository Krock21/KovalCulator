#include <bits/stdc++.h>
#include "Node.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;

Stack HelpStack;
Queue MyQueue;
stack<long long> braces;
stack<long long> commas;
map<string, long double> vars;

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
    else if (s == "(-)" || s == "(+)") return 3;
    else if (s == "log" || s == "sin" || s == "cos") return 4;
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
        if (cin.peek() == ',')
        {
            if (!isoperation)
            {
                cerr << "operation before ','" << endl;
                return;
            }
            while (!HelpStack.empty() && HelpStack.top().name != "(")
            {
                MyQueue.push(HelpStack.pop());
            }
            cin.get();
            commas.top()++;
            isstart = true;
        }
        else if (isstart)
        {
            // унарная операция или число или скобка или функция
            if (cin.peek() == '(')
            {
                braces.push(0);
                commas.push(0);
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
                    cerr << "'" << (char) cin.peek() << "', ";
                    cerr << "Error at" << curpos << " elem(1st case read number)\n";
                    return;
                }
                MyQueue.push(Node(val));
                isstart = false;
                isoperation = true;
            }
            else if (isalpha(cin.peek()))
            {
                string s = "";
                char c;
                while (isalpha(cin.peek()))
                {
                    c = char(cin.get());
                    s.push_back(c);
                }
                if (s == "log" || s == "sin" || s == "cos")
                {
                    HelpStack.push(Node(s));
                    removespaces();
                    isoperation = false;
                    if (cin.peek() != '(')
                    {
                        cerr << "Error at " << curpos << " elem(logsincos case)\n";
                        return;
                    }
                    else
                    {
                        cin.get();
                        HelpStack.push(Node("("));
                    }
                    if (s == "log")
                    {
                        braces.push(1LL);
                        commas.push(0);
                    }
                    else
                    {
                        braces.push(0LL);
                        commas.push(0);
                    }
                }
                else
                {
                    MyQueue.push(Node(s));
                    isstart = false;
                    isoperation = true;
                }
            }
            else
            {
                cerr << "'" << (char) cin.peek() << "', ";
                cerr << "Error at " << curpos << " elem(1st case)\n";
                return;
            }
        }
        else if (isoperation)
        {
            // операция, либо закрывающая скобка и операция
            string nxt = "";
            nxt.push_back(char(cin.peek()));
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
                    isstart = true;
                }
                else
                {
                    while (!HelpStack.empty() && get_priority(HelpStack.top().name) >= get_priority(nxt))
                    {
                        MyQueue.push(HelpStack.pop());
                    }
                    HelpStack.push(Node(nxt));
                    isstart = true;
                }
                isoperation = false;
            }
            else if (nxt == ")")
            {
                cin.get();
                if (braces.size() <= 1)
                {
                    cerr << "Error braces, bad balance" << endl;
                    return;
                }
                if (commas.top() != braces.top())
                {
                    cerr << "Error comma, have " << commas.top() << ", need " << braces.top() << endl;
                    return;
                }
                commas.pop();
                braces.pop();
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
                    cerr << "'" << (char) cin.peek() << "', ";
                    cerr << "Error, don't find ')' \n";
                    return;
                }
            }
            else
            {
                cerr << "'" << (char) cin.peek() << "', ";
                cerr << "Error at " << curpos << " elem(2nd case)\n";
                return;
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
                    cerr << "'" << (char) cin.peek() << "', ";
                    cerr << "Error at" << curpos << " elem(3rd case read number)\n";
                    return;
                }
                MyQueue.push(Node(val));
                isoperation = true;
            }
            else if (isalpha(cin.peek()))
            {
                string s = "";
                char c;
                while (isalpha(cin.peek()))
                {
                    c = char(cin.get());
                    s.push_back(c);
                }
                if (s == "log" || s == "sin" || s == "cos")
                {
                    HelpStack.push(Node(s));
                    removespaces();
                    isoperation = false;
                    if (cin.peek() != '(')
                    {
                        cerr << "Error at " << curpos << " elem(logsincos case)\n";
                        return;
                    }
                    else
                    {
                        cin.get();
                        HelpStack.push(Node("("));
                    }
                    if (s == "log")
                    {
                        braces.push(1LL);
                        commas.push(0LL);
                    }
                    else
                    {
                        braces.push(0LL);
                        commas.push(0LL);
                    }
                }
                else
                {
                    MyQueue.push(Node(s));
                    isstart = false;
                    isoperation = true;
                }
            }
            else
            {
                cerr << "'" << (char) cin.peek() << "', ";
                cerr << "Error at " << curpos << " elem(3rd case)\n";
                return;
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
                cerr << "'" << (char) cin.peek() << "', ";
                cerr << "Error, don't find at end ')' \n";
                return;
            }
            if (!HelpStack.empty())
            {
                cerr << "Stack not empty \n";
                return;
            }
            break;
        }
    }
}

void dumpqueue()
{
    Queue tmp = MyQueue;
    cout << "Queue dump: ";
    while (!tmp.empty())
    {
        if (tmp.top().name == "Noname")
        {
            cout << tmp.pop().val << ", ";
        }
        else
        {
            cout << tmp.pop().name << ", ";
        }
    }
    cout << endl;
}

long long poschitaybistro()
{
    stack<long double> st;
    while (!MyQueue.empty())
    {
        Node cur = MyQueue.pop();
        if (cur.name != "Noname")
        {
            if (cur.name == "(+)")
            {
                if (st.empty())
                {
                    cerr << "poschitay error stack\n";
                    return 0;
                }
            }
            else if (cur.name == "(-)")
            {
                if (st.empty())
                {
                    cerr << "poschitay error stack\n";
                    return 0;
                }
                long double tmp = st.top();
                st.pop();
                st.push(-tmp);
            }
            else if (cur.name == "+")
            {
                long double t1, t2;
                if (st.size() <= 1)
                {
                    cerr << "poschitay error stack\n";
                    return 0;
                }
                t2 = st.top();
                st.pop();
                t1 = st.top();
                st.pop();
                st.push(t1 + t2);
            }
            else if (cur.name == "-")
            {
                long double t1, t2;
                if (st.size() <= 1)
                {
                    cerr << "poschitay error stack\n";
                    return 0;
                }
                t2 = st.top();
                st.pop();
                t1 = st.top();
                st.pop();
                st.push(t1 - t2);
            }
            else if (cur.name == "*")
            {
                long double t1, t2;
                if (st.size() <= 1)
                {
                    cerr << "poschitay error stack\n";
                    return 0;
                }
                t2 = st.top();
                st.pop();
                t1 = st.top();
                st.pop();
                st.push(t1 * t2);
            }
            else if (cur.name == "/")
            {
                long double t1, t2;
                if (st.size() <= 1)
                {
                    cerr << "poschitay error stack\n";
                    return 0;
                }
                t2 = st.top();
                st.pop();
                t1 = st.top();
                st.pop();
                st.push(t1 / t2);
            }
            else if (cur.name == "^")
            {
                long double t1, t2;
                if (st.size() <= 1)
                {
                    cerr << "poschitay error stack\n";
                    return 0;
                }
                t2 = st.top();
                st.pop();
                t1 = st.top();
                st.pop();
                st.push(pow(t1, t2));
            }
            else if (cur.name == "log")
            {
                long double t1, t2;
                if (st.size() <= 1)
                {
                    cerr << "poschitay error stack\n";
                    return 0;
                }
                t2 = st.top();
                st.pop();
                t1 = st.top();
                st.pop();
                st.push(log(t1) / log(t2));
            }
            else if (cur.name == "sin")
            {
                long double t;
                if (st.size() < 1)
                {
                    cerr << "poschitay error stack\n";
                    return 0;
                }
                t = st.top();
                st.pop();
                st.push(sin(t));
            }
            else if (cur.name == "cos")
            {
                long double t;
                if (st.size() < 1)
                {
                    cerr << "poschitay error stack\n";
                    return 0;
                }
                t = st.top();
                st.pop();
                st.push(cos(t));
            }
            else if (cur.name == "e")
            {
                st.push(exp(1));
            }
            else if (cur.name == "p")
            {
                st.push(acos(-1));
            }
            else
            {
                if (vars.find(cur.name) == vars.end())
                {
                    cout << "Write " << cur.name << ": ";
                    long double val;
                    cin >> val;
                    vars[cur.name] = val;
                }
                st.push(vars[cur.name]);
            }
        }
        else
        {
            st.push(cur.val);
        }
    }
    cout << "poschital': ";

    while (!st.empty())
    {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
    return 0;
}

int main()
{
    //freopen("input.txt", "r", stdin);
    while (!cin.eof())
    {
        HelpStack = Stack();
        MyQueue = Queue();
        HelpStack.push(Node("("));
        braces.push(0);
        commas.push(0);
        read();
        dumpqueue();
        poschitaybistro();
        string ost;
        getline(cin, ost);
    }
    return 0;
}