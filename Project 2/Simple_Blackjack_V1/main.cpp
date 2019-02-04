/* 
 * File:   main.cpp
 * Author: Danielle Carlos
 * Created on February 3, 2019, 11:42 AM
 * Purpose: Conversion of MidTerm Blackjack Repeating Code into Functions
 * Version : 1
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
    
    // Player Variables
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
        dealSum = dAceCnt = dAceMin = dAceMax = dPreFix = dCurFix = 0;
        plyrSum = pAceCnt = pAceMin = pAceMax = pPreFix = pCurFix = 0;
        dCardS = pCardS = "";

        //Calculation for Dealer's Initial Hand
        dCard1 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
        dCard2 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14

        //Calculation of value for dealer's first card
        dCrdVal = chkVal(dCard1, dealSum, dAceCnt, dAceMin, dAceMax, dCardS);
        //Determination of dealer's initial fixed value:
        //Start of potential function
        if (dCard1 != 14){
            dCurFix += dCrdVal;
            dealSum = dCurFix;
        }
        else{
            if (dCurFix + dAceMax <= 21){
                dealSum = dCurFix + dAceMax;
            }
            else{
                dealSum = dCurFix + dAceMin;
            }
        }
        dPreFix = dCurFix; //Updates fixed values
        dCardS += " "; //Ensures spacing between cards
        //End of Potential Function
        
        //Display Dealer's Initial Hand
        cout << "Dealer's Current Hand: " << dCardS << endl;
        cout << "Dealer's Current Sum: " << dealSum << endl;

        //Determination of dCurFix if Ace used or Not: (Potential repeatable function)
        if (dAceCnt > 0){
            dCurFix = dealSum - dAceMax + 1*(dAceCnt - 1);
            if(dCurFix != dPreFix){
                dCurFix = dealSum - dAceMin + 1*(dAceCnt -1);
            }
        }
        else {
            dCurFix = dealSum; //It is set equal to the dPreFix
        }
        //Calculation of value for dealer's second card
        dCrdVal = chkVal(dCard2, dealSum, dAceCnt, dAceMin, dAceMax, dCardS);
        //Determination of dCurFix values:
        if (dCard2 != 14){ //If Non-Ace
            dCurFix += dCrdVal;
            dealSum = dCurFix;
            if (dAceCnt > 0){ //If ace was the first card.
                dealSum = dCurFix + dealSum;
            }
            else{
                dealSum = dCurFix;
            }
        }
        else{ //If Ace
            if (dCurFix + dAceMax <= 21){
                dealSum = dCurFix + dAceMax;
            }
            else{
                dealSum = dCurFix + dAceMin;
            }
        }
        dPreFix = dCurFix; //Updates dPreFix value to be current fixed value
        dCardS += " "; //Ensures spacing between cards
        cout << endl;  

    //Calculation for Player's Initial Hand
        pCard1 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
        pCard2 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14


        //Switch Case to Determine Value for pCard1:
        pCrdVal = chkVal(pCard1, plyrSum, pAceCnt, pAceMin, pAceMax, pCardS);
        //Determination of pPreFix for player
        if (pCard1 != 14){
            pCurFix += pCrdVal;
            plyrSum = pCurFix;
        }
        else{
            if (pCurFix + pAceMax <= 21){
                plyrSum = pCurFix + pAceMax;
            }
            else{
                plyrSum = pPreFix + pAceMin;
            }
        }
        pPreFix = pCurFix;
        pCardS += " "; //Ensures spacing between cards


        //Determination of pCurFix if Aces used or not
        if (pAceCnt > 0){
            pCurFix = plyrSum - pAceMax + 1*(pAceCnt - 1);
            if(pCurFix != pCurFix){
                pCurFix = plyrSum - pAceMin + 1*(pAceCnt -1);
            }
        }
        else {
            pCurFix = plyrSum; //It is set equal to the dPreFix
        }
        //Switch Case to Determine Value for pCard2:
        pCrdVal = chkVal(pCard2, plyrSum, pAceCnt, pAceMin, pAceMax, pCardS);
        //Determination of pCurFix values in case of Aces:
        if (pCard2 != 14){
            pCurFix += pCrdVal;
            pPreFix = pCurFix;
            if (pAceCnt > 0){ //If ace was the first card.
                plyrSum = pCurFix + plyrSum;
            }
            else{
                plyrSum = pCurFix;
            }
        }
        else{
            if (pCurFix + pAceMax <= 21){
                plyrSum = pCurFix + pAceMax;
            }
            else{
                plyrSum = pCurFix + pAceMin;
            }
        }
        pPreFix = pCurFix;
        pCardS += " "; //Ensures spacing between cards

        //Display of Player's Initial Total:
        cout << "Player's Current Hand: " << pCardS << endl;
        cout << "Player's Total Value: " << plyrSum << endl;
        cout << endl;

        //Win Condition 1: Calculating if Player has Natural BlackJack
        if (plyrSum == 21){
            budget += 3.00;
            cout << "Natural Blackjack! Player has " << plyrSum << "!" << endl;
            cout <<endl;
        }
        //Hit Phase Begins if Player has no Natural Blackjack
        else{
            cout << "If you would like to hit, type H. Press any other key to stay." << endl;
            cin >> pChoice;
            //Player Hit Phase Begins
            if (pChoice == 'H' || pChoice == 'h'){
                do{
                    //"Draw the card"
                    pCardT = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
                    //Two Scenarios: Aces in Play or Not
                    if (pAceCnt != 0){
                        //Calculation of fixed value (Value without Aces)
                        pCurFix = plyrSum - pAceMax; //Even with double aces,
                            if (pCurFix != pPreFix){ //Ace values are compensated
                                pCurFix = plyrSum - pAceMin;
                            }
                        //"pCardT value Determination"
                        pCrdVal = chkVal(pCardT, plyrSum, pAceCnt, 
                                         pAceMin, pAceMax, pCardS);
                        //Calculation of "flexible Ace" begins:
                        if (pCardT == 14){ 
                            //Calculate immediately/No Update to pPreFix val
                            if (pCurFix + pAceMax <= 21){ 
                                plyrSum = pCurFix + pAceMax;
                            }
                            else { 
                                plyrSum = pCurFix + pAceMin;
                            }
                        }
                        else{ //Non-Ace Values
                            //updates pPreFix with pCurFix values
                            pCurFix += pCrdVal;
                            if (pCurFix + pAceMax <= 21){
                                plyrSum = pCurFix + pAceMax;
                            }
                            else{
                                plyrSum = pCurFix + pAceMin;
                            }
                        }
                        pPreFix = pCurFix;
                        pCardS += " "; //Ensures spacing between cards
                        //Calculation of Player's Current Value:
                        cout << "Player's Current Hand: " << pCardS << endl;
                        cout << "Player's Total Value: " << plyrSum << endl;
                    }
                    //Potentially could be superfluous code.
                    else { //Scenario 2: Aces not In Play
                        //"pCardT value Determination"
                        pCrdVal = chkVal(pCardT, plyrSum, pAceCnt, 
                                         pAceMin, pAceMax, pCardS);
                    //Calculation of pCurFixd
                        if (pCardT == 14){ //Calculate immediately/No Update to pPreFix val
                            if (pCurFix + pAceMax <= 21){ //If highest ace val doesn't bust
                                plyrSum = pCurFix + pAceMax;
                            }
                            else { //Else it can only be one other value.
                                plyrSum = pCurFix + pAceMin;
                            }
                        }
                        else{ //Non-Ace Values--updates pPreFix with pCurFix values
                            pCurFix += pCrdVal;
                            if (pCurFix + pAceMax <= 21){
                                plyrSum = pCurFix + pAceMax;
                            }
                            else{
                                plyrSum = pCurFix + pAceMin;
                            }
                        }
                    pPreFix = pCurFix;
                    pCardS += " "; //Ensures spacing between cards
                    //Display of Player's Current Value:
                    cout << "Player's Current Hand: " << pCardS << endl;
                    cout << "Player's Total Value: " << plyrSum << endl;
                }
                    //Potential Superfluous Code
                //Bust Check:
                if (plyrSum > 21){ //21 inclusive, but not automatic win
                    cout << "Bust! Dealer wins! Player's total value is " << plyrSum << endl;
                    pChoice = 'x';
                }
                else{
                    cout << "If you would like to hit, type H. Press any other key to stay." << endl;
                    cin >> pChoice;
                    }
                } while (pChoice == 'H' || pChoice == 'h');
            //End of do-While Player Phase Loop
            } //End of Player Phase - Dealer Phase Begins Here Conditionally
            //Reveal Dealer's Hand and Current Sum
            if (plyrSum <= 21){
                cout << endl;
                cout << "Dealer's Current Hand: " << dCardS << endl;
                cout << "Dealer's Total Value: " << dealSum << endl;
                cout << endl;

                while (dealSum < 17){
                   //Dealer's Draw's Card:
                    dCardT = (rand() % (14 - 2 + 1)) + 2; //Range 2-14;
                    //Two Scenarios: Aces in Play or Not
                    if (dAceCnt != 0){
                        //Calculation of fixed value (Value without Aces)
                        dCurFix = dealSum - dAceMax; //Even with double aces,
                            if (dCurFix != dPreFix){ //Ace values are compensated
                                dCurFix = dealSum - dAceMin;
                            }
                        //"dCardT value Determination"
                        dCrdVal = chkVal(dCardT, dealSum, dAceCnt, 
                                         dAceMin, dAceMax, dCardS);
                        //Calculation of "flexible Ace" begins:
                        if (dCardT == 14){ //Calculate immediately/No Update to dPreFix val
                            if (dCurFix + dAceMax <= 21){ //If highest ace val doesn't bust
                                dealSum = dCurFix + dAceMax;
                            }
                            else { //Else it can only be one other value.
                                dealSum = dCurFix + dAceMin;
                            }
                        }
                        else{ //Non-Ace Values--updates dPreFix with dCurFix values
                            dCurFix += dCrdVal;
                            if (dCurFix + dAceMax <= 21){
                                dealSum = dCurFix + dAceMax;
                            }
                            else{
                                dealSum = dCurFix + dAceMin;
                            }
                        }
                        dPreFix = dCurFix;
                        dCardS += " "; //Ensures spacing between cards
                    }
                    else { //Scenario 2: Aces not In Play
                        //"dCardT value Determination"
                        dCrdVal = chkVal(dCardT, dealSum, dAceCnt, 
                                         dAceMin, dAceMax, dCardS);
                    //Calculation of dCurFixd
                        if (dCardT == 14){ //Calculate immediately/No Update to dCurFix val
                            if (dCurFix + dAceMax <= 21){ //If highest ace val doesn't bust
                                dealSum = dCurFix + dAceMax;
                            }
                            else { //Else it can only be one other value.
                                dealSum = dCurFix + dAceMin;
                            }
                        }
                        else{ //Non-Ace Values--updates dCurFix with dCurFix values
                            dCurFix += dCrdVal;
                            if (dCurFix + dAceMax <= 21){
                                dealSum = dCurFix + dAceMax;
                            }
                            else{
                                dealSum = dCurFix + dAceMin;
                            }
                        }
                    dCurFix = dCurFix;
                    dCardS += " "; //Ensures spacing between cards
                    }
                } //End of While Loop
                //Display Dealer's Full Hand:
                cout << "Dealer's Current Hand: " << dCardS << endl;
                cout << "Dealer's Total Value: " << dealSum << endl;
                //Bust Check:
                if (dealSum > 21){
                    cout << "Bust! Player wins! Dealer's total value is " << dealSum << endl;
                }
                //Dealer Hit Phase Ends-
                //Comparison Phase Begins IFF dealSum and plyrSum are less than or equal to 21
                else{
                    cout << fixed << setprecision(2) << showpoint;
                  if (plyrSum > dealSum){
                      budget += 1.00;
                      cout << "Player wins! " << plyrSum << " is greater than " << dealSum << "!" << endl;
                      cout << "You've earned $" << budget << endl;
                  }
                  else if (plyrSum < dealSum){
                      cout << "Dealer wins! " << dealSum << " is greater than " << plyrSum << "!" << endl;
                  }
                  else{ //If plyrSum is not greater or less, it must be equal
                      cout << "Tough cookies, it's a draw. " << plyrSum << " is equivalent to " << dealSum << endl;
                      budget += .50;
                      cout << "You've earned $" << budget << endl;
                  }
                }
            }
        }//end of else for player option/end of game--Natural Blackjack skips beyond here
        //Prompt user to repeat or quit
        cout << endl;
        cout << "Would you like to play again? Press any other key to continue or Q to quit." << endl;
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

int chkVal (int card,int cardSum, int &aceCnt, int &aceMin, int &aceMax, string &cardSym){
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