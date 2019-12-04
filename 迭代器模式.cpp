#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<string>
#include<stack>
#include<cmath>
#include<algorithm>
#include<array>

using namespace std;


//菜单项类
class MenuItem
{
public:
	MenuItem(string name, string description, bool vegetarian, double price) : 
		name(name), description(description), vegetarian(vegetarian), price(price) {}

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

	bool isVegetarian()
	{
		return vegetarian;
	}

private:
	string name;
	string description;
	bool vegetarian;
	double price;
};


//抽象的迭代器基类，里面有两个抽象的接口
class Iterator
{
public:
	virtual MenuItem* next() = 0;
	virtual bool hasNext() = 0;
};


//抽象的菜单基类，只提供了一个迭代器接口
class Menu 
{
public:
	virtual Iterator* createIterator() = 0;
};



//煎饼屋对迭代器的实现，即vector对迭代器的实现
class PancakeHouseIterator : public Iterator
{
public:
	PancakeHouseIterator(vector<MenuItem*> menu) : menu(menu) 
	{
		length = menu.size();
		pos = 0;
	}

	bool hasNext()
	{
		if (pos >= length)
		{
			return false;
		}
		return true;
	}

	MenuItem* next()
	{
		if (hasNext())
			return menu[pos++];
		else
			cout << "There is no more item!" << endl;
		return NULL;
	}

private:
	vector<MenuItem*> menu;
	int pos;
	int length;
};


//咖啡馆对迭代器的实现，使用的是set
class CafeHouseIterator : public Iterator
{
public:
	CafeHouseIterator(array<MenuItem*, 5> menu) : menu(menu)
	{
		for (auto elem : menu)
		{
			if (elem != NULL)
				length++;
		}
		pos = 0;
	}

	bool hasNext()
	{
		return (pos < length);
	}

	MenuItem* next()
	{
		if (hasNext())
			return menu[pos++];
		else
			cout << "There is no more item!" << endl;
		return NULL;
	}

private:
	array<MenuItem*, 5> menu;
	int pos;
	int length = 0;
};


//煎饼屋对菜单类的实现，生成煎饼屋的菜单，并返回菜单的迭代器
class PancakeHouseMenu : public Menu
{
public:
	PancakeHouseMenu()
	{	
		addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 2.99);
		addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99);
		addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
		addItem("Waffles", "Wafles, with your choice of blueberries or strawberries", true, 3.59);
	}

	Iterator* createIterator()
	{
		return new PancakeHouseIterator(menuItems);
	}

private:
	vector<MenuItem*> menuItems; 

	void addItem(string name, string description, bool vegetarian, double price)
	{
		MenuItem* menuItem = new MenuItem(name, description, vegetarian, price);
		menuItems.push_back(menuItem);
	}
};


//咖啡馆对菜单项的实现，生成咖啡馆的菜单，并返回菜单的迭代器
class CafeHouseMenu : public Menu
{
public:
	CafeHouseMenu()
	{
		addItem("Veggie Burger and Air Fries", "Veggie burger on a whole wheat bun, lettuce, tomato, and fries", true, 3.99);
		addItem("Soup of the day", "A cup of the soup of the day, with a side salad", true, 3.69);
		addItem("Burrito", "A large burrito, with whole pinto beans, salsa, guacamole", true, 4.29);
	}

	Iterator* createIterator()
	{
		return new CafeHouseIterator(menuItems);
	}

private:
	array<MenuItem*, 5> menuItems{};
	int pos=0;

	void addItem(string name, string description, bool vegetarian, double price)
	{
		MenuItem* menuItem = new MenuItem(name, description, vegetarian, price);
		menuItems[pos++] = menuItem;
	}
};


//女招待的类
class Waitress
{
public:
	   Waitress(Menu* pancakeHouseMenu, Menu* cafeHouseMenu) : pancakeHouseMenu(pancakeHouseMenu), cafeHouseMenu(cafeHouseMenu){}

	   void printMenu()
	   {
	   	Iterator* pancakeHouseIterator = pancakeHouseMenu->createIterator();
	   	Iterator* cafeHouseIterator = cafeHouseMenu->createIterator();

	   	cout << "MENU\n---\nBREAKFAST" << endl;
	   	printMenu(pancakeHouseIterator);

	   	cout << "MENU\n---\nDINNER" << endl;
	   	printMenu(cafeHouseIterator);
	   }

private:
	Menu* pancakeHouseMenu;
	Menu* cafeHouseMenu;

	void printMenu(Iterator* iterator)
	{
		while (iterator->hasNext())
		{
			MenuItem* menuItem = iterator->next();
			cout << menuItem->getName() << ", " << menuItem->getPrice() << " -- " << menuItem->getDescription() << endl;
		}
		cout << endl;
	}
};




int main()
{
	PancakeHouseMenu* pancakeHouseMenu = new PancakeHouseMenu();
	CafeHouseMenu* cafeHouseMenu = new CafeHouseMenu();
	Waitress* waitress = new Waitress(pancakeHouseMenu, cafeHouseMenu);

	waitress->printMenu();

	delete pancakeHouseMenu;
	delete cafeHouseMenu;
	delete waitress;

	return 0;
}