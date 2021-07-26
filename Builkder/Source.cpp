#include<iostream>
#include<string>
using namespace std;

class Computer
{
	string type;
	string cpu;
	size_t ram;
	string disk;
	string gpu;
public:
	void set_type(const string& type)
	{
		this->type = type;
	}
	void set_cpu(const string& cpu)
	{
		this->cpu = cpu;
	}
	void set_ram(size_t ram)
	{
		this->ram = ram;
	}
	void set_disk(const string& disk)
	{
		this->disk = disk;
	}
	void set_gpu(const string& gpu)
	{
		this->gpu = gpu;
	}

	void info()const
	{
		cout << type << endl;
		cout << cpu << endl;
		cout << ram << endl;
		cout << disk << endl;
		cout << gpu << endl;
	}
};

class ComputerBuilder
{
protected:
	Computer* computer;
public:
	ComputerBuilder()
	{
		this->computer = new Computer;
	}
	virtual ~ComputerBuilder()
	{
		delete this->computer;
	}
	Computer* getComputer()
	{
		return computer;
	}
	void createNewComputer()
	{
		computer = new Computer;
	}
	virtual void setTYPE() = 0;
	virtual void setCPU() = 0;
	virtual void setRAM() = 0;
	virtual void setDISK() = 0;
	virtual void setGPU() = 0;
};

class CheapComputerBuilder :public ComputerBuilder
{
public:
	~CheapComputerBuilder() {}
	void setTYPE() override
	{
		computer->set_type("Ѕюджетный компьютер");
	}
	void setCPU() override
	{
		computer->set_cpu("Pentium");
	}
	void setRAM() override
	{
		computer->set_ram(4);
	}
	void setDISK() override
	{
		computer->set_disk("Toshiba HDD 500 GB");
	}
	void setGPU() override
	{
		computer->set_gpu("Integrated GPU");
	}
};
class OfficeComputerBuilder :public ComputerBuilder
{
public:
	~OfficeComputerBuilder() {}
	void setTYPE() override
	{
		computer->set_type("ќффисный компьютер");
	}
	void setCPU() override
	{
		computer->set_cpu("Core i3");
	}
	void setRAM() override
	{
		computer->set_ram(8);
	}
	void setDISK() override
	{
		computer->set_disk("Kingston SSD 240");
	}
	void setGPU() override
	{
		computer->set_gpu("Integrated GPU");
	}
};
class GameComputerBuilder :public ComputerBuilder
{
public:
	~GameComputerBuilder() {}
	void setTYPE() override
	{
		computer->set_type("»гровой компьютер");
	}
	void setCPU() override
	{
		computer->set_cpu("Core i7");
	}
	void setRAM() override
	{
		computer->set_ram(16);
	}
	void setDISK() override
	{
		computer->set_disk("Samsung SSD 500 GB");
	}
	void setGPU() override
	{
		computer->set_gpu("nVidia GeForce 2050 Ti");
	}
};
class Assembler
{
	ComputerBuilder* computer;
public:
	void assemblyComputer(ComputerBuilder* computer)
	{
		this->computer = computer;
		this->computer->setCPU();
		this->computer->setDISK();
		this->computer->setGPU();
		this->computer->setRAM();
		this->computer->setTYPE();
	}
};

void main()
{
	setlocale(0, "Rus");
	CheapComputerBuilder cheap_comp;
	OfficeComputerBuilder office;
	GameComputerBuilder for_crysis;

	Assembler sysadmin;
	sysadmin.assemblyComputer(&cheap_comp);
	cheap_comp.getComputer()->info();
	cout << endl;
	sysadmin.assemblyComputer(&office);
	office.getComputer()->info();
	cout << endl;
	sysadmin.assemblyComputer(&for_crysis);
	for_crysis.getComputer()->info();
}