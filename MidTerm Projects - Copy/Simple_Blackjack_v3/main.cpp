/* 
 * File:   main.cpp
 * Author: Danielle Carlos
 * Created on January 19, 2019, 3:50 PM
 * Purpose:  Simple Blackjack Game v3: Implementation of true value calculation.
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <cstdlib>  //Random Number Generator
#include <ctime>    //For time function

using namespace std;

//User Libraries

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...

//Function Prototypes
int chkRyl(int card1, int card2);   //    Calculates true value of card w/o replacing 
                                    //    identifying values from RNG.

//Execution Begins Here!
int main(int argc, char** argv) {
    //Set the random number seed
    srand(time(0));
    
    //Dealer/Player Variables
    int option,     //1- Hit, 2 - Stay, 3 - Quit
        dCard1,     //Initial dealer card, shown to player (Range: 2-14)
        dCard2,     //Initial dealer card, hidden till reveal (Range: 2-14)
        dCardT,     //Temp value to hold draws for dealer (Range: 2-14)
        dealSum,    //Total value of dealer cards (Range: 2-30)
        pCard1,     //Initial player card (Range: 2-14)
        pCard2,     //Initial player card (Range: 2-14)
        pCardT,     //Temp value to hold draws for player (Range: 2-14)
        plyrSum;    //Total value of player's hand (Range: 2-30)
    
    char jackS, queenS, kingS, aceS; // Used to show traditional J/Q/K/A (Range: 11-14)
    
    
    //Set up initial playing field/initial card draws
    jackS = 'J';
    queenS = 'Q';
    kingS = 'K';
    aceS = 'A';
    //Dealer Initial Values
    dCard1 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
    dCard2 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
    dealSum = chkRyl(dCard1, dCard2) + chkRyl(dCard2, dCard1);
    //Player's Initial Values
    pCard1 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
    pCard2 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
    plyrSum = chkRyl(pCard1, pCard2) + chkRyl(pCard2, pCard1);
    
    //Reveal  board to player--Do/While loop begins here
    //  Switch series to output different statements based on if royals are present or not
    switch (dCard1){
        case 11: cout << "Dealer has: " << jackS << endl; break;
        case 12: cout << "Dealer has: " << queenS << endl; break;
        case 13: cout << "Dealer has: " << kingS << endl; break;
        case 14: cout << "Dealer has: " << aceS << endl; break;
        default: cout << "Dealer has: " << dCard1 << endl; break;
    }
    cout << "" << endl;
    switch (pCard1){
        case 11: cout << "Player has: " << jackS << endl; break;
        case 12: cout << "Player has: " << queenS << endl; break;
        case 13: cout << "Player has: " << kingS << endl; break;
        case 14: cout << "Player has: " << aceS << endl; break;
        default: cout << "Player has: " << pCard1 << endl; break;
    }
    switch (pCard2){
        case 11: cout << "Player has: " << jackS << endl; break;
        case 12: cout << "Player has: " << queenS << endl; break;
        case 13: cout << "Player has: " << kingS << endl; break;
        case 14: cout << "Player has: " << aceS << endl; break;
        default: cout << "Player has: " << pCard2 << endl; break;
    }
    cout << "Player current total value: " << plyrSum << endl;
    cout << "" << endl;
    cout << "If you want to hit, press '1'. Otherwise press '2' to stay" << endl;
    //Map inputs -> outputs
    
    //Display the outputs

    //Exit stage right or left!
    return 0;
}
//Function implementation begins
//Function to check true value of cards
chkRyl(int card1, int card2){
    if (card1 == 11 || card1 == 12 || card1 == 13) //if J/Q/K
        return 10;
    else if (card1 ==14){ //If Ace
        if (card2 != 14) //If anything other than dual A
            return 11;
        else //Dual Ace: Initialized to equal 2 to prevent bust. Flex value
            return 1;
    }
    return card1; //If it is not any of the options.
}
