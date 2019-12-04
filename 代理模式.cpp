#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<string>
#include<stack>
#include<cmath>
#include<algorithm>

using namespace std;


class Subject
{
public:
    virtual void request() = 0;
};


class RealSubject : public Subject
{
public:
    void request()
    {
        cout << "I'm real subject..." << endl;
    }
};


class Proxy : public Subject
{
public:
    void request()
    {
        if (realSubject == NULL)
            realSubject = new RealSubject();
        realSubject->request();
    }

    ~Proxy()
    {
        delete realSubject;
    }

private:
    Subject* realSubject;
};



int main()
{
    Subject* proxy = new Proxy();
    proxy->request();

    delete proxy;

    return 0;
}