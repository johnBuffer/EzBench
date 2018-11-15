# EzBench
Easy to use performance comparator for C++ (C++11 required)

## Usage
Include ezbench.hpp
```c++
include "ezbench.hpp"
```

### Create a set of minimal functions to compare
```c++
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
```
Using a very simple test structure
```c++
struct TestStruct
{
  double ddd[20];
  
  TestStruct() = default;
  TestStruct(int)
  {
    ddd[1] = rand() % 10000;
  }

  void increaseA()
  {
    ddd[0]++;
  }
};
```

### Build the benchmark - so EZ
```c++
std::vector<TestStruct> vec;
std::list<TestStruct> list;

uint8_t  iteration_count = 1;
uint32_t objects_count = 1000000;

ezb::Benchmark bench{
  iteration_count, // Not supported yet, set it to 1
  {
    {"Insertion", // Test 1
      {
        {"Vector", std::bind(vecAdd, &vec,  objects_count)},
        {"List", std::bind(listAdd,  &list, objects_count)}
      }
    },
    {"Iteration", // Test 2
      {
        {"Vector", std::bind(vecIter, &vec)},
        {"List", std::bind(listIter,  &list)}
      }
    },
    {"Deletion", // Test 3
      {
        {"Vector", std::bind(vecDel, &vec)},
        {"List", std::bind(listDel,  &list)}
      }
    }
  }
};
```

### Output
```
-----[ Insertion ]-----
List    196.335 ms (100 % -> x1)
Vector  401.454 ms (204 % -> x2)

-----[ Iteration ]-----
Vector  11.769 ms (100 % -> x1)
List    63.3059 ms (537 % -> x5)

-----[ Deletion ]-----
List    63.6138 ms (100 % -> x1)
Vector  1355.97 ms (2131 % -> x21)
```



