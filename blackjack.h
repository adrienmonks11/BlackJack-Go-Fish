#ifndef M2OEP_blackjack_H
#define M2OEP_blackjack_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "CardGame.h"
using namespace std;
class BlackJack: public CardGame{
public:
    BlackJack();
    int win();
    int lose();
    int tie();

    //dealer and player hands
    vector<card> dealer_hand;
    vector<card> player_hand;

    //used for printing cards in players hands to console
    void print_hand(vector<card> deck);

    //Prints to console that players hand is being shown and calls print_hand
    void show_player_cards(vector<card> cards);

    //Prints to console that dealers hand is being shown and calls print_hand
    void show_dealer_cards(vector<card> cards);

    //Deals cards to user and dealer by alternating off the top(front) of the deck
    vector<card> deal_cards(vector<card> deck){
        player_hand.push_back(deck[0]);
        deck.erase(deck.begin());
        dealer_hand.push_back(deck[0]);
        deck.erase(deck.begin());
        player_hand.push_back(deck[0]);
        deck.erase(deck.begin());
        dealer_hand.push_back(deck[0]);
        deck.erase(deck.begin());
        return deck;
    }

    //adds a card to the users hand when they choose hit
    vector<card> player_hit(vector<card> deck){
        player_hand.push_back(deck[0]);
        deck.erase(deck.begin());
        return deck;
    }

    //adds a card to the dealers hand, called whenever the dealer's total is less than 17
    vector<card> dealer_hit(vector<card> deck){
        dealer_hand.push_back(deck[0]);
        deck.erase(deck.begin());
        return deck;
    }

    //returns the sum of a players cards and checks to see if and Ace should be 1 or 11
    int get_total(vector<card> deck);

    //Used to create a loop to play the game
    void play_game();

};
#endif
