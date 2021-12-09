// Eric Cisco
//cs 162
//sources none 
// Project4
#include "header.hpp"

int main()
{
    CardCollection myCards;
    char option;
    bool success;
    cout << fixed << showpoint << setprecision(2);
    cout << "Welcome to the magic card collection program. " << endl;
    myCards.loadCards();
    myCards.listCards();
    do
    {
        cout << "What would you like to do? (S)earch for a card,";
        cout << "(A)dd a card,(R)emove a card,  (L)ist all cards,";
        cout << " or (Q)uit? ";
        cin.get(option);
        cin.ignore();
        switch(option)
        {
            case 'S':
                success = myCards.searchCards();
                if(success)
                {
                    cout << "Card found!" << endl;
                }
                else
                {
                    cout << "Card not in database." << endl;
                }
                break;
            case 'A':
                myCards.addACard();
                break;
            case 'R':
                success = myCards.removeCard();
                if(success)
                {
                    cout << "Card was removed." << endl;
                }
                else
                {
                    cout << "Card could not be found." << endl;
                }
                break;
            case 'L':
                myCards.listCards();
                break;
            case 'Q':
                cout << "Thank you come again!!!" << endl;
                break;
            default:
                cout << "not a valid choice." << endl;
        }
    }
    while(option != 'Q');
    myCards.writeCards();
    return 0;
}
