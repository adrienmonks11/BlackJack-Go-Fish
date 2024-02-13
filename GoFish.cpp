
#include "GoFish.h"
int dealer_pairs;
int player_pairs;

GoFish::GoFish(){
    dealer_pairs =0;
    player_pairs =0;

}

void GoFish::print_hand(vector<card> deck){
    for (const auto& card : deck) {
        value converted = (value)card.value;
        std::cout << converted << " of ";
        switch (card.suit) {
            case suit::Hearts:
                std::cout << "Hearts" << std::endl;
                break;
            case suit::Diamonds:
                std::cout << "Diamonds" << std::endl;
                break;
            case suit::Clubs:
                std::cout << "Clubs" << std::endl;
                break;
            case suit::Spades:
                std::cout << "Spades" << std::endl;
                break;
        }
    }
}

void GoFish::show_player_cards(vector<card> cards){
    cout<<"Your cards are:\n";
    print_hand(cards);
}

void GoFish::show_dealer_cards(vector<card> cards){
    cout<<"Dealer cards:\n";
    print_hand(cards);
}

void GoFish::add_player_pairs(vector<card> &pair, int &player_pairs){
    if (pair.size() > 0){
        cout << "The " << pair.at(0).value << " of " << pair.at(0).suit << " and the ";
        cout << pair.at(1).value << " of " << pair.at(1).suit << " were removed as a pair.";
        player_pairs++;
        cout << " Your total number of pairs is now: " << player_pairs << endl;
    }
}

void GoFish::add_dealer_pairs(vector<card> &pair, int &dealer_pairs){
    if (pair.size() > 0){
        cout << "The " << pair.at(0).value << " of " << pair.at(0).suit << " and the ";
        cout << pair.at(1).value << " of " << pair.at(1).suit << " were removed as a pair from the dealers hand.";
        dealer_pairs++;
        cout << " The dealers total number of pairs is now: " << dealer_pairs << endl;
    }
}


void GoFish::find_player_pairs(vector<CardGame::card> &cards) {
    vector<CardGame::card> pair;
    for (int i = 0; i < cards.size(); i++) {
        for (int j = 0; j < cards.size(); j++) {
            if (cards.at(i).value == cards.at(j).value && cards.at(i).suit != cards.at(j).suit) {
                pair.push_back(cards.at(i));
                pair.push_back(cards.at(j));
                cards.erase(cards.begin() + i);
                cards.erase(cards.begin() + j - 1);
                add_player_pairs(pair, player_pairs);
                pair.clear();
            }
        }
    }
}

void GoFish::find_dealer_pairs(vector<CardGame::card> &cards) {
    vector<CardGame::card> pair;
    for (int i = 0; i < cards.size(); i++) {
        for (int j = 0; j < cards.size(); j++) {
            if (cards.at(i).value == cards.at(j).value && cards.at(i).suit != cards.at(j).suit) {
                pair.push_back(cards.at(i));
                pair.push_back(cards.at(j));
                cards.erase(cards.begin() + i);
                cards.erase(cards.begin() + j - 1);
                add_dealer_pairs(pair, dealer_pairs);
                pair.clear();
            }
        }
    }
}

void GoFish::get_turn_dealer(vector<CardGame::card> &player_cards, vector<CardGame::card> &dealer_cards, vector<GoFish::card> &deck) {
    bool found = true;
    if (dealer_cards.size() < 1){
        found = false;
    }
    srand(time(0));
    while(found){
        cout << "The dealer will now pick a card" << endl;
        int choice = rand() % 13 + 1;
        cout << "The dealer has chosen " << choice << endl;
        for (int i = 0; i < player_cards.size(); i++) {
            if (choice == player_cards.at(i).value) {
                dealer_cards.push_back(player_cards.at(i));
                player_cards.erase(player_cards.begin() + i);
                find_dealer_pairs(dealer_cards);
                cout << "Your hand is now: " << endl;
                print_hand(player_cards);
                cout << "Since the dealer found a card, they get to go again." << endl;
                found = true;
                break;
            }
            else{
                found = false;
            }
        }
    }
    if (!found){
        deal_one_card_dealer(deck,dealer_cards);
        find_dealer_pairs(dealer_cards);
    }
}

void GoFish::get_turn_player(vector<CardGame::card> &player_cards, vector<CardGame::card> &dealer_cards, vector<GoFish::card> &deck) {
    bool found = true;
    if (player_cards.size() < 1){
        found = false;
    }
    string input;
    while(found){
        cout << "Please pick a card. Please enter your card choice as a number" << endl;
        cout << "Ace = 1, Jack = 11, Queen = 12, King = 13" << endl;
        int choice = get_int_from_user();
        while (choice < 1 || choice > 13) {
            cout << "Please enter your card choice as a number" << endl;
            cout << "Ace = 1, Jack = 11, Queen = 12, King = 13" << endl;
            choice = get_int_from_user();;
        }
        for (int i = 0; i < dealer_cards.size(); i++) {
            card card = dealer_cards.at(i);
            if (choice == card.value) {
                dealer_cards.erase(dealer_cards.begin() + i);
                player_cards.push_back(card);
                cout << "You found the " << card.value << " of " << card.suit << endl;
                print_hand(player_cards);
                find_player_pairs(player_cards);
                cout << "Since you found a card, you get to go again." << endl;
                found = true;
                break;
            }
            else{
                found = false;
            }
        }
    }
    if (!found){
        cout << "Go Fish!" << endl;
        cout << "Enter any character to draw a card: " << endl;
        getline(cin, input);
        deal_one_card_player(deck,player_cards);
        print_hand(player_cards);
        find_player_pairs(player_cards);
    }
}

void GoFish::play_game() {
    cout<<"Welcome to Go Fish! ";
    GoFish my_game;
    vector<GoFish::card> my_deck =my_game.create_deck();
    my_game.deal_cards(my_deck);
    my_game.show_player_cards(my_game.player_hand);
    find_player_pairs(my_game.player_hand);
    find_dealer_pairs(my_game.dealer_hand);
    cout<<"------------------"<<endl;
    cout << "Your turn first." << endl;
    while (my_deck.size() > 0) {
        get_turn_player(my_game.player_hand, my_game.dealer_hand, my_deck);
        get_turn_dealer(my_game.player_hand, my_game.dealer_hand, my_deck);
    }
    cout << "Since the deck ran out you can no longer go fish. The game is over." << endl;
    if (dealer_pairs > player_pairs){
        cout << "The dealer had more pairs than you and won the game." << endl;
    }
    else{
        cout << "You had more pairs than the dealer and won the game!" << endl;
    }
}