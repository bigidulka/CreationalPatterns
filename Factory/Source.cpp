#include<iostream>
#include<string>
#include<ctime>
#include<list>
using namespace std;

class CPU
{
protected:
	string model;
	double frequency;
	unsigned int number_of_cores;
	unsigned int cache;
	string socket;
	bool hyper_threading;
public:
	CPU(const string& model, double frequency, unsigned int number_of_cores, unsigned int cache, string socket, bool hyper_threading)
	{
		this->model = model;
		this->frequency = frequency;
		this->number_of_cores = number_of_cores;
		this->cache = cache;
		this->socket = socket;
		this->hyper_threading = hyper_threading;
	}
	virtual ~CPU() {}
	virtual void info()const
	{
		cout << model << "F = "
			<< frequency << "GHz, "
			<< number_of_cores << " cores, "
			<< cache << " MB Cache, "
			<< socket << " socket, ";
		if (hyper_threading)cout << "HyperThreading";
		cout << endl;
	}
	virtual const string& get_model()const = 0;
};
class Core_I3 : public CPU
{
public:
	Core_I3() :CPU("Core-i3 2120", 2.5, 2, 3, "LGA1155", true) {}
	~Core_I3() {}

	// Унаследовано через CPU
	const string& get_model() const
	{
		return this->model;
	}
};
class Core_I5 : public CPU
{
public:
	Core_I5() :CPU("Core-i5 2400", 3.4, 4, 4, "LGA1155", false) {}
	~Core_I5() {}

	// Унаследовано через CPU
	const string& get_model() const
	{
		return this->model;
	}
};
class Core_I7 : public CPU
{
public:
	Core_I7() :CPU("Core-i7 2700K", 3.8, 4, 8, "LGA1155", true) {}
	~Core_I7() {}

	const string& get_model() const
	{
		return this->model;
	}
};
class Core_I7EE :public CPU
{
public:
	Core_I7EE() :CPU("Core-i7 EE 2900K", 4.2, 6, 12, "LGA-2011", true) {};
	~Core_I7EE() {}
	const string& get_model() const
	{
		return this->model;
	}
};

//#define FACTORY_AS_GLOBAL_FUNCTION
#ifdef FACTORY_AS_GLOBAL_FUNCTION
enum CPUtype
{
	Core_I3, Core_I5, Core_I7, Core_I7EE
};


CPU* CPUfactory(CPUtype type)
{
	switch (type)
	{
	case Core_I3: return new class Core_I3();
	case Core_I5:return new class Core_I5();
	case Core_I7:return new class Core_I7();
	case Core_I7EE:return new class Core_I7EE();
	default:return nullptr;
	}
}
#endif //FACTORY_AS_GLOBAL_FUNCTION
class CPUFactory
{
public:
	enum CPUType
	{
		Core_I3, Core_I5, Core_I7, Core_I7EE
	};
	static CPU* CreateCPU(CPUType type)
	{
		switch (type)
		{
		case Core_I3: return new class Core_I3();
		case Core_I5:return new class Core_I5();
		case Core_I7:return new class Core_I7();
		case Core_I7EE:return new class Core_I7EE();
		default:return nullptr;
		}
	}
};

void main()
{
	setlocale(0, "Rus");

#ifdef FACTORY_AS_GLOBAL_FUNCTION
	//class Core_I3 corei3;
	//corei3.info();
	CPU* my_cpu = CPUfactory(Core_I7EE);
	my_cpu->info();
	cout << sizeof(CPUtype) << endl;
	int n;
	cout << "Введите кол-во изделий: "; cin >> n;
	CPU** _cpu = new CPU * [n];
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		_cpu[i] = CPUfactory(CPUtype(rand() % 3));
	}
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << ' ';
		_cpu[i]->info();
	}
	for (int i = 0; i < n; i++)
	{
		delete _cpu[i];
	}
	delete[] _cpu;
#endif // FACTORY_AS_GLOBAL_FUNCTION

	CPU* my_cpu = CPUFactory::CreateCPU(CPUFactory::Core_I7EE);
	my_cpu->info();

	int n;
	cout << "Кол-во: "; cin >> n;
	list<CPU*> _cpu;
	for (int i = 0; i < n; i++)
	{
		_cpu.push_back(CPUFactory::CreateCPU(CPUFactory::CPUType(rand() % 4)));
	}
	for (list<CPU*>::iterator it = _cpu.begin(); it != _cpu.end(); it++)
	{
		(*it)->info();
	}
}