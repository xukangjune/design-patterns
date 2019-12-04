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

class ChocolateBoiler
{
public:
	static ChocolateBoiler* getInstance()
	{
		if (uniqueInstance == NULL)
		{
			cout << "there will be only excuted once" << endl;
			uniqueInstance = new ChocolateBoiler();
		}
		return uniqueInstance;
	}

	void fill()
	{
		if (this->empty)
		{
			this->empty = false;
			this->boiled = false;
			cout << "fill boiler with milk and chocolate" << endl;
		}
	}

	void drain()
	{
		if (!this->empty && !this->boiled)
		{
			cout << "have discharged the boiling milk and chocolate" << endl;
			this->empty = true;
		}
	}

	void boil()
	{
		if (!this->empty && !this->boiled)
		{
			cout << "the milk and chocolate is boiling " << endl;
			this->boiled = true;
		}
	}


private:
	bool empty;
	bool boiled;
	static ChocolateBoiler* uniqueInstance;

	ChocolateBoiler()
	{
		this->empty = true;
		this->boiled = false;
	}
};


ChocolateBoiler* ChocolateBoiler::uniqueInstance = NULL;
int main()
{
	ChocolateBoiler* instance = ChocolateBoiler::getInstance();
	instance->fill();
	instance->drain();
	instance->boil();

	ChocolateBoiler* instance_2 = ChocolateBoiler::getInstance();
	instance->fill();
	instance->drain();
	instance->boil();

	delete instance;
	delete instance_2;

	return 0;
}