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


class Pizza
{
public:
	string name;
	string dough;
	string sauce;
	string toppings;

	void prepare()
	{
		cout << "Preparing " << name << endl;
		cout << "Tossing dough... " << dough << endl;
		cout << "Adding sauce... " << sauce << endl;
		cout << "Adding toppings: " << endl;
		cout <<"       " << toppings << endl;
	} 

	void bake()
	{
		cout << "Back for 25 mins at 350" << endl;
	}

	void cut()
	{
		cout << "Cutting the pizza into diagonal slices" << endl;
	}

	void box()
	{
		cout << "Place pizza in officicl PizzaStore box" << endl;
	}

	string getName()
	{
		return name;
	}
};


class NYStyleCheesePizza : public Pizza
{
public:
	NYStyleCheesePizza()
	{
		this->name = "NY Style Sauce and Cheese Pizza";
		this->dough = "Thin Crust Dough";
		this->sauce = "Marinara Sauce";
		this->toppings = "Grated Regggiano Cheese";
	}
};


class ChicagoStyleCheesePizza : public Pizza
{
public:
	ChicagoStyleCheesePizza()
	{
		this->name = "Chicago Style Deep Dish Cheese Pizza";
		this->dough = "Extra Thick Crust Dough";
		this->sauce = "Plum Tomato Sauce";
		this->toppings = "Shredded Mozzarella Cheese";	
	}


	void cut()
	{
		cout << "Cutting the pizza into aqure slices" << endl;
	}
};


class PizzaStroe
{
public:
	Pizza* orderPizza(string type)
	{
		Pizza* pizza;
		pizza = createPizza(type);

		pizza->prepare();
		pizza->bake();
		pizza->cut();
		pizza->box(); 

		return pizza;
	}
	
	virtual Pizza* createPizza(string type) = 0;
};


class NYPizzaStore : public PizzaStroe
{
public:
	Pizza* createPizza(string item)
	{
		if (item == "cheese")
			return new NYStyleCheesePizza();
		else
			return NULL;
	}
};


class ChicagoPizzaStore : public PizzaStroe
{
public:
	Pizza* createPizza(string item)
	{
		if (item == "cheese")
			return new ChicagoStyleCheesePizza();
		else
			return NULL;
	}
};


int main()
{
	PizzaStroe* nyStore = new NYPizzaStore();
	PizzaStroe* chicagoStore = new ChicagoPizzaStore();


	Pizza* pizza = nyStore->orderPizza("cheese");
	cout << "Ethan ordered a " + pizza->getName() << endl;

	cout << endl;

	pizza = chicagoStore->orderPizza("cheese");
	cout << "Joel ordered a " + pizza->getName() << endl;


	delete nyStore;
	delete chicagoStore;

	return 0;
}