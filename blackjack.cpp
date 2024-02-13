#include <iostream>
#include <vector>
#include <algorithm>
#include "blackjack.h"
#include <fstream>
#include <unistd.h>
using namespace std;

BlackJack::BlackJack() {
}
bool game_over = false;

void BlackJack::print_hand(vector<card> deck){
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

void BlackJack::show_player_cards(vector<card> cards){
    cout<<"Your cards are:\n";
    print_hand(cards);
    cout<<"Dealer cards are hidden.\n";
}

void BlackJack::show_dealer_cards(vector<card> cards){
    cout<<"Dealer cards:\n";
    print_hand(cards);
}

int BlackJack::get_total(vector<card> deck){
    int player_total =0;
    vector<int> player_values;
    for (const auto& card : deck) {
        player_values.push_back(card.value);
    }
    sort(player_values.begin(),player_values.end(),greater<int>());
    for(int i= 0; i < player_values.size();i++) {
        if (player_values[i] == 1) {
            if (player_total >= 11) {
                player_total += 1;
            } else {
                player_total += 11;
            }
        } else if (player_values[i] > 10) {
            player_total += 10;
        } else {
            player_total += player_values[i];
        }
    }
    return player_total;

}
int BlackJack::win(){
    string resultsFile = "results.txt";
    string line;
    string test;
    char l;
    char t;
    char a;
    int wins;
    ofstream outFile;
    ifstream inFile("results.txt");
    int i = 0;
    while (getline(inFile, line)){
        if(i == 0){
            l = line[8];
        }
        if(i == 1){
            a = line[6];
            wins = (a - '0') + 1;
        }
        if(i == 2){
            t = line[6];
        }
        i++;
    }
    outFile.open(resultsFile, ios_base::out);
    outFile << "Losses: " << l << "\n";
    outFile << "Wins: " << wins << "\n";
    outFile << "Ties: " << t;
    outFile.close();
    return 0;
}

int BlackJack::lose(){
    string resultsFile = "results.txt";
    string line;
    string test;
    char w;
    char t;
    char a;
    int losses;
    ofstream outFile;
    ifstream inFile("results.txt");
    int i = 0;
    while (getline(inFile, line)){
        if(i == 0){
            a = line[8];
            losses = (a - '0') + 1;
        }
        if(i == 1){
            w = line[6];
        }
        if(i == 2){
            t = line[6];
        }
        i++;
    }
    outFile.open(resultsFile, ios_base::out);
    outFile << "Losses: " << losses << "\n";
    outFile << "Wins: " << w << "\n";
    outFile << "Ties: " << t;
    outFile.close();
    return 0;
}

int BlackJack::tie(){
    string resultsFile = "results.txt";
    string line;
    string test;
    char w;
    char l;
    char a;
    int ties;
    ofstream outFile;
    ifstream inFile("results.txt");
    int i = 0;
    while (getline(inFile, line)){
        if(i == 0){
            l = line[8];
        }
        if(i == 1){
            w = line[6];
        }
        if(i == 2){
            a = line[6];
            ties = (a - '0') + 1;
        }
        i++;
    }
    cout << a << endl;
    outFile.open(resultsFile, ios_base::out);
    outFile << "Losses: " << l << "\n";
    outFile << "Wins: " << w << "\n";
    outFile << "Ties: " << ties;
    outFile.close();
    return 0;
}
void BlackJack::play_game(){
    cout<<"Welcome to BlackJack! This a normal game of blackjack but without splitting hands, as there are no bets involved.";
    cout<<"\nEach run of the program is one hand of blackjack.";
    cout<<"\nEnter any character to start game: ";
    BlackJack my_game;
    string input;
    getline(cin,input);
    //create new deck
    vector<BlackJack::card> my_deck = my_game.create_deck();
    //deal cards and show player hand
    my_deck = my_game.deal_cards(my_deck);
    my_game.show_player_cards(my_game.player_hand);

    char player_choice = ' ';
    std::size_t found_char;
    //loops until valid input is entered (s or h)
    while(player_choice!='s'&& player_choice!='S'){
        cin.clear();
        cout<<"\nEnter h for hit, s for stand, or r to reset the results document";
        getline(cin,input);
        found_char = input.find_first_not_of("hsHSrR");
        if(input==""){
            cout<<"No input. Enter h for hit, s for stand, or r to reset the results document: ";
        }
        else if(input.size()>1){
            cout<<"Invalid input. Enter h for hit, s for stand, or r to reset the results document: ";
        }
        else if(isspace(input.at(0))){
            cout<<"No input. Enter h for hit, s for stand, or r to reset the results document: ";
        }
        else{
            if(found_char!=std::string::npos){
                cout<<"Invalid input. Enter h for hit, s for stand, or r to reset the results document: ";
            }
            else{
                player_choice= input[0];
                //if player chooses hit
                if(player_choice=='h'||player_choice=='H'){
                    my_deck = my_game.player_hit(my_deck);
                    my_game.show_player_cards(my_game.player_hand);
                    int player_total = my_game.get_total(my_game.player_hand);

                    //check if player has busted (gone over 21)
                    if(player_total>21){
                        cout<<"Your total is " <<player_total<<"\n";
                        cout<<"You lose:(" << endl;
                        lose();

                        return;
                    }
                    //check if player has auto-won by getting 21
                    if(player_total==21){
                        cout<<"Your total is " <<player_total<<"\n";
                        cout<<"You win!"<< endl;
                        win();

                        return;
                    }
                    if(player_total<21){
                        cout<<"Your total is " <<player_total<<"\n";
                    }
                }
                    //player chooses stand, their turn is over
                else if (player_choice=='s'||player_choice=='S'){
                    int player_total = my_game.get_total(my_game.player_hand);
                    cout<<"Your total is " <<player_total<<"\n\n";
                    cout<<"Dealer turn"<<"\n";
                    my_game.show_dealer_cards(my_game.dealer_hand);
                    int dealer_total = my_game.get_total(my_game.dealer_hand);

                    //repeatedly hit until dealer total is 17 or greater
                    while(dealer_total<17){
                        cout<<"\nDealer hit\n\n";
                        sleep(1);
                        my_deck= my_game.dealer_hit(my_deck);
                        my_game.show_dealer_cards(my_game.dealer_hand);
                        dealer_total = my_game.get_total(my_game.dealer_hand);
                    }
                    //check if dealer has busted
                    if(dealer_total>21){
                        cout<<"Dealer has "<<dealer_total<<", You win!" << endl;
                        win();

                        return;
                    }
                        //if dealer wins
                    else if(dealer_total>player_total){
                        cout<<"Dealer has "<<dealer_total;
                        cout<<", You lose:("<< endl;
                        lose();

                        return;
                    }
                        //if user wins
                    else if(dealer_total<player_total){
                        cout<<"Dealer has "<<dealer_total;
                        cout<<", You win!"<< endl;
                        win();

                        return;
                    }
                        //if tie
                    else{
                        cout<<"Dealer has "<<dealer_total;
                        cout<<", Its a tie!"<< endl;
                        tie();

                        return;
                    }
                }
                else{
                    string resultsFile = "results.txt";
                    fstream outFile;
                    outFile.open(resultsFile, ios_base::out);
                    outFile << "Losses: 0" << "\n";
                    outFile << "Wins: 0" << "\n";
                    outFile << "Ties: 0";
                    outFile.close();
                    cout << "Results.txt has been reset." << endl;
                }
            }
        }
    }
}