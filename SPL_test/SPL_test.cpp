#include <iostream>
#include "test_3.h"

extern void PrintIntBin (signed int In);     //test 1
extern void RemoveDups  (char* str);         //test 2

char data[] = "AAA BBB AAA"; //проверка второго теста

List l1;
List l2;

int main (void)
{  
    /****************test 1*****************/
    PrintIntBin(static_cast<signed int>(strlen(data)));
    /****************test 2*****************/
    printf("%s\n", data);
    RemoveDups(data);
    printf("%s\n", data);
    /****************test 3*****************/

    l1.InitTestList();
    l1.printList();

    FILE* opF (fopen("out2023_09.txt", "wb"));

    l1.Serialize(opF);

    fclose(opF);

    system("pause");

    FILE* opFR(fopen("out2023_09.txt", "rb"));
    l2.Deserialize(opFR);
    fclose(opFR);

    l2.printList();

    system("pause");

    return 0;
}