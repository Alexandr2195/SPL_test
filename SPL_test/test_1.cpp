#include <iostream> //для вывода в консоль

void PrintIntBin(signed int In)
{
    constexpr signed int Sp((sizeof(signed int) * 8) - 1);

    printf("0b");

    for (signed int i(Sp); i >= 0; i--)
    {
        if ((In >> i) & 1)
            printf("1");
        else
            printf("0");
    }

    printf("\n");

    return;
}