#include <iostream>
#include "bimap.h"
#include "bimap.cpp"

struct data
{
    std::string s1, s2;
    int x;
};

int main()
{
    Bimap<long long, std::string> map({ {2ll, "hi"},{10ll, "hey"}});
    std::cout << "insert new: " << map.Insert(100ll, "hello") << "\n";
    std::cout << "insert existing: " << map.Insert(2ll, "hi") << "\n";
    auto [x, y] = map.Find(10ll);
    std::cout << "hit: " << y << " value: " << x << "\n";
    auto [x1, y1] = map.Find("hey");
    std::cout << "hit: " << y1 << " value: " << x1 << "\n";
    auto [x2, y2] = map.Find("howdy");
    std::cout << "hit: " << y2 << " value: " << x2 << "\n";
    std::cout << "delete element: " << map.Remove("hey") << "\n";
    std::cout << "delete same: " << map.Remove(10ll) << "\n";
    std::cout << "delete element2: " << map.Remove(2ll) << "\n";
    std::cout << "delete same2: " << map.Remove("hi") << "\n";
}

