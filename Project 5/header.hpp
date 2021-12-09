#ifndef __HEADER__
#define __HEADER__
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cctype>
using namespace std;

const int STR_SIZE = 256;

class CardInfo
{
    char * name;
    double price;
    char * set;
    char * type;
    int count;
    public:
    CardInfo();
    CardInfo(char [],double,char [], char [], int);
    const char * getName();
    double getPrice();
    const char * getSet();
    const char * getType();
    int getCount();
    CardInfo & operator=(CardInfo &otherCard);
    ~CardInfo();
};

struct node
{
    CardInfo card;
    node *next, *prev;
};

class CardCollection
{
    node *head, *tail;
    int count;
    char fileName[STR_SIZE];
    public:
    CardCollection();
    void loadCards();
    void writeCards();
    void addACard();
    bool removeCard();
    bool searchCards();
    void listCards();
    ~CardCollection();
};

#endif
