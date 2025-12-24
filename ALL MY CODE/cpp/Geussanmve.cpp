#include <iostream>
#include <string>

int add(int a, int b)
{
    return a + b;
}

bool is_even(int a)
{
    if (a % 2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
double exp(double a, int p)
{
    double at = a;
    for (int i = 0; i < p; i++)
    {
        a *= at;
    }
    return a;
}
void calc()
{
    char op;
    double num1;
    double num2;
    std::cout << "Choose an operator. (/, +, -, *, ^) ";
    std::cin >> op;
    std::cout << "number 1 ";
    std::cin >> num1;
    std::cout << "number 2 (must be int if op was a ^) ";
    std::cin >> num2;
    switch (op)
    {
    case '+':
        std::cout << num1 + num2 << '\n';
        break;
    case '-':
        std::cout << num1 - num2 << '\n';
        break;
    case '/':
        std::cout << num1 / num2 << '\n';
        break;
    case '*':
        std::cout << num1 * num2 << '\n';
        break;
    case '^':
        std::cout << exp(num1, num2) << '\n';
        break;
    default:
        std::cout << "not an operation";
    }
}
int main()
{
    std::cout << "Hello, World!" << '\n';
    std::cout << add(99, 1220) << is_even(99);
    calc();
    return 0;
}
