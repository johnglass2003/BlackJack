#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <cstdlib>
#include<time.h>
#include<map>
#include <vector>



using namespace std;


class Card {
public:
    //Card member values
    int suit;
    int rank;
    bool revealed;

    Card() {
        //Basic Card constructor
    }

    //Card Constructor with Args
    Card(int s, int r, bool re) {
        suit = s;
        rank = r;
        revealed = re;
    }
};

class Game {
private:
    //Set of all cards already dealt
    set<string> s;
public:
    //Dictionary of all card suits
    map<int, string> suits;
    //Dictionary of all card ranks
    map<int, string> ranks;
    //Player hand
    vector<Card> p;
    //Dealer hand
    vector<Card> d;

    Game() {
        //Basic constructor
    }

    //Deal function
    void Deal(vector<Card>& v, bool re) {
        //Random values for Suit and Rank
        srand(time(nullptr));
        int rank = rand() % 13;
        int suit = rand() % 4;

        while(s.find(to_string(suit) + to_string(rank)) != s.end()) {
            //If the card has already been dealt, randomize suit and rank again
            rank = rand() % 13;
            suit = rand() % 4;
        }
        //Inserts the card suit/rank combination in the set so it does not get re-dealt
        s.insert(to_string(suit) + to_string(rank));
        //Creates a new card instance representing the dealt card and pushes it to the correct player's vector
        Card c = Card(suit, rank, re);
        v.push_back(c);
    }

    void displayHand(vector<Card> v) {
        auto it1 = suits.find(0);
        auto it2 = ranks.find(0);

        //Iterates through the desired vector and prints each card based on it's revealed value
        for (int i = 0; i < v.size(); i++) {
            if (v.at(i).revealed == false)
            {
                cout << "HIDDEN    ";
            }
            else
            {
                it1 = suits.find(v.at(i).suit);
                it2 = ranks.find(v.at(i).rank);
                cout << it2->second << " of " << it1->second << "    ";
            }
        }
        cout << endl;
    }

    void displayCard(vector<Card> v, int c) {
        //Finds the most recently added card and displays it based on it's revealed value
        auto it1 = suits.find(0);
        auto it2 = ranks.find(0);

        if (c < v.size())
        {
            if (v.at(c).revealed == false)
            {
                cout << "HIDDEN    ";
            }
            else
            {
                it1 = suits.find(v.at(c).suit);
                it2 = ranks.find(v.at(c).rank);
                cout << it2->second << " of " << it1->second << "    ";
            }
        }
    }

    bool hasAce(vector<Card> v)
    {
        //Checks the desired player's hand for an Ace
        for (int i = 0; i < v.size(); i++) {
            if (v.at(i).rank == 0)
            {
                return true;
            }
        }
        return false;
    }

    void clearDealt()
    {
        //Clears the Game's set represnting the cards in the deck already dealt
        s.clear();
    }

    int calHand(vector<Card> v) {
        //Calculates the desired player's hand value based on their card's ranks
        int s = 0;
        for (int i = 0; i < v.size(); i++) {
            if (v.at(i).rank == 0)
            {
                s += 11;
            }
            else if (v.at(i).rank <= 9)
            {
                s += v.at(i).rank + 1;
            }
            else if (v.at(i).rank == 13)
            {
                s += 1;
            }
            else
            {
                s += 10;
            }
        }
        return s;
    }
};

int main()
{
    
    //Initializes Game objects
    Game g;
    //Defines the suits and ranks for all the cards in the deck
    g.suits.insert(pair<int, string>(0, "Spades"));
    g.suits.insert(pair<int, string>(1, "Clubs"));
    g.suits.insert(pair<int, string>(2, "Hearts"));
    g.suits.insert(pair<int, string>(3, "Diamonds"));

    g.ranks.insert(pair<int, string>(0, "Ace"));
    g.ranks.insert(pair<int, string>(1, "2"));
    g.ranks.insert(pair<int, string>(2, "3"));
    g.ranks.insert(pair<int, string>(3, "4"));
    g.ranks.insert(pair<int, string>(4, "5"));
    g.ranks.insert(pair<int, string>(5, "6"));
    g.ranks.insert(pair<int, string>(6, "7"));
    g.ranks.insert(pair<int, string>(7, "8"));
    g.ranks.insert(pair<int, string>(8, "9"));
    g.ranks.insert(pair<int, string>(9, "10"));
    g.ranks.insert(pair<int, string>(10, "Jack"));
    g.ranks.insert(pair<int, string>(11, "Queen"));
    g.ranks.insert(pair<int, string>(12, "King"));

    g.ranks.insert(pair<int, string>(13, "1"));

    bool kg = true;
    string userName;
    cout << "Welcome to BlackJack! Please enter your name: ";
    cin >> userName;

    cout << "Goodluck " << userName << endl;
    cout << endl;
    string userInput;
    bool finished = false;
    while (!finished)
    {
        cout << "-------------------------------------------------------------------" << endl;
        g.Deal(g.p, 1);
        g.Deal(g.p, 1);
        g.Deal(g.d, 1);
        g.Deal(g.d, 0);



        cout << "Dealer Hand: " << endl;
        g.displayHand(g.d);
        cout << endl;
        cout << "Your Hand: " << endl;
        g.displayHand(g.p);
        cout << endl;

        if(g.calHand(g.p) == 21)
        {
            //Player has BlackJack
            if (g.calHand(g.d) == 21)
            {
                //Both players got BlackJack
                g.d.at(1).revealed = 1;
                cout << "Tie!" << endl;
            }
            cout << "BlackJack! You Win!" << endl;
        }
        else if (g.calHand(g.d) == 21)
        {
            //Only dealer has BlackJack
            g.d.at(1).revealed = 1;
            cout << "Dealer's Hand: ";
            g.displayHand(g.d);
            cout << "Dealer has BlackJack! You Lose." << endl;
        }
        else
        {
            while (g.calHand(g.p) < 21 && kg)
            {
                //Player can choose to hit up until their hand value exceeds 21 or they stand
                cout << "Hand Value: " << g.calHand(g.p) << endl;
                cout << endl;
                cout << "Would you like to Hit? (Y/N)" << endl;
                cin >> userInput;
                while (userInput != "Y" && userInput != "N")
                {
                    cout << "Please re-enter (Y/N)" << endl;
                    cin >> userInput;
                }
                if (userInput == "Y")
                {
                    //Player Hit
                    g.Deal(g.p, 1);
                    cout << "You drew a: ";
                    g.displayCard(g.p, g.p.size() - 1);
                    cout << endl;
                    cout << endl;
                    if (g.calHand(g.p) > 21)
                    {
                        //If a player busts, checks if their hand has an ace to be converted from an 11 to a 1
                        if (g.hasAce(g.p)) {
                            bool converted = false;
                            for (int i = 0; i < g.p.size(); i++)
                            {
                                if (g.p.at(i).rank == 0 && !converted)
                                {
                                    g.p.at(i).rank = 13;
                                    converted = true;
                                }
                            }
                        }
                        else
                        {
                            kg = false;
                        }
                    }
                }
                else if (userInput == "N")
                {
                    g.d.at(1).revealed = 1;

                    cout << "Dealer Hand: " << endl;
                    g.displayHand(g.d);
                    cout << endl;

                    //Dealer hits until his hand is 17 or over
                    while(g.calHand(g.d) < 17)
                    {
                        g.Deal(g.d, 1);
                        cout << "Dealer drew a: ";
                        g.displayCard(g.d, g.d.size() - 1);
                        cout << endl;
                        cout << endl;
                    }
                    kg = false;
                }
            }

            //First checks if a player has busted

            if (g.calHand(g.p) > 21)
            {
                cout << "Busted! You Lose. Hand value: " << g.calHand(g.p) << endl;
                cout << endl;
            }
            else if (g.calHand(g.d) > 21)
            {
                cout << "Dealer Busted! You Win. Dealer Hand value: " << g.calHand(g.d) << endl;
                cout << endl;
            }
            else 
            {
                //Whoever has a higher hand wins
                if (g.calHand(g.p) > g.calHand(g.d))
                {
                    cout << g.calHand(g.p) << " > " << g.calHand(g.d) << ": You Win!";
                    cout << endl;
                }
                else if (g.calHand(g.p) < g.calHand(g.d))
                {
                    cout << g.calHand(g.p) << " < " << g.calHand(g.d) << ": You Lose!";
                    cout << endl;
                }
                else
                {
                    //Tie game situation
                    cout << g.calHand(g.p) << " = " << g.calHand(g.d) << ": Tie Game!";
                    cout << endl;
                }
            }
        }

        cout << "Play Again? (Y/N)" << endl;
        cin >> userInput;
        while (userInput != "Y" && userInput != "N")
        {
            cout << "Please re-enter (Y/N)" << endl;
            cin >> userInput;
        }
        if (userInput == "Y")
        {
            //Resets the game
            g.d.clear();
            g.p.clear();
            g.clearDealt();
            kg = true;
            continue;
        }
        else if (userInput == "N")
        {
            finished = true;
        }
    }
    cout << "Goodbye and thank you for playing!" << endl;
}