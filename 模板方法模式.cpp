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


class CaffeineBeverage
{
public:
	void prepareRecipe()
	{
		boilWater();
		brew();
		pourIncup();

		if (hook())
		{
			addCondiments();
		}
	}

	virtual void brew() = 0;
	virtual void addCondiments() = 0;

	virtual bool hook() 
	{
		return true;
	}

private:
	void boilWater()
	{
		cout << "Boilling water" << endl;
	}

	void pourIncup()
	{
		cout << "Pouring into cup" << endl;
	}
};


class Tea : public CaffeineBeverage
{
	void brew()
	{
		cout << "Steeping the tea" << endl;
	}

	void addCondiments()
	{
		cout << "Adding Lemon" << endl;
	}
};


class Coffee : public CaffeineBeverage
{
	void brew()
	{
		cout << "Dripping Coffee through filter" << endl;
	}

	void addCondiments()
	{
		cout << "Adding Sugar and Milk" << endl;
	}

	bool hook()
	{
		string answer = "";
		cout << "Would you like milk and sugar with your coffee (y/n) ?" << endl;
		cin >> answer;

		if (answer == "y")
			return true;
		return false;
	}
};


int main()
{
	Tea* tea = new Tea();
	Coffee* coffee = new Coffee();

	cout << "\nMaking tea... " << endl;
	tea->prepareRecipe();

	cout << "\nMaking coffee..." << endl;
	coffee->prepareRecipe();

	delete tea;
	delete coffee;

	return 0;
}