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


class Duck
{
public:
	virtual void quack() = 0;
	virtual void fly() = 0;
};


class Turkey
{
public:
	virtual void gobble() = 0;
	virtual void fly() = 0;
};


class WildTurkey : public Turkey
{
public:
	void gobble()
	{
		cout << "gobble gobble" << endl;
	}

	void fly()
	{
		cout << "I'm flying a short distance" << endl;
	}
};


class TurkeyAdapter : public Duck
{
public:
	TurkeyAdapter(Turkey* turkey) : turkey(turkey) {}

	void quack()
	{
		turkey->gobble();
	}

	void fly()
	{
		for (int i=0; i<5; ++i)
			turkey->fly();
	}


private:
	Turkey* turkey;
};


int main()
{
	Turkey* turkey = new WildTurkey();
	Duck* turkeyAdapter = new TurkeyAdapter(turkey);

	turkeyAdapter->quack();
	turkeyAdapter->fly();

	delete turkey;
	delete turkeyAdapter;

	return 0;
}