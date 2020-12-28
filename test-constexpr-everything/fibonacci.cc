constexpr uint64_t factorial(uint64_t n) { return n <= 1 ? 1 : (n * factorial(n - 1)); }

constexpr uint64_t fibonacci(uint64_t n) { return n <= 1 ? n : fibonacci(n - 1) + fibonacci(n - 2); }

int main()
{
    // 这可能不会真的被优化
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
