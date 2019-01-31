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
void chkRyl(int, int&, int&);          //Calculates true value of "drawn" card
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
    cout << "If you want to hit, press '1'. Otherwise press 2 to stay" << endl;
    cin >> option;
    }
    //Player Phase: Hit
    do{
        if (option == 1){ //If player chooses to hit
             pCardT = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
             chkRyl(pCardT, pAceCnt, plyrSum);
             pCardS += prntSym(pCardT);
             cout << "Player has: " << pCardS << endl;
             cout << "Player's current total value: " << plyrSum << endl;
             if (plyrSum > 21)
                 cout << "Bust! Dealer wins! Player has over 21!" << endl;
             else{ //If player has 21 or less
                 cout << "Press 1 to hit. Else, press 2 to stay." << endl;
                 cin >> option;
             }
        }
    }while (option != 2 && plyrSum < 21);
    if (option == 2 && plyrSum <= 21){
    //Dealer Phase: Hit
        while (dealSum < 16){ //Dealer stops hitting after first instance of 17+
            if (dealSum < 17){ //Only hit if dealer less than 16
                //Reveal Dealers Full Hand
                dCardT = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
                chkRyl(dCardT, dAceCnt, dealSum);
                dCardS += prntSym(dCardT);
                cout << "Dealer has: " << dCardS << endl;
                cout << "Dealer's current total value: " << dealSum << endl;
            }
            else {
                cout << "Dealer has: " << dCardS << endl;
                cout << "Dealer's current total value: " << dealSum << endl;
            }
        }
    }
    //Reveal Dealer's Hand if 17 or Higher
 
    //Compare Hands to determine winner
        
    //Display the outputs

    //Exit stage right or left!
    return 0;
}

//Function implementation begins
//Function to check true value of cards
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
    for (int val = 0; val < aceCnt; val++){
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
