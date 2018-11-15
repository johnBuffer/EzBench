#include "Benchmark.hpp"
#include <vector>
#include <list>

struct TestStruct
{
	double ddd[20];

	TestStruct() {}

	TestStruct(int)
	{
		ddd[1] = rand() % 10000;
	}

	void increaseA()
	{
		ddd[0]++;
	}
};

void vecAdd(std::vector<TestStruct>* vec, uint32_t add_count)
{
	srand(0);
	for (int i(add_count); i--;)
	{
		vec->push_back(TestStruct(0));
	}
}

void listAdd(std::list<TestStruct>* list, uint32_t add_count)
{
	srand(0);
	for (int i(add_count); i--;)
	{
		list->push_back(TestStruct(0));
	}
}

void vecIter(std::vector<TestStruct>* container)
{
	for (TestStruct& ts : *container)
	{
		ts.increaseA();
	}
}

void listIter(std::list <TestStruct>* container)
{
	for (TestStruct& ts : *container)
	{
		ts.increaseA();
	}
}

void vecDel(std::vector<TestStruct>* container)
{
	for (auto it(container->begin()); it != container->end(); ) {
		if (it->ddd[1] == 0) {
			it = container->erase(it);
		}
		else {
			++it;
		}
	}
}

void listDel(std::list<TestStruct>* container)
{
	for (auto it(container->begin()); it != container->end(); ) {
		if (it->ddd[1] == 0) {
			it = container->erase(it);
		}
		else {
			++it;
		}
	}
}

int main()
{
	std::vector<TestStruct> vec;
	std::list<TestStruct> list;

	uint8_t  iteration_count = 1;
	uint32_t objects_count = 1000000;

	ezb::Benchmark bench{
		iteration_count,
		{
			{"Insertion",
				{
					{"Vector", std::bind(vecAdd, &vec,  objects_count)},
					{"List", std::bind(listAdd,  &list, objects_count)}
				}
			},
			{"Iteration",
				{
					{"Vector", std::bind(vecIter, &vec)},
					{"List", std::bind(listIter,  &list)}
				}
			},
			{"Deletion",
				{
					{"Vector", std::bind(vecDel, &vec)},
					{"List", std::bind(listDel,  &list)}
				}
			}
		}
	};

	bench.run();

	return 0;
}