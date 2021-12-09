#include "header.hpp"

CardCollection::CardCollection()
{
    head = nullptr;
    tail = nullptr;
}

const char * CardInfo::getName()
{
    return name;
}

double CardInfo::getPrice()
{
    return price;
}

const char * CardInfo::getSet()
{
    return set;
}

const char * CardInfo::getType()
{
    return type;
}

int CardInfo::getCount()
{
    return count;
}


CardInfo::CardInfo(char tName[],double tPrice,char tSet[],char tType[],int tCount)
{
    int len;
    len = strlen(tName);
    name = new char[len + 1];
    strcpy(name,tName);
    price = tPrice; 
    len = strlen(tSet);
    set = new char[len + 1];
    strcpy(set,tSet);
    len = strlen(tType);
    type = new char[len + 1];
    strcpy(type,tType);
    count = tCount;
}

CardInfo & CardInfo::operator=(CardInfo &otherCard)
{
    if(name != nullptr)
    {
        delete[] name;
    }
    name = new char[strlen(otherCard.name) + 1];
    strcpy(name,otherCard.name);
    price = otherCard.price;
    if(set != nullptr)
    {
        delete[] set;
    }
    set = new char[strlen(otherCard.set) + 1];
    strcpy(set,otherCard.set);
    if(type != nullptr)
    {
        delete[] type;
    }
    type = new char[strlen(otherCard.type) + 1];
    strcpy(type,otherCard.type);
    count = otherCard.count;
    return *this;
}

CardInfo::~CardInfo()
{
    delete[] name;
    delete[] set;
    delete[] type;
}

CardCollection::~CardCollection()
{
    node *cur = head;
    while(head != nullptr)
    {
        head = cur->next;
        delete cur;
        cur = head;
    }
}
void CardCollection::loadCards()
{
    char tName[STR_SIZE], tSet[STR_SIZE], tType[STR_SIZE];
    double tPrice;
    int tCount;
    node *cur, *temp;
    ifstream inFile;
    cout << "What is the name of the file?: ";
    cin.getline(fileName,STR_SIZE,'\n');
    inFile.open(fileName);
    while(!inFile.is_open())
    {
        cout << "Error opening the file. Type \"quit\" to quit." << endl;
        cout << "What is the name of the file?: ";
        cin.getline(fileName,STR_SIZE, '\n');
        if(strcmp(fileName, "quit") == 0)
        {
            cout << "Quiting." << endl;
            break;
        }
        inFile.open(fileName);
    }
     while(!inFile.eof())
     {
         inFile.getline(tName,STR_SIZE,',');
         inFile >> tPrice;
         inFile.ignore();
         inFile.getline(tSet,STR_SIZE,',');
         inFile.getline(tType,STR_SIZE,',');
         inFile >> tCount;
         inFile.ignore();
         inFile.peek();
         CardInfo tempCard(tName,tPrice,tSet,tType,tCount);
         temp = new node;
         temp->next = nullptr;
         temp->prev = nullptr;
         temp->card = tempCard;
         if (head == nullptr)
         {
             head = temp;
             tail = temp;
         }
         else
         {
             if(strcmp(head->card.getName(),tempCard.getName()) > 0)
             {
                 temp->next = head;
                 head->prev = temp;
                 head = temp;
             }
             else
             {
                 cur = head->next;
                 while(cur != nullptr)
                 {
                     if(strcmp(cur->prev->card.getName(),tempCard.getName()) < 0 && strcmp(tempCard.getName(), cur->card.getName()) < 0)
                     {
                         cur->prev->next = temp;
                         temp->prev = cur->prev;
                         cur->prev = temp;
                         temp->next = cur;
                         break;
                     }
                     else
                     {
                         cur = cur->next;
                     }
                 }
                 if(cur == nullptr)
                 {
                     tail->next = temp;
                     temp->prev = tail;
                     tail = temp;
                 }
             }
         }
     }
     inFile.close();
}


void CardCollection::listCards()
{
    node *cur;
    cur = head;
    cout << left << setw(26) << "Name" << setw(9) << "Price";
    cout << setw(24) << "Set" << setw(15) << "Type" << "Count" << endl;
    cout << "------------------------------------------------------------";
    cout << "-----------------" << endl;
    while(cur != nullptr)
    {
        cout << left << setw(26) << cur->card.getName() << setw(9);
        cout << cur->card.getPrice() << setw(24); 
        cout << cur->card.getSet() << setw(15);
        cout << cur->card.getType() << cur->card.getCount() << endl;
        cur = cur->next;
    }
}

bool CardCollection::searchCards()
{
    char search[STR_SIZE];
    bool found = false;
    node *cur;
    cur = head;
    cout << "What is the name of the card you would like to search for? ";
    cin.getline(search,STR_SIZE,'\n');
    while(cur != nullptr)
    {
        if(strcmp(search,cur->card.getName()) == 0)
        {
            cout << "The information on the card " << search << " is as ";
            cout << "follows." << endl;
            cout << "Price $" << cur->card.getPrice() << ", Set: ";
            cout << cur->card.getSet() << ", Type: " << cur->card.getType();
            cout << ", Count: " << cur->card.getCount() << endl;
            found = true;
            break;
        }
        else
        {
            cur = cur->next; 
        }
    }
    return found;
}

void CardCollection::addACard()
{
    char tName[STR_SIZE], tSet[STR_SIZE], tType[STR_SIZE];
    int tCount;
    double tPrice;
    node *cur, *temp;
    temp = new node;
    cout << "What is the name of the card?: ";
    cin.getline(tName,STR_SIZE);
    cout << "What is the price of the card?: $";
    cin >> tPrice;
    while(cin.fail() || tPrice <= 0)
    {
        cin.clear();
        cin.ignore(STR_SIZE,'\n');
        cout << "Input failure. Please enter an amount greater than 0";
        cout << " and in numeric form." << endl;
        cout << "Try again: $";
        cin >> tPrice;
    }
    cin.ignore();
    cout << "What set is the card in?: ";
    cin.getline(tSet,STR_SIZE);
    cout << "What type is the card?: ";
    cin.getline(tType,STR_SIZE);
    cout << "How many copies of the card do you have?: ";
    cin >> tCount;
    while(cin.fail() || tCount < 1)
    {
        cin.clear();
        cin.ignore(STR_SIZE,'\n');
        cout << "Input failure. Please enter a number greater than 1 ";
        cout << "and in numeric form." << endl;
        cout << "Try again: ";
        cin >> tCount;
    }
    cin.ignore();
    CardInfo tempCard(tName,tPrice,tSet,tType,tCount);
    temp->card = tempCard;
    temp->next = nullptr;
    temp->prev = nullptr;
    if (head == nullptr)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        if(strcmp(tempCard.getName(),head->card.getName()) < 0)
        {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
        else
        {
            cur = head->next;
            while(cur != nullptr)
            {
                if(strcmp(cur->prev->card.getName(),tempCard.getName()) < 0 && strcmp(tempCard.getName(), cur->card.getName()) < 0)
                {
                    cur->prev->next = temp;
                    temp->prev = cur->prev;
                    cur->prev = temp;
                    temp->next = cur;
                    break;
                }
                else
                {
                    cur = cur->next;
                }
            }
            if(cur == nullptr)
            {
                tail->next = temp;
                temp->prev = tail;
                tail = temp;
            }
        }
    }
}


void CardCollection::writeCards()
{
    ofstream outFile;
    outFile.open(fileName);
    node *cur;
    cur = head;
    while(cur != nullptr)
    {
        outFile << cur->card.getName() << "," << cur->card.getPrice(); 
        outFile << "," << cur->card.getSet() << "," << cur->card.getType(); 
        outFile << "," << cur->card.getCount() << endl;
        cur = cur->next;
    }
    outFile.close();
}

bool CardCollection::removeCard()
{
    node *cur, *prev;
    bool found = false;
    char search[STR_SIZE];
    cout << "What is the name of the card you would like to delete?: ";
    cin.getline(search,STR_SIZE,'\n');
    if(head != nullptr)
    {
        if(strcmp(search,head->card.getName()) == 0)
        {
            cur = head;
            head = head->next;
            delete cur;
            if(head == nullptr)
            {
                tail = nullptr;
            }
            found = false;
        }
        else
        {
            prev = head;
            cur = head->next;
            while(cur != nullptr)
            {
                if(strcmp(search,cur->card.getName()) == 0)
                {
                    prev->next = cur->next;
                    delete cur;
                    if(prev->next == nullptr)
                    {
                        tail = prev;
                    }
                    found = true;
                    break;
                }
                else
                {
                    prev = cur;
                    cur = cur->next;
                }
            }
        }
    }
    return found;
}

CardInfo::CardInfo()
{
    name = type = set = nullptr;
    price = 0.0;
    count = 0;
}
