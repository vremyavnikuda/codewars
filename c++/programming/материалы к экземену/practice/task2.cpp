#include <iostream>
#include <list>

template<typename T>

bool isEquality(const std::list<T> &L1, const std::list<T> &L2)
{
    if (L1.size() != L2.size())
    {
        return false;
    }

    return std::equal(L1.begin(), L1.end(), L2.begin(), L2.end());
};

int main()
{
    std::list<int> L1 = {1, 2, 3, 4};
    std::list<int> L2 = {1, 2, 3, 4, 5};

    bool L1_equals_L2 = isEquality(L1, L2);

    std::cout << "L1==L2 : " << (L1_equals_L2 ? "Yes" : "No") << std::endl;
};