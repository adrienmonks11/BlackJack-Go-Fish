
#ifndef M2OEP_CARDGAME_H
#define M2OEP_CARDGAME_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <sstream>
using namespace std;
class CardGame{
public:
    CardGame()= default;
    //suits for cards
    enum suit{
        Diamonds = 1,
        Hearts = 2,
        Clubs = 3,
        Spades = 4
    };
    //values for cards
    enum value{
        Ace = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven =7, eight = 8,
        nine = 9, ten = 10, Jack = 11, Queen = 12, King = 13
    };
    //card in deck with an integer value and suit
    struct card{
        value value;
        suit suit;
    };

    //overloaded operator for value
    friend ostream& operator<<(ostream& out, value value){
        switch(value){
            case Ace: out<< "Ace"; break;
            case two: out<< 2; break;
            case three: out<< 3; break;
            case four: out<< 4; break;
            case five: out<< 5; break;
            case six: out<< 6; break;
            case seven: out<< 7; break;
            case eight: out<< 8; break;
            case nine: out<< 9; break;
            case ten: out<< 10; break;
            case Jack: out<< "Jack"; break;
            case Queen: out<< "Queen"; break;
            case King: out<< "King"; break;
        }
        return out;
    }

    //overloaded operator for suit
    friend ostream& operator<<(ostream& out, suit suit){
        switch(suit){
            case Diamonds: out<< "Diamonds"; break;
            case Hearts: out<< "Hearts"; break;
            case Clubs: out<< "Clubs"; break;
            case Spades: out<< "Spades"; break;
        }
        return out;
    }
    // overloaded operator for == for cards
    friend bool operator == (card& card1, card& card2){
        if (card1.suit == card2.suit && card1.value == card2.value){
            return true;
        }
        else{
            return false;
        }
    }

    //create deck of cards by adding ace through king of each suit
    vector<card> create_deck(){
        vector<card> deck;
        for(int i = 1; i <= 13;i++){
            deck.push_back({value(i),suit::Diamonds});
            deck.push_back({value(i),suit::Hearts});
            deck.push_back({value(i),suit::Clubs});
            deck.push_back({value(i),suit::Spades});
        }
        //shuffle the deck
        std::shuffle(deck.begin(), deck.end(), std::random_device());
        return deck;
    }
    //used for printing cards in players hands to console
    void print_hand(vector<card>  deck);

    //Prints to console that players hand is being shown and calls print_hand
    void show_player_cards(vector<card> cards) ;

    //Prints to console that dealers hand is being shown and calls print_hand
    void show_dealer_cards(vector<card> cards);

    vector<card> deal_cards(vector<card> deck);

    int get_int_from_user() {
        string input;
        stringstream ss;
        int space;
        int badInput = 0;
        int num;
        cout << "Enter a number: " << endl;
        getline(cin, input);
        // loop analyzes every char to ensure all are digits, and one negative sign is allowed at the begining of the loop
        for (int i = 0; i < input.length(); i++) {
            if (!isdigit(input[i]) or isspace(input[i])) {
                space = 1;
            }
            else {
                space = 0;
            }
            badInput = badInput | space;
        }
        // check for bad input, and repeat if necessary
        while (input == "" or badInput == 1) {
            badInput = 0;
            if (input == "") {
                cout << "You entered nothing, enter a number: " << endl;
                getline(cin, input);
                badInput = 1;
            }
            else {
                for (int i = 0; i < input.length(); i++) {
                    if (!isdigit(input[i]) or isspace(input[i])) {
                        space = 1;
                    }
                    else {
                        space = 0;
                    }
                    badInput = badInput | space;
                }
                if (badInput == 1) {
                    cout << "Invalid input. Enter a number: " << endl;
                    getline(cin, input);
                } else {
                    ss << input;
                    ss >> num;
                    return num;
                }
            }
        }
        ss << input;
        ss >> num;
        return num;
    }
};



#endif //M2OEP_CARDGAME_H
