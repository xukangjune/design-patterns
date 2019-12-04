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


class Equipment
{
public:
	string name;

	void on()
	{
		cout << name << " on" << endl;
	}

	void off()
	{
		cout << name << " off" << endl;
	}
};


class Amplifier : public Equipment
{
public:
	Amplifier(string name)
	{
		this->name = name;
	}
};


class Tuner : public Equipment
{
public:
	Tuner(string name)
	{
		this->name = name;
	}
};


class DvdPlayer : public Equipment
{
public:
	DvdPlayer(string name)
	{
		this->name = name;
	}
};


class Screen : public Equipment
{
public:
	Screen(string name)
	{
		this->name = name;
	}
};


class PopCornPopper : public Equipment
{
public:
	PopCornPopper(string name) 
	{
		this->name = name;
	}
};


class HomeTheaterFacade
{
public:
	HomeTheaterFacade(Amplifier* amp,
	Tuner* tuner,
	DvdPlayer* dvd,
	Screen* screen, 
	PopCornPopper* popper) : 
	amp(amp),
	tuner(tuner),
	dvd(dvd),
	screen(screen),
	popper(popper) {}

	void watchMovie()
	{
		cout << "\nWe are now watching movie...\n" << endl;
		amp->on();
		tuner->on();
		dvd->on();
		screen->on();
		popper->on();
	}

	void endMovie()
	{
		cout << "\nShutting movie...\n" << endl;
		amp->off();
		tuner->off();
		dvd->off();
		screen->off();
		popper->off();
	}

private:
	Amplifier* amp;
	Tuner* tuner;
	DvdPlayer* dvd;
	Screen* screen;
	PopCornPopper* popper;
};


int main()
{
	Amplifier* amp = new Amplifier("Amplifier");
	Tuner* tuner = new Tuner("Tuner");
	DvdPlayer* dvd = new DvdPlayer("DvdPlayer");
	Screen* screen = new Screen("Screen");
	PopCornPopper* popper = new PopCornPopper("PopCornPopper");
	HomeTheaterFacade* homeTheater = new HomeTheaterFacade(amp, tuner, dvd, screen, popper);

	homeTheater->watchMovie();
	homeTheater->endMovie();


	delete amp;
	delete tuner;
	delete dvd;
	delete screen;
	delete popper;
	delete homeTheater;

	return 0;
}