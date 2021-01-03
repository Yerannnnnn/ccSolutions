// compiler see https://godbolt.org/z/T47aG6

constexpr uint64_t factorial(uint64_t n) { return n <= 1 ? 1 : (n * factorial(n - 1)); }

#if 1
constexpr uint64_t fibonacci(uint64_t n) { return n <= 1 ? n : fibonacci(n - 1) + fibonacci(n - 2); }
#else
constexpr uint64_t fibonacci(uint64_t n)
{
    uint64_t F0{0};
    uint64_t F1{1};
    uint64_t F{};

    if (n <= 1) {
        return n;
    } else {
        for (uint64_t i = 2; i <= n; ++i) {
            F  = F0 + F1;
            F0 = F1;
            F1 = F;
        }
        return F;
    }
}
#endif
// const base function
void test1()
{
    // 这可能不会真的被优化 (在msvc中不会)
    std::cout << factorial(20) << '\n';
    std::cout << factorial(21) << '\n';
    std::cout << factorial(22) << '\n';
    std::cout << fibonacci(20) << '\n';
    std::cout << fibonacci(21) << '\n';
    std::cout << fibonacci(22) << '\n';

    // it works
    {
        constexpr auto ret = factorial(20);
        std::cout << ret << '\n';
    }
    {
        constexpr auto ret = factorial(21);
        std::cout << ret << '\n';
    }
    {
        constexpr auto ret = factorial(22);
        std::cout << ret << '\n';
    }
    {
        constexpr auto ret = fibonacci(20);
        std::cout << ret << '\n';
    }
    {
        constexpr auto ret = fibonacci(21);
        std::cout << ret << '\n';
    }
    {
        constexpr auto ret = fibonacci(22);
        static_assert(ret == fibonacci(22));
        std::cout << ret << '\n';
    }
}

// const stl
void test2()
{
    // it works
    constexpr std::array valuesA{fibonacci(8), fibonacci(9), fibonacci(10)};
    constexpr uint64_t   valuesB[]{fibonacci(8), fibonacci(9), fibonacci(10)};
    std::cout << valuesA[1] << '\n';
    std::cout << valuesA[2] << '\n';
    std::cout << valuesB[1] << '\n';
    std::cout << valuesB[2] << '\n';
}

// contexpr function return stl
#if 1
constexpr const uint64_t NN = 20;
#else
// message : failure was caused by evaluation exceeding step limit of 1048576 (/constexpr:steps<NUMBER>)
constexpr const uint64_t NN = 50;
#endif
constexpr std::array<uint64_t, NN> fill_array()
{
    std::array<uint64_t, NN> v{0};
    for (uint64_t i = 0; i < NN; ++i) {
        v[i] = fibonacci(i);
    }
    return v;
}
void test3()
{
    // it works
    constexpr std::array<uint64_t, NN> v = fill_array();
    std::cout << v[9] << '\n';
    std::cout << v[10] << '\n';

    // you can use static_assert check compile time tests
    static_assert(v[1] == 1, "Test failed! Fibonnaci(1) != 1!\n");
    static_assert(v[10] == 55, "Test failed! Fibonnaci(10) != 55!\n");
}

int main()
{
    test1();
    test2();
    test3();
}
