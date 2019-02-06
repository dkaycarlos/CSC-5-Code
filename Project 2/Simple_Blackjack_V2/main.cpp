/* 
 * File:   main.cpp
 * Author: Danielle Carlos
 * Created on February 5, 2019, 8:02 PM
 * Purpose: Implementation of Vectors/Bubble Sort/Selection Sort/Linear Search
 *          Adjustment of calculation functions necessary on change to vectors
 * Version : 2.0
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <cstdlib>  //Random Number Generator
#include <ctime>    //For time function
#include <iomanip> //Output manipulation library
#include <vector>  //Vector Library
using namespace std;

//User Libraries

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...

//Function Prototypes
void draw (vector<int>&);
int calcVal(vector<int>);
string prntD(vector<int>);
string prntP(vector<int>);
char prntSym(int);

//Execution Begins Here!
int main(int argc, char** argv) {
    
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Dealer Variables
    int dealSum; //Total sum of dealer's combined cards
    vector<int>dHand; //Vector to hold dealer's cards.
    string dCardS; // Dealer's symbolic hand
    
    //Player Variables
    int  plyrSum; //Total sum of player's cards
    char pChoice, //Holds variable if player wants to hit/stay
           pQuit; //Variable which determines if program exits or repeats
     bool ifQuit; //Returns True/False based on pQuit
    float budget; //Holds money earned for player. No condition tied to it
    string pCardS; // Player's symbolic hand
    vector<int>pHand; //Vector to hold player's cards
    
    //Initialize or input i.e. set variable values
    budget = 0.0; //Cumulative over multiple games
    //Game begins here:
    do{
        //Game initializes/Board Resets
        cout << fixed << setprecision(2) << showpoint;
        dealSum = plyrSum = 0;
        dCardS = pCardS = "";
        dHand.clear(), pHand.clear();
        
        //Calculation for Dealer's Initial Hand
        //Draw initial card for dealer
        draw(dHand);
        //Obtain initial value
        dealSum = calcVal(dHand);
        dCardS = prntD(dHand);
        
        //Display Dealer's Initial Card    
        cout << "Dealer's Current Hand: " << dCardS << endl;
        cout << "Dealer's Current Sum: " << dealSum << endl;
        cout << endl;
        //Dealer Draws Second Card
        draw(dHand);
        dealSum = calcVal(dHand);
    //End of Dealer Initial calculations
        
    //Begin Player Initial calculations:
        //Player draws two initial cards
        for (int i = 0; i < 2; i++){
            draw(pHand);
        }
        //Calculate the value of the player's hand
        plyrSum = calcVal(pHand);
        pCardS = prntP(pHand);
        
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
                    draw(pHand);
                    //Calculation of player's current hand
                    plyrSum = calcVal(pHand);
                    pCardS = prntP(pHand);
                    //Ensures spacing between cards

                    //Display Player's Current Value:
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
                dCardS = prntD(dHand);
                cout << "Dealer's Current Hand: " << dCardS << endl;
                cout << "Dealer's Total Value: " << dealSum << endl;
                cout << endl;
                
                //If dealer's hand value is less than 17
                while (dealSum < 17){
                   //Dealer draws card
                    draw(dHand);
                   //Dealer's hand is calculated
                    dealSum = calcVal(dHand);
                    //If dealer's value is less than 17 hit again
                    //Else
                } //End of While Loop
                
                //Display Dealer's Full Hand/Player's Hand
                dCardS = prntD(dHand);
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

char prntSym(int card){
        switch(card){ //Symbol Conversion
        case 2: return '2';  
        case 3: return '3'; 
        case 4: return '4'; 
        case 5: return '5'; 
        case 6: return '6'; 
        case 7: return '7'; 
        case 8: return '8'; 
        case 9: return '9'; 
        case 10: return 'T'; 
        case 11: return 'J';
        case 12: return 'Q';  
        case 13: return 'K'; 
        case 14: return 'A';
    default: break;
    }
}

//Prints dealer's current hand in reverse order: A-2/BubbleSort
string prntD(vector<int> hand){
        string sHand = "";
    for (int indx = 0; indx < hand.size(); indx++){
        for (int adj = indx + 1; adj < hand.size(); adj++){
            if (hand[indx] < hand[adj]){
                int temp = hand[indx];
                hand[indx] = hand[adj];
                hand[adj] = temp;
            }
        }
    }
    //After cards have been sorted
    for (int indx = 0; indx < hand.size(); indx++){
        sHand += prntSym(hand[indx]);
        sHand += " ";
    }
    return sHand;
}
//Prints Player's Current Hand in order: 2-A/Selection Sort
string prntP(vector<int> hand){
    string sHand; //Variable to return sorted hand
    for (int i = 0; i < hand.size(); i++){
            int max = hand[i];
            int indx = i; 
        for (int adj = i + 1; adj < hand.size(); adj++){
            if (hand[adj] < max){
                max = hand[adj];
                indx = adj;
            }
        }
            int temp = hand[i];
            hand[i] = hand[indx];
            hand[indx] = temp;
    }
    //After cards have been sorted print
    for (int indx = 0; indx < hand.size(); indx++){
        sHand += prntSym(hand[indx]);
        sHand += " ";
    }
    return sHand;
}
//Calculates value of hand when called:
int calcVal(vector<int> hand){
    int currCrd, currFix, aceCnt, aceMax;
    currCrd = currFix = aceCnt = 0;
    //Obtain raw pulls from hand--Calculate fixed value
    for (int indx = 0; indx < hand.size(); indx++){
        currCrd = hand[indx];
        if (currCrd != 14){ //If J/Q/K
            if (currCrd == 11 || currCrd == 12 || currCrd == 13){
                currFix += 10;
            }
            else { //Non-Royal Cards = face value
                currFix += currCrd;
            }
        }
    }
    //Search hand for any aces: Linear Search Example
    for (int indx = 0; indx < hand.size(); indx++){
        if (hand[indx] == 14){
            aceCnt++;
        }
    }
    //Calculate ace value(if any are in hand)
    aceMax = aceCnt + 10;
    if (aceCnt > 0){
        if (currFix + aceMax <= 21){
            return currFix + aceMax;
        }
        else {
            return currFix + aceCnt;
        }
    }
    else return currFix;
}

//Draw function--Draws Cards, Adds to Vector
void draw (vector<int> &hand){
    //Draws the Card-Keeps Raw Values
    int card = (rand() % (14 - 2 + 1)) + 2;
    hand.push_back(card);
}



