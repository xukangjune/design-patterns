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


class Command
{
public:
	string name = "Command";

	string getName()
	{
		return this->name;
	}
	
	virtual void excute() = 0;
	virtual void undo() = 0;
};


class Light
{
public:
	string name = "";
	Light(string name) : name(name) {}

	void on()
	{
		cout << name << " light on..." << endl;
	}

	void off()
	{
		cout << name << " light off..." << endl;
	}
};


class Stereo
{
public:
	string name = "";
	Stereo(string name) : name(name) {}

	void on()
	{
		cout << name << " stereo on..." << endl;
	}

	void off()
	{
		cout << name << " stereo off..." << endl;
	}
};


/*先生成一个空方法，用来刚开始时初始化每个slot，这样每个slot一开始都会有方法的，而不是“空”*/
class NoCommand : public Command
{
public:
	NoCommand()
	{
		name = "NoCommand";
	}

	void excute() {};
	void undo() {};                  
};


class LightOnCommand : public Command
{
public:
	Light* light;
	LightOnCommand(Light* light) : light(light) 
	{
		name = light->name + " light on command";
	}

	void excute()
	{
		light->on();
	}

	void undo()
	{
		light->off();
	}
};


class LightOffCommand: public Command
{
public:
	Light* light;
	LightOffCommand(Light* light) : light(light) 
	{
		name = light->name + " light off command";
	}

	void excute()
	{
		light->off();
	}

	void undo()
	{
		light->on();
	}
};


class StereoOnCommand : public Command
{
public:
	Stereo* stereo;
	StereoOnCommand(Stereo* stereo) : stereo(stereo) 
	{
		name = stereo->name + " stereo on command";
	}

	void excute()
	{
		stereo->on();
	}

	void undo()
	{
		stereo->off();
	}
};


class StereoOffCommand : public Command
{
public:
	Stereo* stereo;
	StereoOffCommand(Stereo* stereo) : stereo(stereo) 
	{
		name = stereo->name + " stereo off command";
	}

	void excute()
	{
		stereo->off();
	}

	void undo()
	{
		stereo->on();
	}
};


class MacroOnCommand : public Command
{
public:
	vector<Command*> commands;

	MacroOnCommand(vector<Command*> commands) : commands(commands) 
	{
		name = "all on commands";
	}

	void excute()
	{
		for (auto command : commands)
			command->excute();
	}

	void undo()
	{
		for (auto command : commands)
			command->undo();
	}
};


class MacroOffCommand : public Command
{
public:
	vector<Command*> commands;

	MacroOffCommand(vector<Command*> commands) : commands(commands) 
	{
		name = "all off commands";
	}

	void excute()
	{
		for (auto command: commands)
			command->excute();
	}

	void undo()
	{
		for (auto command : commands)
			command->undo();
	}
};


class RemoteControl
{
public:
	RemoteControl()
	{
		Command* noCommand = new NoCommand();
		for (int i=0; i<7; ++i)
		{
			onCommand.push_back(noCommand);
			offCommand.push_back(noCommand);
		}
		undoCommand = noCommand;
	}

	void setCommand(int slot, Command* onCommand, Command* offCommand)
	{
		this->onCommand[slot] = onCommand;
		this->offCommand[slot] = offCommand;
	}

	void onButtonWasPushed(int slot)
	{
		onCommand[slot]->excute();
		undoCommand = onCommand[slot];
	}

	void offButtonWasPushed(int slot)
	{
		offCommand[slot]->excute();
		undoCommand = offCommand[slot];
	}

	void undozButtonWasPushed()
	{
		undoCommand->undo();
	}

	void print()
	{
		size_t i=0;
		cout << "-------------- Remote Control -----------------" << endl;
		for (; i<onCommand.size(); ++i)
		{
			cout << "[slot " << i << "] " << onCommand[i]->getName() << "    " <<
			offCommand[i]->getName() << endl;
		}
	}


private:
 	vector<Command*> onCommand;
 	vector<Command*> offCommand;
 	Command* undoCommand;
};


int main()
{
	RemoteControl* control = new RemoteControl();
	control->print();


	Light* livingRoomLight = new Light("Living Room");
	Light* kitchenLight = new Light("Kitchen");
	Stereo* stereo = new Stereo("Living Room");

	LightOnCommand* livingRoomLightOn = new LightOnCommand(livingRoomLight);
	LightOnCommand* kitchenLightOn = new LightOnCommand(kitchenLight);
	LightOffCommand* livingRoomLightOff = new LightOffCommand(livingRoomLight);
	LightOffCommand* kitchenLightOff = new LightOffCommand(kitchenLight);

	StereoOnCommand* stereoOn = new StereoOnCommand(stereo);
	StereoOffCommand* stereoOff = new StereoOffCommand(stereo);

	vector<Command*> allOnCommands{livingRoomLightOn, kitchenLightOn, stereoOn};
	vector<Command*> allOffCommands{livingRoomLightOff, kitchenLightOff, stereoOff};

	MacroOnCommand* allAppliancesOn = new MacroOnCommand(allOnCommands);
	MacroOffCommand* allAppliancesOff = new MacroOffCommand(allOffCommands);

	control->setCommand(3, livingRoomLightOn, livingRoomLightOff);
	control->setCommand(5, kitchenLightOn, kitchenLightOff);
	control->setCommand(2, stereoOn, stereoOff);
	control->setCommand(0, allAppliancesOn, allAppliancesOff);

	control->print();

	cout << "\n--------------------------------\n" << endl;

	control->onButtonWasPushed(2);
	control->undozButtonWasPushed();
	control->offButtonWasPushed(1);
	control->offButtonWasPushed(3);
	control->onButtonWasPushed(3);
	control->undozButtonWasPushed();
	control->onButtonWasPushed(5);
	control->offButtonWasPushed(2);
	control->offButtonWasPushed(5);

	cout << "\n--------------------------------\n" << endl;

	control->offButtonWasPushed(0);
	control->undozButtonWasPushed();
	control->onButtonWasPushed(0);

	return 0;
}