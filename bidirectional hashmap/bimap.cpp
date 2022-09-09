#include "bimap.h"
#include <iostream>

template<class T1, class T2>
Bimap<T1, T2>::Bimap()
{

}

template<class T1, class T2>
Bimap<T1, T2>::Bimap(std::initializer_list<std::pair<T1, T2>> data)
{
    for (auto var : data)
        this->Insert(var.first, var.second);
}

template<class T1, class T2>
bool Bimap<T1, T2>::Insert(T1 const& inp1, T2 const& inp2)
{
    size_t hash1 = std::hash<T1>{}(inp1);
    size_t hash2 = std::hash<T2>{}(inp2);

    auto f1 = map1.find(hash2);
    auto f2 = map2.find(hash1);
    if (!(f1 == map1.end() || f2 == map2.end()))
        return false;

    map1.insert(std::make_pair(hash2, T1{ inp1 }));
    map2.insert(std::make_pair(hash1, T2{ inp2 }));
    return true;
}

template<class T1, class T2>
std::pair<T1, bool> Bimap<T1, T2>::Find(T2 const& inp2)
{
    size_t hash2 = std::hash<T2>{}(inp2);
    auto f1 = map1.find(hash2);

    if (f1 == map1.end())
        return std::make_pair(T1{}, false);

    return std::make_pair(f1->second, true);
}

template<class T1, class T2>
std::pair<T2, bool> Bimap<T1, T2>::Find(T1 const& inp1)
{
    size_t hash1 = std::hash<T1>{}(inp1);
    auto f2 = map2.find(hash1);

    if (f2 == map2.end())
        return std::make_pair(T2{}, false);

    return std::make_pair(f2->second, true);
}

template<class T1, class T2>
bool Bimap<T1, T2>::Remove(T2 const& key)
{    
    auto [val, hit] = this->Find(key);
    if (!hit)
        return false;

    size_t hash2 = std::hash<T2>{}(key);
    size_t hash1 = std::hash<T1>{}(val);
    return map1.erase(hash2) && map2.erase(hash1);  // should always be true
}

template<class T1, class T2>
bool Bimap<T1, T2>::Remove(T1 const& key)
{
    auto [val, hit] = this->Find(key);
    if (!hit)
        return false;

    size_t hash1 = std::hash<T1>{}(key);
    size_t hash2 = std::hash<T2>{}(val);
    return map2.erase(hash1) && map1.erase(hash2);  // should always be true
}