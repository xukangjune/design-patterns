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


class Beverage
{
public:
	string description = "Unknown Beverage";

	virtual double cost() = 0;

	string getDescription()
	{
		return this->description;
	}
};


class Espresso : public Beverage
{
public:
	Espresso()
	{
		this->description = "Espresso";
	}

	double cost()
	{
		return 1.99;
	}
};

class HouseBlend : public Beverage
{
public:
	HouseBlend()
	{
		this->description = "HouseBlend";
	}

	double cost()
	{
		return 0.89;
	}
};


class DarkRoast : public Beverage
{
public:
	DarkRoast()
	{
		this->description = "DarkRoast";
	}

	double cost()
	{
		return 0.99;
	}
};



class Mocha : public Beverage
{
public:
	Mocha(Beverage* beverage)
	{
		this->beverage = beverage;
		this->description = this->beverage->getDescription() + ", Mocha";
	}


	double cost()
	{
		return this->beverage->cost() + 0.20;
	}

private:
	Beverage* beverage;
};


class Soy : public Beverage
{
public:
	Soy(Beverage* beverage)
	{
		this->beverage = beverage;
		this->description = this->beverage->getDescription() + ", Soy";
	}

	double cost()
	{
		return this->beverage->cost() + 0.15;
	}

private:
	Beverage* beverage;
};


class Whip : public Beverage
{
public:
	Whip(Beverage* beverage)
	{
		this->beverage = beverage;
		this->description = this->beverage->getDescription() + ", Whip";
	}

	double cost()
	{
		return this->beverage->cost() + 0.10;
	}

private:
	Beverage* beverage;
};



int main()
{
	Beverage* beverage = new Espresso();
	cout << beverage->getDescription() << " $" << beverage->cost() << endl;

	Beverage* beverage_2 = new DarkRoast();
	beverage_2 = new Mocha(beverage_2);
	beverage_2 = new Mocha(beverage_2);
	beverage_2 = new Whip(beverage_2);
	cout << beverage_2->getDescription() << " $" << beverage_2->cost() << endl;

	Beverage* beverage_3 = new HouseBlend();
	beverage_3 = new Soy(beverage_3);
	beverage_3 = new Mocha(beverage_3);
	beverage_3 = new Whip(beverage_3);
	cout << beverage_3->getDescription() << " $" << beverage_3->cost() << endl;

	delete beverage;
	delete beverage_2;
	delete beverage_3;

	return 0;
}