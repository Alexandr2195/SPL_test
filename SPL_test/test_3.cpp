#include "test_3.h"

#include <map>
#include <vector>
#include <cassert>

constexpr unsigned int INVALID_INDEX(static_cast<unsigned int>(-1));

List::~List(void)
{
    for (auto [Current, Next] = std::tuple{ this->head, (ListNode*)nullptr }; Current; Current = Next)
    {
        Next = Current->next;
        delete Current;
    }
}

void List::Serialize(FILE* file)
{
    if (!file)
        return;

    std::map<ListNode*, int> Index;         //у unordered_map сложность от O(1) до O(n), 
                                            //в цикле ниже, может получиться сложность O(n^2) по этому, решил использовать обычную map 

    for(auto [Current, i] = std::tuple{ head, 0 }; Current; Current = Current->next, i++)    //O(n)
        Index.insert( { Current , i} );                                                      //O(log(n))      //Индексация листа для сохранения на  ListNode* rand;

    fwrite(reinterpret_cast<const void*>(&this->count), 1, sizeof(int), file);               //записываю размер листа
    
    for (ListNode* Current(head); Current; Current = Current->next)                          //O(n)             
    {
        unsigned int ind_rand(INVALID_INDEX);

        if (Current->rand)
            ind_rand = Index.at(Current->rand);                                              //O(log(n))

        auto StrSize(Current->data.size());

        size_t CheckSizeOut (0);
        size_t CheckSizeIn  (sizeof(unsigned int) + sizeof(size_t) + StrSize);

        CheckSizeOut += fwrite((const void*)&ind_rand            , 1, sizeof(unsigned int)  , file);            //запись индекса рандомного указателя
        CheckSizeOut += fwrite((const void*)&StrSize             , 1, sizeof(size_t)        , file);            //размер строки
        CheckSizeOut += fwrite((const void*)Current->data.c_str(), 1, StrSize               , file);            //строка

        assert(CheckSizeIn == CheckSizeOut);                                   
    }
}

void List::Deserialize(FILE* file)
{
    if (!file)
        return;

    fread(&this->count, 1, sizeof(int), file);          //размер списка

    if (!this->count)
    {
        this->head = nullptr;
        this->tail = nullptr;
        return;
    }

    std::vector<ListNode*> indexList;

    indexList.resize(this->count);     //резервирую место, что бы лишний раз не вызывать realloc

    for (auto [lPrev, i] = std::tuple{ (ListNode*)nullptr, 0 }; i < this->count; i++)               //O(n)
    {
        auto Current = new ListNode; Current->next = Current->prev = Current->rand = nullptr;

        if (lPrev)
        {
            lPrev   ->next = Current;
            Current ->prev = lPrev  ;
        }

        indexList.at(i) = Current;

        lPrev = Current;
    }                                                                                                   //создание Node, индексация, заполнение указателей на next и prev

    this->head = indexList.at(0);
    this->tail = indexList.at(static_cast<size_t>(this->count - 1));

    for (const auto& Current : indexList)                               //O(n)
    {
        unsigned int    RandIndex   (0);
        size_t          strSize     (0);
        fread((void*)&RandIndex, 1, sizeof(unsigned int), file);                            //чтение индекса рандомного указателя

        Current->rand = RandIndex == INVALID_INDEX ? nullptr : indexList.at(RandIndex);     

        fread((void*)&strSize, 1, sizeof(size_t), file);            //чтение размера строки
        Current->data.resize(strSize);                              //задаю размер для строки перед прочтением
        fread((void*)Current->data.data(), 1, strSize, file);       //чтение строки
    }

    return;
}

//просто инициализация для проверки
void List::InitTestList(void)
{
    ListNode* a1 (new ListNode);
    ListNode* a2 (new ListNode);
    ListNode* a3 (new ListNode);
    ListNode* a4 (new ListNode);
    ListNode* a5 (new ListNode);

    a1->prev = nullptr;
    a1->next = a2;
    a1->rand = a5;
    a1->data = "2313";
    
    a2->prev = a1;
    a2->next = a3;
    a2->rand = nullptr;
    a2->data = "GH";
    
    a3->prev = a2;
    a3->next = a4;
    a3->rand = a1;
    a3->data = "DK";
    
    a4->prev = a3;
    a4->next = a5;
    a4->rand = a3;
    a4->data = "Ssdasdfwerwc";
    
    a5->prev = a4;
    a5->next = nullptr;
    a5->rand = a2;
    a5->data = "R$$#32wefd52";    
    
    head = a1;
    tail = a2;
    
    count = 5;
}