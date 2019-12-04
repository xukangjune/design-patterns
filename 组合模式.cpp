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


class MenuComponent
{
public:
	virtual void add(MenuComponent* menuComponent)
	{
		cout << "Not defined" << endl;
	}

	virtual void remove(MenuComponent* menuComponent)
	{
		cout << "Not defined" << endl;
	}

	virtual MenuComponent* getChild(int i)
	{
		cout << "Not defined" << endl;
		return NULL;
	}

	virtual string getName()
	{
		cout << "Not defined" << endl;
		return "";
	}

	virtual string getDescription()
	{
		cout << "Not defined" << endl;
		return "";
	}

	virtual double getPrice()
	{
		cout << "Not defined" << endl;
		return 0.0;
	}

	virtual bool isLeaf()
	{
		return false;
	}

	virtual void print()
	{
		cout << "Not defined" << endl;
	}
};


//菜单项类，相当于叶子节点
class MenuItem : public MenuComponent
{
public:
	MenuItem(string name, string description, double price) : name(name), description(description), price(price) {}

	string getName()
	{
		return name;
	}

	string getDescription()
	{
		return description;
	}

	double getPrice()
	{
		return price;
	}

	bool isLeaf()
	{
		return true;
	}

	void print()
	{
		cout << " " << getName() << ", " << getPrice() << endl;
		cout << "      --" << getDescription() << endl;
	}

private:
	string name;
	string description;
	double price;
};


//菜单类，包含了菜单项和菜单，相当于树中的节点
class Menu : public MenuComponent
{
public:
	Menu(string name, string description) : name(name), description(description) {}

	void add(MenuComponent* menuComponent)
	{
		menuComponents.push_back(menuComponent);
	}

	void remove(MenuComponent* menuComponent)
	{
		for (auto iter=menuComponents.begin(); iter != menuComponents.end(); iter++)
		{
			if (*iter == menuComponent)
			{
				menuComponents.erase(iter);
				break;
			}
		}

		cout << "Not matched" << endl;
	}

	MenuComponent* getChild(int i)
	{
		if (i < menuComponents.size())
			return menuComponents[i];
		cout << "out of range" << endl;
		return NULL;
	}

	string getName()
	{
		return name;
	}

	string getDescription()
	{
		return description;
	}

	void print()
	{
		cout << "\n" << getName() << ", " << getDescription() << endl;
		cout << "---------------------------------" << endl;

		for (auto menuComponent : menuComponents)
		{
			menuComponent->print();
		}
	}

private:
	vector<MenuComponent*> menuComponents;
	string name;
	string description;
};


//女招待类，负责打印所有的信息
class Waitress
{
public:
	Waitress(MenuComponent* allMenus) : allMenus(allMenus) {}

	void printMenu()
	{
		allMenus->print();
	}

private:
	MenuComponent* allMenus;
};



int main()
{
	MenuComponent* pancakeHouseMenu = new Menu("PANCAKE HOUSE MENU", "Breakfast");
	MenuComponent* dinerMenu = new Menu("DINER MENU", "Launch");
	MenuComponent* cafeMenu = new Menu("CAFE MENU", "Dinner");
	MenuComponent* desertMenu = new Menu("DESERT MENU", "desert");

	MenuComponent* allMenus = new Menu("ALL MENUS", "All menus combined");
	allMenus->add(pancakeHouseMenu);
	allMenus->add(dinerMenu);
	allMenus->add(cafeMenu);

	pancakeHouseMenu->add(new MenuItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs, and toast", 2.99));
	pancakeHouseMenu->add(new MenuItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", 2.99));
	pancakeHouseMenu->add(new MenuItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", 3.49));
	pancakeHouseMenu->add(new MenuItem("Waffles", "Wafles, with your choice of blueberries or strawberries", 3.59));

	desertMenu->add(new MenuItem("Apple Pie(v)", "Apple pie with a flakey crust, topped with vanilla ice cream", 1.59));
	desertMenu->add(new MenuItem("Cheeesecake(v)", "Creamy New York cheesecake, with a chocolate graham crust", 1.99));
	desertMenu->add(new MenuItem("Sorbet(v)", "Ascoop of raspberry and a scoop of lime", 1.89));

	dinerMenu->add(new MenuItem("Vegetarian BLT(v)", "(Fakin' ) Bacon with lettuce $ tomato on whole wheat", 2.99));
	dinerMenu->add(new MenuItem("BLT", "Bacon with lettuce & tomato on whole wheat", 2.99));
	dinerMenu->add(new MenuItem("Soup of the day", "A hot dog, with saurkraut, relish, onions, topped with cheese", 3.05));
	dinerMenu->add(desertMenu);

	cafeMenu->add(new MenuItem("Veggie Burger and Air Fries", "Veggie burger on a whole wheat bun, lettuce, tomato, and fries", 3.99));
	cafeMenu->add(new MenuItem("Soup of the day", "A cup of the soup of the day, with a side salad", 3.69));
	cafeMenu->add(new MenuItem("Burrito", "A large burrito, with whole pinto beans, salsa, guacamole", 4.29));

	Waitress* waitress = new Waitress(allMenus);
	waitress->printMenu();



	return 0;

}