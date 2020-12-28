constexpr int factorial(int n) { return n <= 1 ? 1 : (n * factorial(n - 1)); }

int main()
{
    std::cout << factorial(10) << '\n';
    std::cout << factorial(11) << '\n';
    std::cout << factorial(12) << '\n';
}
