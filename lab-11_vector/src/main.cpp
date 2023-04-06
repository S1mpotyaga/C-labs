#include <iostream>
#include <string>
#include <cassert>
#include <vector>   

#include "my_vector.h"

namespace product {
    class Product;
}

std::ostream& operator<< (std::ostream& out, const product::Product& p);

namespace product {

    class Product {
    public:
        Product(std::string name, int quantity, double price);
        bool operator == (Product other);

        friend std::ostream& ::operator<< (std::ostream& out, const Product& p);

    private:
        std::string name_;
        int quantity_;
        double price_;
    };

    Product::Product(std::string name, int quantity, double price) {
        name_ = std::move(name);
        quantity_ = quantity;
        price_ = price;
    }

    bool Product::operator == (Product other) {
        return name_ == other.name_ && quantity_ == other.quantity_ && price_ == other.price_;
    }

}  // namespace product

std::ostream& operator<< (std::ostream& out, const product::Product& p) {
    out << p.name_ << ' ' << p.quantity_ << ' ' << p.price_;
    return out;
}

namespace test{
    template<typename T>
    void test_my_vector(std::vector<T> testVector, std::size_t start_cap) {
        containers::my_vector<T> v;
        v.reserve(start_cap);
        std::size_t cap = 1;
        while (cap < start_cap) cap *= 2;
        for (std::size_t i = 0; i < testVector.size(); i++) {
            if (i >= cap) cap *= 2;
            v.push_back(testVector[i]);
            assert(v[i] == testVector[i]);
            assert(v.size() == i + 1);
            assert(v.capacity() == cap);
        }
        v.clear();
        assert(v.empty());
        assert(v.size() == 0);
        assert(v.capacity() == cap);

        for (int i = testVector.size() - 1; i >= 0; i--) {
            v.push_back(testVector[i]);
            assert(v[testVector.size() - i - 1] == testVector[i]);
            assert(v.size() == testVector.size() - i);
            assert(v.capacity() == cap);
        }

        containers::my_vector<T> u;
        u = v;
        assert(v.size() == u.size());
        assert(v.capacity() == u.capacity());

        for (std::size_t i = 0; i < testVector.size(); i++) {
            v.pop_back();
            assert(v.size() == testVector.size() - i - 1);
        }


    }

    template<typename T>
    void test_my_vector_default_constructible(std::vector<T> testVector, std::size_t startSize) {
        containers::my_vector<T> v;
        v.resize(startSize);
        for (std::size_t i = 0; i < startSize; i++) assert(v[i] == T());
        std::size_t cap = 1;
        while (cap < startSize) cap *= 2;
        assert(v.capacity() == cap);
        for (std::size_t i = 0; i < testVector.size(); i++) {
            if (i + startSize >= cap) cap *= 2;
            v.push_back(testVector[i]);
            assert(v[i + startSize] == testVector[i]);
            assert(v.size() == i + 1 + startSize);
            assert(v.capacity() == cap);
        }

        containers::my_vector<T> u(100);
        u = v;
        assert(v.size() == u.size());
        assert(v.capacity() == u.capacity());

        v.clear();
        assert(v.empty());
        assert(v.size() == 0);
        assert(v.capacity() == cap);   
    }
}

int main() {
	
    std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::vector<product::Product> v2 = {product::Product("abc", 1, 3.2),
                                product::Product("sdsdf", 2, 4.56),
                                product::Product("asd", 0, 1.1)};

    test::test_my_vector(v1, 2);
    test::test_my_vector(v1, 7);
    test::test_my_vector(v1, 100);
    test::test_my_vector(v2, 2);
    test::test_my_vector(v2, 1);
    test::test_my_vector_default_constructible(v1, 1);
    test::test_my_vector_default_constructible(v1, 2);

    return 0;
}
