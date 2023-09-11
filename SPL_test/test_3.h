#pragma once
#include <string>

struct ListNode {
    ListNode* prev;
    ListNode* next;
    ListNode* rand; // ��������� �� ������������ ������� ������� ������, ���� NULL
    std::string data;
};

class List {
public:
    void Serialize  (FILE* file); // ���������� � ���� (���� ������ � ������� fopen(path, "wb"))
    void Deserialize(FILE* file); // �������� �� ����� (���� ������ � ������� fopen(path, "rb"))

    ~List   (void);               // ����������� ��� ������� ���������� ������

    /*����������� ������*/
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