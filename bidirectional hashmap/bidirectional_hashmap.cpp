#include <iostream>
#include "bimap.h"
#include "bimap.cpp"

struct my_data
{
    my_data() {};
    my_data(std::string i1, std::string i2, int i3) : s1{ i1 }, s2{ i2 }, x{ i3 } {};
    std::string s1, s2;
    int x;
    bool operator==(my_data const& other) const
    {
        return s1 == other.s1 &&
            s2 == other.s2 &&
            x == other.x;
    }
};

template<> 
struct std::hash<my_data>
{
    std::size_t operator()(my_data const& k) const
    {
        return ((std::hash<std::string>{}(k.s1)
            ^ (std::hash<std::string>{}(k.s2) << 1)) >> 1)
            ^ (std::hash<int>{}(k.x) << 1);
    }
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

    Bimap<std::string, my_data> map2({ {"languages", {"C++", "C", 23}}});

    std::cout << "insert new: " << map2.Insert("hardware", {"CPU", "GPU", 10}) << "\n";
    std::cout << "insert existing: " << map2.Insert("hardware", { "CPU", "GPU", 10 }) << "\n";
    auto [x3, y3] = map2.Find("hardware");
    std::cout << "hit: " << y3 << " value: " << x3.s1 << "\n";
    auto [x4, y4] = map2.Find({"C++", "C", 23});
    std::cout << "hit: " << y4 << " value: " << x4 << "\n";
    std::cout << "delete element: " << map2.Remove({ "C++", "C", 23 }) << "\n";
    std::cout << "delete element2: " << map2.Remove("hardware") << "\n";
    std::cout << "delete same2: " << map2.Remove("hardware") << "\n";
}

