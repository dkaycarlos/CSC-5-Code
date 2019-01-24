/* 
 * File:   main.cpp
 * Author: Danielle Carlos
 * Created on January 21, 2019, 10:08 AM
 * Purpose:  Simple Blackjack Game v4: String append/Win/Lose Conditions
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
int chkRyl(int, int);    //    Calculates true value of card w/o replacing 
                                    //     identifying values from RNG.
void chkRyl(int, int&, int&);          //Prototype for improved chkRyl
string prntSym (int);          //      Identifies and prints proper symbols for card values
void calcAce (int, int, int&); //      used in calculation when aces are in play.


//Execution Begins Here!
int main(int argc, char** argv) {
    //Set the random number seed
    srand(time(0));
    
    //Dealer/Player Variables
    int option,     //1- Hit, 2 - Stay, 3 - Quit
        dCard1,     //Initial dealer card, shown to player (Range: 2-14)
        dCard2,     //Initial dealer card, hidden till reveal (Range: 2-14)
        dCardT,     //Temp value to hold draws for dealer (Range: 2-14)
        dAceCnt,    // Keeps track of Ace total/ for value calculation
        dealSum,    //Total value of dealer cards (Range: 2-30)
        pCard1,     //Initial player card (Range: 2-14)
        pCard2,     //Initial player card (Range: 2-14)
        pCardT,     //Temp value to hold draws for player (Range: 2-14)
        pAceCnt,    // Keeps track of Ace total /for value calculation
        plyrSum;    //Total value of player's hand (Range: 2-30)
    
    string dCardS, pCardS;   // Strings to keep track of cards/print cards
    
    
    //Set up initial playing field/initial card draws
    dCardS = ""; //Setting to null resets cards for loop
    pCardS = "";
    dealSum = 0;
    plyrSum = 0;
    pAceCnt = 0; //Setting equal to 0 enables reset for loop
    dAceCnt = 0; 
    //Dealer Initial Values
    dCard1 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
    dCard2 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
    
    //Calculate Sum for Dealer's Initial Hand
    chkRyl(dCard1, dAceCnt, dealSum);
    chkRyl(dCard2, dAceCnt, dealSum);
    dCardS = prntSym(dCard1) + prntSym(dCard2); //To be used in dealer reveal phase only
    

    //Player's Initial Values
    pCard1 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
    pCard2 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14

    //Calculate Initial Sum for Player
    chkRyl(pCard1, pAceCnt, plyrSum);
    chkRyl(pCard2, pAceCnt, plyrSum);
    pCardS = prntSym(pCard1) + prntSym (pCard2);
    
    //Reveal  board to player
 
    cout << "Dealer has: " << prntSym(dCard1) << endl;
    cout << "" << endl;
    cout << "Player has: " << pCardS << endl;
    cout << "Player current total value: " << plyrSum << endl;
    cout << "" << endl;
    
    //Initial victory condition check: Natural BlackJack
    if (plyrSum == 21 && dealSum != 21){ 
        cout << "Dealer has: " << dCardS << endl;
        cout << "Player wins!" << endl;
        cout << "" << endl;
    }
    else if (plyrSum == 21 && dealSum == 21){
        cout << "Dealer has: " << dCardS << endl;
        cout << "Round ends in a draw" << endl;
        cout << "" << endl;
    }
    else {
    cout << "If you want to hit, press '1'. Otherwise press any other key to stay" << endl;
    }
 
    //Player Phase: Hit
    
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
//Function which prints correct symbols based on card value
string prntSym (int card){
    switch (card){
        case 2: return "2 ";
        case 3: return "3 ";
        case 4: return "4 ";
        case 5: return "5 ";
        case 6: return "6 ";
        case 7: return "7 ";
        case 8: return "8 ";
        case 9: return "9 ";
        case 10: return "10 ";
        case 11: return "J ";
        case 12: return "Q ";
        case 13: return "K ";
        case 14: return "A ";
    }
    return "";
}
//Function to calculate Ace flexible value post initial phase
void calcAce (int card, int aceCnt, int& cardSum){ //Checked out/working 01/24/19
    int minVal =  0;
    int maxVal = 10;
    for (int val = 1; val < aceCnt; val++){
        minVal++;
        maxVal++;
    }
    if (aceCnt == 1){ //If initial card is an ace or not
       cardSum += maxVal;
    }
    else if (card == 14 && aceCnt > 1){ //if there are two or more aces
        if (maxVal + 11 <= 21){
            cardSum = maxVal + 11;
        }    
        else if (maxVal + 1 <= 21){
            cardSum = maxVal + 1;
        }
        else if (minVal + 11 <= 21){
            cardSum = minVal + 11;
        }
        else if (minVal + 1 <= 21){
            cardSum = minVal + 1;
        }
        else if (maxVal +1 > 21 && minVal + 1 > 21){
            cardSum = minVal + 1; //bust value, the check will catch upon exiting
        }
    }
    else { //If the card is not 14/aceCnt higher than 1
        if (maxVal + cardSum <= 21){
            cardSum += maxVal;
        }
        else if (minVal + cardSum <= 21){
            cardSum += minVal;
        }
        else if (minVal + cardSum > 21){ //bust case
            cardSum += minVal;
        }
    }
}
//Prototype function-chkRyl
void chkRyl(int card, int& aceCnt, int& cardSum){ //Checked out and working 01/24/19
    if (card == 11 || card == 12 || card == 13){ //If J/Q/K is pulled
        cardSum += 10; //already adds the value to the card
    }
    else if (card == 14){
        aceCnt++;
        calcAce(card, aceCnt, cardSum);
        cout << "aceCount: " << aceCnt << endl;
    }
    else
        cardSum += card;
}