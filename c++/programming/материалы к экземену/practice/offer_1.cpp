#include <vector>
#include <iostream>

template <class T, template <class...> class C, class U>
C<T> cast_all(const C<U> &c)
{
    C<T> result(c.begin(), c.end());
    return result;
}

int main()
{
    std::vector<float> vf = {1.2, 2.6, 3.7};
    auto vi = cast_all<int>(vf);
    for (auto &&i : vi)
    {
        std::cout << i << std::endl;
    }
}