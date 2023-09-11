#pragma once
#include <string>

struct ListNode {
    ListNode* prev;
    ListNode* next;
    ListNode* rand; // указатель на произвольный элемент данного списка, либо NULL
    std::string data;
};

class List {
public:
    void Serialize  (FILE* file); // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
    void Deserialize(FILE* file); // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

    ~List   (void);               // понадобился для очистки выделенной памяти

    /*Проверочные методы*/
    void InitTestList   (void);
    void printList      (void)      
    {
        for (ListNode* Current(head); Current; Current = Current->next)
            printf("%s\n", Current->data.data());
    }
    /********************/
private:
    ListNode* head;
    ListNode* tail;
    int       count;
};