#pragma once
#include <unordered_map>

template<class T1, class T2>
class Bimap {
public:
    Bimap() = default;
    explicit Bimap(std::initializer_list<std::pair<T1, T2>> const& data);
    bool Insert(T1 const& inp1, T2 const& inp2);
    std::pair<T1, bool> Find(T2 const& key);
    std::pair<T2, bool> Find(T1 const& key);
    bool Remove(T2 const& key);
    bool Remove(T1 const& key);

private:
    std::unordered_map<size_t, T1> map1{};
    std::unordered_map<size_t, T2> map2{};
};
