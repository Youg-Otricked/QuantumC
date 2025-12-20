#include <iostream>
#include <ctime>
int main()
{
    srand(time(0));
    int randNum = rand() % 5 + 1;

    switch (randNum)
    {
    case 1:
        std::cout << "You fail." << '\n';
        break;
    case 2:
        std::cout << "yhouyoulyowiuayfoiawyfowai";
        break;
    case 3:
        std::cout << "you give giftcards as gifts.";
        break;
    case 4:
        std::cout << "random";
        break;
    case 5:
        std::cout << "this is a random event generator";
        break;
    }

    return 0;
}