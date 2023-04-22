#include "my_array.h"
#include <cstddef>
#include <cassert>

namespace mainNamespace {

}
using lab_13::my_array;

template<typename T, std::size_t N>
void test_core() {
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    a.empty();
    ca.empty();
    a.size();
    ca.size();

    a.at(0);
    ca.at(0);
    a[0];
    ca[0];
    (void)static_cast<const T &>(a[0]);
    (void)static_cast<const T &>(ca[0]);
}

template<typename T, std::size_t N>
void test_assign() {
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    a.fill(T());

    a[0] = T();
    a[0] = a[0];
    a[0] = ca[0];
}

class NonCopyable {
 public:
    NonCopyable() {}
 private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable);
};

template<std::size_t N>
void test_bool() {
    my_array<bool, N> a;
    a.fill(false);
    a[0] = true;
    a[1] = a[0];
    assert(a[0] == true);
    assert(a[1] == true);
}

template<std::size_t N>
void testInOutBool() {
    lab_13::my_array<bool, N> a;
    a.fill(false);
    a[1] = true;
    a[2] = a[1];
    std::cout << a[0] << '\n';
    std::cout << a[1] << '\n';
    std::cout << a[2] << '\n';
    std::cin >> a[3];
    std::cout << a[3] << '\n';
}

int main() {
    test_core<int, 10>();
    test_core<bool, 10>();
    test_core<NonCopyable, 10>();

    test_assign<int, 10>();
    test_assign<bool, 10>();
    test_bool<10>();
    testInOutBool<10>();
}
