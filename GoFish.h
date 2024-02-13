#ifndef M2OEP_GOFISH_H
#define M2OEP_GOFISH_H
#include "CardGame.h"

class GoFish: public CardGame{
public:
    GoFish();

    //dealer and player hands
    vector<card> dealer_hand;
    vector<card> player_hand;
    vector<card> remaining_cards;

    //used for printing cards in players hands to console
    void print_hand(vector<card> deck);

    //Prints to console that players hand is being shown and calls print_hand
    void show_player_cards(vector<card> cards);

    //Prints to console that dealers hand is being shown and calls print_hand
    void show_dealer_cards(vector<card> cards);

    //Finds pairs in player hand
    void find_player_pairs(vector<CardGame::card> &cards);

    //Finds pairs in dealer hand
    void find_dealer_pairs(vector<CardGame::card> &cards);

    //Updates the total number of player pairs
    void add_player_pairs(vector<card> &pair, int &player_pairs);

    //Updates the total number of dealer pairs
    void add_dealer_pairs(vector<card> &pair, int &dealer_pairs);

    //Gets the choice of the player, determines if they found a match or need to gofish
    void get_turn_player(vector<CardGame::card> &player_cards, vector<CardGame::card> &dealer_cards, vector<GoFish::card> &deck);

    //Gets the choice of the dealer, determines if they found a match or need to gofish
    void get_turn_dealer(vector<CardGame::card> &player_cards, vector<CardGame::card> &dealer_cards, vector<GoFish::card> &deck);

    //Deals cards to user and dealer by alternating off the top(front) of the deck
    void deal_cards(vector<card> &deck){
        for(int i = 0; i < 7;i++){
            player_hand.push_back(deck[0]);
            deck.erase(deck.begin());
            dealer_hand.push_back(deck[0]);
            deck.erase(deck.begin());
        }
    }

    //Deals top card off deck to player, used when a match is not found and the player "gofishes"
    vector<card> deal_one_card_player(vector<card> &deck, vector<card> &player_cards){
        player_cards.push_back(deck[0]);
        cout << "You drew the " << deck[0].value << " of " << deck[0].suit << endl;
        deck.erase(deck.begin());
        return deck;
    }
    //Deals top card off deck to dealer, used when a match is not found and the dealer "gofishes"
    vector<card> deal_one_card_dealer(vector<card> &deck, vector<card> &dealer_cards){
        cout << "The dealer did not guess a card you have, and is going fish." << endl;
        dealer_cards.push_back(deck[0]);
        deck.erase(deck.begin());
        return deck;
    }

    //Used to create a loop to play the game
    void play_game();

};

#endif
