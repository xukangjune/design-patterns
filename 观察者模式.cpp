#include<iostream>
#include<vector>
#include<map>
#include<list>
#include<set>
#include<queue>
#include<string>
#include<stack>
#include<cmath>
#include<algorithm>

using namespace std;

class Observer
{
public:
	virtual void update(int) = 0;
};


class Subject
{
public:
	virtual void registerObserver(Observer*) = 0;
	virtual void removeObserver(Observer*) = 0;
	virtual void notifyObservers() = 0;
};


class Observer_1 : public Observer
{
public:
	Observer_1(Subject* subject) : m_subject(subject)
	{
		this->m_subject->registerObserver(this);
	}


	void update(int val)
	{
		cout << "new value:  " << pow(val, 2) << endl;
	}


private:
	Subject* m_subject;
};


class Observer_2 : public Observer
{
public:
	Observer_2(Subject* subject) : m_subject(subject)
	{
		this->m_subject->registerObserver(this);
	}


	void update(int val)
	{
		cout << "new value:  " << pow(val, 3) << endl;
	}


private:
	Subject* m_subject;
};


class subject : public Subject
{
private:
	vector<Observer*> ob_vec;
	int state;

public:
	void set_state(int val)
	{
		state = val;
	}


	void registerObserver(Observer* observer)
	{
		ob_vec.push_back(observer);
	}

	void removeObserver(Observer* observer)
	{
		for (auto it = ob_vec.begin(); it != ob_vec.end(); ++it)
		{
			if (*it == observer)
			{
				ob_vec.erase(it);
				break;
			}
		}
	}

	void notifyObservers()
	{
		for (auto it = ob_vec.begin(); it != ob_vec.end(); ++it)
		{
			(*it)->update(state);
		}
	}
};


int main()
{
	subject* real_subject = new subject();
	Observer_1*  real_observer_1 = new Observer_1(real_subject);
	Observer_2*  real_onserver_2 = new Observer_2(real_subject);

	real_subject->set_state(10);
	real_subject->notifyObservers();

	delete real_subject;
	delete real_observer_1;
	delete real_onserver_2;

	return 0;
}