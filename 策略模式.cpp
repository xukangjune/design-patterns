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

class QuackBehavior
{
public:
	virtual void quack() = 0;
};

class Duck
{
public:
	QuackBehavior* quackBehavior;

	void performFly()
	{
		quackBehavior->quack();
	}

	void setQuackBehavior(QuackBehavior* newQuackBehavior)
	{
		quackBehavior = newQuackBehavior;
	}
};



class Quack : public QuackBehavior
{
public:
	void quack()
	{
		cout << "Quack..." << endl;
	}
};

class Squeak : public QuackBehavior
{
public:
	void quack()
	{
		cout << "Squeak..." << endl;
	}
};



class MallardDuck : public Duck
{
public:
	MallardDuck()
	{
		cout << "I'm mallard duck" << endl;
		quackBehavior = new Quack();
	}
};


int main()
{
	Duck* mallard = new MallardDuck();
	mallard->performFly();

	QuackBehavior* newQuackBehavior = new Squeak();
	mallard->setQuackBehavior(newQuackBehavior);

	mallard->performFly();

	delete mallard;
	delete newQuackBehavior;

	return 0;
}