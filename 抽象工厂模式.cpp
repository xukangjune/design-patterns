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

	virtual void prepare() = 0;

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

	void setName(string name)
	{
		this->name = name;
	}

	string getName()
	{
		return this->name;
	}
};


class PizzaIngredientFactory
{
public:
	virtual void createDough() = 0;
	virtual void createSauce() = 0;
	virtual void createCheese() = 0;
	virtual void createPepperoni() = 0;
	virtual void createClam() = 0;
};


class NYPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
	void createDough()
	{
		cout << "NY circle dough" << endl;
	}

	void createSauce()
	{
		cout << "NY thick sauce" << endl;;
	}

	void createCheese()
	{
		cout << "NY hard cheese" << endl;;
	}

	void createPepperoni()
	{
		cout << "NY warm pepperoni" << endl;
	}

	void createClam()
	{
		cout << "NY fresh clam" << endl;
	}
};


class CHIPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
	void createDough()
	{
		cout << "CHI circle dough" << endl;
	}

	void createSauce()
	{
		cout << "CHI thick sauce" << endl;;
	}

	void createCheese()
	{
		cout << "CHI hard cheese" << endl;;
	}

	void createPepperoni()
	{
		cout << "CHI warm pepperoni" << endl;
	}

	void createClam()
	{
		cout << "CHI fresh clam" << endl;
	}
};


class CheesePizza : public Pizza
{
public:
	PizzaIngredientFactory* ingredientFactory;

	CheesePizza(PizzaIngredientFactory* ingredientFactory)
	{
		this->ingredientFactory = ingredientFactory;
	}

	void prepare()
	{
		cout << "Preoaring..." << endl;
		this->ingredientFactory->createDough();
		this->ingredientFactory->createSauce();
		this->ingredientFactory->createCheese();
	}
};


class ClamPizza : public Pizza
{
public:
	PizzaIngredientFactory* ingredientFactory;

	ClamPizza(PizzaIngredientFactory* ingredientFactory)
	{
		this->ingredientFactory = ingredientFactory;
	}

	void prepare()
	{
		cout << "Preoaring..." << endl;
		this->ingredientFactory->createDough();
		this->ingredientFactory->createSauce();
		this->ingredientFactory->createCheese();
		this->ingredientFactory->createClam();
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
		Pizza* pizza = NULL;
		PizzaIngredientFactory* ingredientFactory = new NYPizzaIngredientFactory();

		if (item == "cheese")
		{
			pizza = new CheesePizza(ingredientFactory);
			pizza->setName("NY style cheese pizza");
		}

		else if (item == "clam")
		{
			pizza = new ClamPizza(ingredientFactory);
			pizza->setName("NY style clam pizza");
		}

		else
		{
			pizza = NULL;
		}

		return pizza;
	}
};


class CHIPizzaStore : public PizzaStroe
{
public:
	Pizza* createPizza(string item)
	{
		Pizza* pizza = NULL;
		PizzaIngredientFactory* ingredientFactory = new CHIPizzaIngredientFactory();

		if (item == "cheese")
		{
			pizza = new CheesePizza(ingredientFactory);
			pizza->setName("CHI style cheese pizza");
		}

		else if (item == "clam")
		{
			pizza = new ClamPizza(ingredientFactory);
			pizza->setName("CHI style clam pizza");
		}

		else
		{
			pizza = NULL;
		}

		return pizza;
	}
};


int main()
{
	PizzaStroe* nyStore = new NYPizzaStore();
	PizzaStroe* chicagoStore = new CHIPizzaStore();


	Pizza* pizza = nyStore->orderPizza("cheese");
	cout << "Ethan ordered a " + pizza->getName() << endl;

	cout << endl;

	pizza = chicagoStore->orderPizza("clam");
	cout << "Joel ordered a " + pizza->getName() << endl;


	delete nyStore;
	delete chicagoStore;

	return 0;
}