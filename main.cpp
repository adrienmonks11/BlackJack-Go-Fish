#include "blackjack.h"
#include "GoFish.h"
using namespace std;
int main(){
    while (true) {
        string input;
        cout<<"Enter g for GoFish, b for BlackJack, or e to exit: ";
        getline(cin,input);
        while (input != "g" && input != "b" && input != "e" && input != "G" && input != "B" && input != "E") {
            cout << "Invalid input, enter g for GoFish, b for BlackJack, or e to exit: ";
            getline(cin, input);
        }
        if (input == "b" or input == "B") {
            BlackJack game;
            game.play_game();
        } else if (input == "g" or input == "G") {
            GoFish fish;
            fish.play_game();
        } else {
            return 0;
        }
    }
}
