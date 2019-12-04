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


class GumballMachine;


//状态的基类，其中定义了每个状态中都必须实现的方法
class State
{
public:
	virtual void insertQuarter(GumballMachine* gumballMachine) = 0;
	virtual void ejectQuarter(GumballMachine* gumballMachine) = 0;
	virtual void turnCrank(GumballMachine* gumballMachine) = 0;
	virtual void dispense(GumballMachine* gumballMachine) = 0;
};


//糖果机类，其中有各种状态。而糖果机每次都只能在一个状态。通过状态的动作，选择转换的下一个状态
class GumballMachine
{
public:
	GumballMachine(int numberGumballs, 	State* soldOutState, State* noQuarterState, State* hasQuarterState, State* soldState) : 
	count(numberGumballs), soldOutState(soldOutState), noQuarterState(noQuarterState), hasQuarterState(hasQuarterState), soldState(soldState)
	{
		state = noQuarterState;
	}

	void insertQuarter()
	{
		state->insertQuarter(this);
		printState();
	}

	void ejectQuarter()
	{
		state->ejectQuarter(this);
		printState();
	}

	void turnCrank()
	{
		state->turnCrank(this);
		state->dispense(this);
		printState();
	}

	void setState(State* state)
	{
		this->state = state;
	}

	void releaseBall()
	{
		cout << "A gumball comes rolling out the slot..." << endl;
		if (count != 0)
			count--;
	}

	State* getHasQuarterState()
	{
		return hasQuarterState;
	}

	State* getNoQuarterState()
	{
		return noQuarterState;
	}

	State* getSoldOutState()
	{
		return soldOutState;
	}

	State* getSoldState()
	{
		return soldState;
	}

	int getCount()
	{
		return count;
	}

	void printState()
	{
		if (state == noQuarterState)
			cout << "----------The gumballMachine in noQuarterState..." << endl;
		else if (state == hasQuarterState)
			cout << "----------The gumballMachine in hasQuarterState..." << endl;
		else if (state == soldState)
			cout << "----------The gumballMachine in soldState..." << endl;
		else if (state == soldOutState)
			cout << "----------The gumballMachine in soldOutState..." << endl;
		else
			cout << "ERROR STATE" << endl;
		cout << endl;
	}

private:
	State* soldOutState;
	State* noQuarterState;
	State* hasQuarterState;
	State* soldState;

	State* state = soldOutState;
	int count = 0;
};


//NoQuarterState状态
class NoQuarterState : public State
{
public:
	void insertQuarter(GumballMachine* gumballMachine)
	{
		cout << "You insert a quarter..." << endl;
		gumballMachine->setState(gumballMachine->getHasQuarterState());
	}

	void ejectQuarter(GumballMachine* gumballMachine)
	{
		cout << "You haven't inserted a quarter..." << endl;
	}

	void turnCrank(GumballMachine* gumballMachine)
	{
		cout << "You turned, but there's no quarter..." << endl;
	}

	void dispense(GumballMachine* gumballMachine)
	{
		cout << "You need pay first..." << endl;
	}

private:
	GumballMachine* gumballMachine;
};


//HasQuarterState状态
class HasQuarterState : public State
{
public:
	void insertQuarter(GumballMachine* gumballMachine)
	{
		cout << "You can't insert another quarter..." << endl;
	}

	void ejectQuarter(GumballMachine* gumballMachine)
	{
		cout << "Quarter returned..." << endl;
		gumballMachine->setState(gumballMachine->getNoQuarterState());
	}

	void turnCrank(GumballMachine* gumballMachine)
	{
		cout << "You turned..." << endl;
		gumballMachine->setState(gumballMachine->getSoldState());
	}

	void dispense(GumballMachine* gumballMachine)
	{
		cout << "No gumballs dispensed..." << endl;
	}

private:
	GumballMachine* gumballMachine;
};


//SoldState状态
class SoldState : public State
{
public:
	void insertQuarter(GumballMachine* gumballMachine)
	{
		cout << "Please wait, we're already giving you a gumball..." << endl;
	}

	void ejectQuarter(GumballMachine* gumballMachine)
	{
		cout << "Sorry, you have already turned the crank..." << endl;
	}

	void turnCrank(GumballMachine* gumballMachine)
	{
		cout << "Turning twice doesn't get you another gumball..." << endl;

	}

	void dispense(GumballMachine* gumballMachine)
	{
		gumballMachine->releaseBall();
		if (gumballMachine->getCount() > 0)
			gumballMachine->setState(gumballMachine->getNoQuarterState());
		else
		{
			cout << "Oops, out of gumballs" << endl;
			gumballMachine->setState(gumballMachine->getSoldOutState());
		}
	}

private:
	GumballMachine* gumballMachine;
};


//SoldOutState状态
class SoldOutState : public State
{
public:
	void insertQuarter(GumballMachine* gumballMachine)
	{
		cout << "You can't insert a quarter, the machine is sold yet..." << endl;
	}

	void ejectQuarter(GumballMachine* gumballMachine)
	{
		cout << "You can't eject, you haven't insert a quarter..." << endl;
	}

	void turnCrank(GumballMachine* gumballMachine)
	{
		cout << "Sorry, there is no more gumballs..." << endl;
	}

	void dispense(GumballMachine* gumballMachine)
	{
		cout << "No gumballs dispensed..." << endl;
	}

private:
	GumballMachine* gumballMachine;
};



int main()
{
	State* soldOutState = new SoldOutState();
	State* noQuarterState = new NoQuarterState();
	State* hasQuarterState = new HasQuarterState();
	State* soldState = new SoldState();

	GumballMachine* gumballMachine = new GumballMachine(1, soldOutState, noQuarterState, hasQuarterState, soldState);
	gumballMachine->insertQuarter();
	gumballMachine->ejectQuarter();
	gumballMachine->insertQuarter();
	gumballMachine->turnCrank();

	delete soldOutState;
	delete noQuarterState;
	delete hasQuarterState;
	delete soldState;
	delete gumballMachine;

	return 0;
}