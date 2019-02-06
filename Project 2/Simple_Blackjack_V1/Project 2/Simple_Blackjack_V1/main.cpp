/* 
 * File:   main.cpp
 * Author: Danielle Carlos
 * Created on February 4, 2019, 6:42 PM
 * Purpose: Conversion of MidTerm Blackjack Repeating Code into Functions
 * Version : 1.0
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <cstdlib>  //Random Number Generator
#include <ctime>    //For time function
#include <iomanip> //Output manipulation library
using namespace std;

//User Libraries

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...

//Function Prototypes
int chkVal (int, int, int &, int &, int &, string &);
int handVal (int, int, int &, int &, int, int, int);
void currAdj (int, int, int, int, int, int &);
//Execution Begins Here!
int main(int argc, char** argv) {
    
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Dealer Variables
    int dCard1, //Initial dealer card, 1 card shown to player [Range: 2-14]   
        dCard2, //Second card shown on reveal phase [Range 2-14]
        dCardT, //Temporary dealer value
        dealSum, //Total sum of dealer's combined cards
        dAceCnt, //Dealer's ace count-used to determine aceMin & aceMax
        dAceMin, // 1*aceCnt
        dPreFix, //Fixed value without ace values
        dCurFix, //Current Fixed Value for Dealer
        dCrdVal, //Holds value of cards
        dAceMax; // dAceMin + 10
    string dCardS; // Dealer's symbolic hand
    
    //Player Variables
    int pCard1, pCard2, //Initial player cards [Range: 2-14]
        pCardT,  //Temporary value used to hold pCardValue
        plyrSum, //Total sum of player's cards
        pAceCnt, //Player's ace count-used to determine aceMin & aceMax
        pAceMin, // 1*aceCnt
        pAceMax, // dAceMin + 10
        pCrdVal, //Holds current value of card for Player
        pPreFix, //Fixed value without ace values
        pCurFix; //Current fixed value
    char pChoice, // Holds variable if player wants to hit/stay
           pQuit; //Variable which determines if program exits or repeats
     bool ifQuit;
    float budget; //Holds money earned for player. No condition tied to it
    string pCardS; // Player's symbolic hand
    
    //Initialize or input i.e. set variable values
    budget = 0.0; //Cumulative over multiple games
    //Repetition of game would begin here at initialization
    do{
        cout << fixed << setprecision(2) << showpoint;
        dealSum = dAceCnt = dAceMin = dAceMax = dPreFix = dCurFix = 0;
        plyrSum = pAceCnt = pAceMin = pAceMax = pPreFix = pCurFix = 0;
        dCardS = pCardS = "";

        //Calculation for Dealer's Initial Hand
        dCard1 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
        dCard2 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14

        //Calculation of value for dealer's first card
        dCrdVal = chkVal(dCard1, dealSum, dAceCnt, dAceMin, dAceMax, dCardS);
        //Calculation of dealer's hand value, update fixed values if necessary
        dealSum = handVal(dCard1, dCrdVal, dPreFix, dCurFix, dAceCnt, dAceMin, dAceMax);
        //Ensure spacing between cards
        dCardS += " "; 
        //Display Dealer's Initial Hand
        cout << "Dealer's Current Hand: " << dCardS << endl;
        cout << "Dealer's Current Sum: " << dealSum << endl;

        //Adjust current fixed value if aces in play or not
        currAdj (dAceCnt, dAceMin, dAceMax, dealSum, dPreFix, dCurFix);
        //Calculation of value for dealer's second card
        dCrdVal = chkVal(dCard2, dealSum, dAceCnt, 
                         dAceMin, dAceMax, dCardS);
        //Calculation of dealer's current hand value, adjust fixed values if necessary
        dealSum = handVal(dCard2, dCrdVal, dPreFix, 
                          dCurFix, dAceCnt, dAceMin, dAceMax);
        //Ensures spacing between cards
        dCardS += " "; 
        cout << endl;
    //End of Dealer Initial calculations
    //Begin Player Initial calculations:
        //Calculation for Obtaining Player's Initial Hand
        pCard1 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
        pCard2 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14

        //Calculation of player's first card
        pCrdVal = chkVal(pCard1, plyrSum, pAceCnt, pAceMin, pAceMax, pCardS);
        //Calculate player's current hand, update any fixed values if needed
        plyrSum = handVal(pCard1, pCrdVal, pPreFix, 
                          pCurFix,pAceCnt, pAceMin, pAceMax);
        //Ensures spacing between cards
        pCardS += " ";

        //Adjust current fixed value if aces in play or not
        currAdj (pAceCnt, pAceMin, pAceMax, plyrSum, pPreFix, pCurFix);
        //Switch Case to Determine Value for pCard2:
        pCrdVal = chkVal(pCard2, plyrSum, pAceCnt, pAceMin, pAceMax, pCardS);
        //Determination of pCurFix values in case of Aces:
        plyrSum = handVal(pCard2, pCrdVal, pPreFix, pCurFix, 
                                  pAceCnt, pAceMin, pAceMax);
        //Ensures spacing between cards
        pCardS += " "; 

        //Display of Player's Initial Total:
        cout << "Player's Current Hand: " << pCardS << endl;
        cout << "Player's Total Value: " << plyrSum << endl;
        cout << endl;

        //Win Condition 1: Calculating if Player has Natural BlackJack
        if (plyrSum == 21){
            budget += 3.00;
            cout << "Natural Blackjack! Player has " << plyrSum << "!" << endl;
            cout << "You've earned $3.00!" << endl;
            cout << "Current budget = $" << budget << endl;
            cout <<endl;
        }
        //Hit Phase Begins if Player has no Natural Blackjack
        else{
            cout << "If you would like to hit, type H. "
                    "Press any other key to stay." << endl;
            cin >> pChoice;
            //Player Hit Phase Begins
            if (pChoice == 'H' || pChoice == 'h'){
                do{
                    //"Draw the card"
                    pCardT = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
                    //Calculation of player's fixed value
                    currAdj (pAceCnt, pAceMin, pAceMax, 
                             plyrSum, pPreFix, pCurFix);
                    //Player's drawn card value is determined
                    pCrdVal = chkVal(pCardT, plyrSum, pAceCnt, 
                                     pAceMin, pAceMax, pCardS);
                    //Calculation of player's hand value
                    plyrSum = handVal(pCardT, pCrdVal, pPreFix, 
                                      pCurFix,pAceCnt, pAceMin, pAceMax);
                    //Ensures spacing between cards
                    pCardS += " ";

                    //Calculation of Player's Current Value:
                    cout << "Player's Current Hand: " << pCardS << endl;
                    cout << "Player's Total Value: " << plyrSum << endl;
                    
                    //Bust Check:
                    if (plyrSum > 21){ //21 inclusive, but not automatic win
                        cout << "Bust! Dealer wins! Player's total value is " 
                             << plyrSum << endl;
                        cout << "Current budget = $" << budget << endl;
                        //Make player choice false to end hit phase
                        pChoice = 'x';
                    }
                    else{
                        //Prompt user if they would like to hit or stay
                        cout << "If you would like to hit, type H. "
                                "Press any other key to stay." << endl;
                        cin >> pChoice;
                        //Repeat if they choose to hit
                    }
                } while (pChoice == 'H' || pChoice == 'h');
            //End of do-While Player Phase Loop
            }
            //End of Player Phase - Dealer Phase Begins Conditionally
            //If player's sum is less than 21
            if (plyrSum <= 21){
                cout << endl;
                //Reveal dealer's hand to player
                cout << "Dealer's Current Hand: " << dCardS << endl;
                cout << "Dealer's Total Value: " << dealSum << endl;
                cout << endl;
                
                //If dealer's hand value is less than 17
                while (dealSum < 17){
                   //Dealer draws card
                    dCardT = (rand() % (14 - 2 + 1)) + 2; //Range 2-14;
                    //Adjust fixed value if aces in play or not
                    currAdj (dAceCnt, dAceMin, dAceMax, 
                             dealSum, dPreFix, dCurFix);
                        //Dealer's drawn card value is determined
                        dCrdVal = chkVal(dCardT, dealSum, dAceCnt, 
                                         dAceMin, dAceMax, dCardS);
                        //Dealer's hand is calculated
                        dealSum = handVal(dCardT, dCrdVal, dPreFix, 
                                          dCurFix, dAceCnt, dAceMin, dAceMax);
                        dCardS += " "; //Ensures spacing between cards
                        
                    //If dealer's value is less than 17 hit again
                    //Else
                } //End of While Loop
                
                //Display Dealer's Full Hand/Player's Hand
                cout << "Dealer's Current Hand: " << dCardS << endl;
                cout << "Dealer's Total Value: " << dealSum << endl;
                cout << "Player's Current Hand: " << pCardS << endl;
                cout << "Player's Current Value: " << plyrSum << endl;
                //Bust Check for Dealer:
                if (dealSum > 21){
                    cout << "Bust! Player wins! Dealer's total value is " 
                         << dealSum << endl;
                    //Add Money to Budget
                    budget += 2.00;
                    cout << "You've earned $2.00!" << endl;
                    cout << "Current budget = $" << budget << endl;
                    cout << endl;
                }
                //Dealer Hit Phase Ends-
                //Comparison Phase Begins if player and dealer have not busted
                else{
                  if (plyrSum > dealSum){
                      budget += 1.00;
                      cout << "Player wins! " << plyrSum << " is greater than " 
                           << dealSum << "!" << endl;
                      cout << "You've earned $1.00!"<< endl;
                      cout << "Current budget = $" << budget << endl;
                  }
                  else if (plyrSum < dealSum){
                      cout << "Dealer wins! " << dealSum << " is greater than " 
                           << plyrSum << "!" << endl;
                  }
                  else{ //If plyrSum is not greater or less, it must be equal
                      cout << "Tough cookies, it's a draw. " 
                           << plyrSum << " is equivalent to " 
                           << dealSum << endl;
                      budget += .50;
                      cout << "You've earned $0.50"<< endl;
                      cout << "Current budget = $" << budget << endl;
                  }
                }
            }
        }//End of blackjack round
        //Prompt user to repeat or quit
        cout << endl;
        cout << "Would you like to play again? "
                "Press any other key to continue or Q to quit." << endl;
        cin >> pQuit;
        if (pQuit == 'Q' || pQuit == 'q'){
            ifQuit = true;
        }
        else{
            ifQuit = false;
        }
    } while(ifQuit != true);
    cout << "You've earned $" << budget << " for this session!" << endl;
    //Exit stage right or left!
    return 0;
}

//Auxiliary Functions Begins Here:

void currAdj (int aceCnt, int aceMin, int aceMax, int cardSum, 
                                    int prevFix, int & currFix){
    //If there are aces in play:
    if (aceCnt > 0){
        currFix = cardSum - aceMax;
        if(currFix != prevFix){
            currFix = cardSum - aceMin;
        }
    }
    //Sum value has no flex variables, is fixed
    else {
        currFix = cardSum; //It is set equal to the dPreFix
    }
}

int handVal (int card, int cardVal, int &prevFix, int &currFix, 
                            int aceCnt, int aceMin, int aceMax){
    //If there are aces in play
    if (aceCnt > 0){
        //If there are aces in play
        if (card == 14){
            if (currFix + aceMax <= 21){
                return currFix + aceMax;
            }
            else{
                return currFix + aceMin;
            }
        }
        else if (card != 14){
              currFix += cardVal;
              prevFix = currFix;
            if (currFix + aceMax <= 21){
                return currFix + aceMax;
            }
            else{
                return currFix + aceMin;
            }
        }
    }
    else {
        //If No Aces are in Play
        if (card != 14){
        currFix += cardVal;
        prevFix = currFix;
        return currFix;
        }
        else {
            if (currFix + aceMax <= 21){
                return currFix + aceMax;
            }
            else{
                return currFix + aceMin;
            }
        }
    }
    return 0;
}

int chkVal (int card,int cardSum, int &aceCnt, 
                int &aceMin, int &aceMax, string &cardSym){
    switch(card){ //10 Value Cards Conversion/Symbol Conversion
        case 2: cardSym += '2'; return 2; 
        case 3: cardSym += '3'; return 3;
        case 4: cardSym += '4'; return 4;
        case 5: cardSym += '5'; return 5;
        case 6: cardSym += '6'; return 6;
        case 7: cardSym += '7'; return 7;
        case 8: cardSym += '8'; return 8;
        case 9: cardSym += '9'; return 9;
        case 10: cardSym += 'T'; return 10;  //Case 10-13 = 10
        case 11: cardSym += 'J'; return 10; //Each different symbols:
        case 12: cardSym += 'Q'; return 10;//  T=10, J= Jack, Q= Queen
        case 13: cardSym += 'K'; return 10;//  K = King
        case 14: //Aces
        {
            aceCnt++;
            aceMin = aceCnt;
            aceMax = aceMin + 10;
            cardSym += 'A';
            if (cardSum + aceMax <= 21){
                return aceMax;
            }
            else
                return aceMin;
        }
    default: return card;
}
    return 0;
}