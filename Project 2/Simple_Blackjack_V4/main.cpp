/* 
 * File:   main.cpp
 * Author: Danielle Carlos
 * Created on February 8, 2019, 12:03 PM
 * Purpose: Implementation of Menu/Stats/Sorts
 * Version : 4.0
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <cstdlib>  //Random Number Generator
#include <ctime>    //For time function
#include <iomanip> //Output manipulation library
#include <vector>  //Vector Library
#include <fstream> //Input/Output Files
using namespace std;

//User Libraries

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...
const int COLS = 2;
//Function Prototypes
void draw (vector<int>&,int[], int, int &);
int calcVal(vector<int>, char [][COLS]);
string prntRev(vector<int>, char[][COLS]);
string prntOrd(vector<int>, char[][COLS]);
bool linSrch(int[], int, int);
void suitFill(char [][COLS], int);
void valFill (char [][COLS], int);
void shuff(int [], int &, int);
string prntHnd(vector<int>, char[][COLS]);
void write(char[], int, int, int, int, int, float, string);
void statDisp(char[]);
void menu(char[], char &);

//Execution Begins Here!
int main(int argc, char** argv) {
    
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //General Game Variables
    const int NCARDS = 53;
    char deck[NCARDS][COLS]; //52 Card Deck with internal values
    int discard[NCARDS]; //Discard Pile/Cards already used in play
    int crdCnt;         //Used to determine when to shuffle
    
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
    string pName;
    
    //Variables cumulative over multiple games for stats:
    int rnds, wins, loss, draws, shuffle;
    
    //Initialize 2D Array and Discard Array/Cumulative variables
    budget = 0.0;
    //Note: crdCnt is for shuffle trigger, rest is for stats
    char fn[] = "stats.dat";
    crdCnt = rnds = wins = loss = draws = 0;
    discard[NCARDS] = {};
    suitFill(deck, NCARDS);
    valFill (deck, NCARDS);
        
    //Game begins here:
    cout << "Welcome to Simple Blackjack! Please enter your name: " << endl;
    cin >> pName;
    do{
        //Game initializes/Board Resets
        cout << fixed << setprecision(2) << showpoint;
        dealSum = plyrSum = 0;
        dCardS = pCardS = "";
        dHand.clear(), pHand.clear();
        
        //Calculation for Dealer's Initial Hand
        //Draw initial card for dealer
        draw(dHand, discard, NCARDS, crdCnt);
        //Obtain initial value
        dealSum = calcVal(dHand, deck);
        dCardS = prntHnd(dHand, deck);
        
        //Display Dealer's Initial Card    
        cout << "Dealer's Current Hand: " << dCardS << endl;
        cout << "Dealer's Current Sum: " << dealSum << endl;
        cout << endl;
        //Dealer Draws Second Card
        draw(dHand,discard, NCARDS, crdCnt);
        dealSum = calcVal(dHand, deck);
    //End of Dealer Initial calculations
        
    //Begin Player Initial calculations:
        //Player draws two initial cards
        for (int i = 0; i < 2; i++){
            draw(pHand, discard, NCARDS, crdCnt);
        }
        //Calculate the value of the player's hand
        plyrSum = calcVal(pHand, deck);
        pCardS = prntHnd(pHand, deck);
        
        //Display of Player's Initial Total:
        cout << "Player's Current Hand: " << pCardS << endl;
        cout << "Player's Total Value: " << plyrSum << endl;
        cout << endl;

        //Win Condition 1: Calculating if Player has Natural BlackJack
        if (plyrSum == 21){
            budget += 3.00;
            wins++;
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
                    draw(pHand, discard, NCARDS, crdCnt);
                    //Calculation of player's current hand
                    plyrSum = calcVal(pHand, deck);
                    pCardS = prntHnd(pHand, deck);
                    //Ensures spacing between cards

                    //Display Player's Current Value:
                    cout << "Player's Current Hand: " << pCardS << endl;
                    cout << "Player's Total Value: " << plyrSum << endl;
                    
                    //Bust Check:
                    if (plyrSum > 21){ //21 inclusive, but not automatic win
                        cout << "Bust! Dealer wins! Player's total value is " 
                             << plyrSum << endl;
                        cout << "Current budget = $" << budget << endl;
                        loss++;
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
                dCardS = prntHnd(dHand, deck);
                cout << "Dealer's Current Hand: " << dCardS << endl;
                cout << "Dealer's Total Value: " << dealSum << endl;
                cout << endl;
                
                //If dealer's hand value is less than 17
                while (dealSum < 17){
                   //Dealer draws card
                    draw(dHand, discard, NCARDS, crdCnt);
                   //Dealer's hand is calculated
                    dealSum = calcVal(dHand, deck);
                    //If dealer's value is less than 17 hit again
                    //Else
                } //End of While Loop
                //Sort cards for presentation:
                dCardS = prntRev(dHand, deck);
                pCardS = prntOrd(pHand, deck);
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
                    wins++;
                    cout << "You've earned $2.00!" << endl;
                    cout << "Current budget = $" << budget << endl;
                    cout << endl;
                }
                //Dealer Hit Phase Ends-
                //Comparison Phase Begins if player and dealer have not busted
                else{
                  if (plyrSum > dealSum){
                      budget += 1.00;
                      wins++;
                      cout << "Player wins! " << plyrSum << " is greater than " 
                           << dealSum << "!" << endl;
                      cout << "You've earned $1.00!"<< endl;
                      cout << "Current budget = $" << budget << endl;
                  }
                  else if (plyrSum < dealSum){
                      loss++;
                      cout << "Dealer wins! " << dealSum << " is greater than " 
                           << plyrSum << "!" << endl;
                  }
                  else{ //If plyrSum is not greater or less, it must be equal
                      budget += .50;
                      draws++;
                      cout << "Tough cookies, it's a draw. " 
                           << plyrSum << " is equivalent to " 
                           << dealSum << endl;
                      cout << "You've earned $0.50"<< endl;
                      cout << "Current budget = $" << budget << endl;
                  }
                }
            }
        }//End of blackjack round
        rnds ++; //Add to round counter
        //Check if deck is below 75%
        if (crdCnt >= 39){
            cout << "Remaining deck below 75%. Reshuffling deck" << endl;
            shuff(discard, crdCnt, NCARDS);
            shuffle ++;
        }
        //Record/Update stats
        write(fn, wins, loss, draws, shuffle, rnds, budget, pName);
        //Prompt user to repeat or quit
        menu(fn, pQuit);
        if (pQuit == 'Q' || pQuit == 'q'){
            ifQuit = true;
        }
        else{
            ifQuit = false;
        }
    } while(ifQuit != true);    
    //Exit stage right or left!
    return 0;
}

//Auxiliary Functions Begins Here:

//Prints cards in reverse order for display
string prntRev(vector<int> hand, char deck[][COLS]){
    string sHand = "";
    for (int indx = 0; indx < hand.size(); indx++){
        for (int adj = indx + 1; adj < hand.size(); adj++){
            if (deck[hand[indx]][1] < deck[hand[adj]][1]){
                int temp = hand[indx];
                hand[indx] = hand[adj];
                hand[adj] = temp;
            }
        }
    }
    //After cards have been sorted
    sHand = prntHnd(hand, deck);
    return sHand;
}
//Prints Player's Current Hand in order: 2-A/Selection Sort
string prntOrd(vector<int> hand, char deck[][COLS]){
    string sHand; //Variable to return sorted hand
    for (int i = 0; i < hand.size(); i++){
            int max = deck[hand[i]][1];
            int indx = i; 
        for (int adj = i + 1; adj < hand.size(); adj++){
            if (deck[hand[adj]][1] < max){
                max = hand[adj];
                indx = adj;
            }
        }
            int temp = hand[i];
            hand[i] = hand[indx];
            hand[indx] = temp;
    }
    //After cards have been sorted print
    sHand = prntHnd(hand, deck);
    return sHand;
}

//V4 Functions:
void menu(char fn[], char &pQuit){
    int option; 
    cout << endl;
    cout << "Round has ended. " << endl;
    cout << "Type 1 for your current stats, '2' to play again or "
         << "'3' to exit" << endl;
        cin >> option;
        switch(option){
            case 1: //Display stats, prompt to play or quit
            {
                statDisp(fn);
                cout << "If you would like to exit, type any other key. " 
                     << "If you would like to keep playing, type 2" << endl;
                cin >> option; 
                break;
            }
            case 2: //Changes the flag to exit the game
            {
                pQuit = 'x';
                break;
            }
            default: cout << "Thank you for playing!"; pQuit = 'q'; exit(0);
        }
}

//Stats Functions--Input/Output Files
void statDisp(char fn[]){
    int wins, loss, draws, shuffle, rnds;
    float budget;
    string name;
    ifstream in;
    in.open(fn);
    in >> wins >> loss >> draws >> shuffle >> rnds >> budget >> name;
    cout << "Stats for " << name << ": " << endl;
    cout << endl;
    cout << "Number of wins: " << wins << endl;
    cout << "Number of losses: " << loss << endl;
    cout << "Number of draws: " << draws << endl;
    cout << "Number of times deck has shuffled: " << shuffle << endl;
    cout << "Number of rounds: " << rnds << endl;
    cout << "Total earned for the session: " << budget << endl;
    in.close();
}

void write(char fn[], int wins, int loss, int draws, 
                int shuffle, int rnds, float budget, string name){
    //Declare the file
    ofstream out;
    out.open(fn);
    out << wins << " " << loss << " " << draws << " " << shuffle 
        << " " << rnds << " " << budget  << " "<< name;
    out.close();
}

//V3 Fucntions:
//On command reset to "reshuffle" cards after threshold is met
void shuff(int discrd[], int &crdCnt, int n){
    discrd[n] = {};
    crdCnt = 0;
}

string prntHnd(vector<int> hand, char deck[][COLS]){
    string sHand = "";
    for (int indx = 0; indx < hand.size(); indx++){
        sHand += deck[hand[indx]][0];
        sHand += " ";
    }
    return sHand;
}

//Initialization Functions for 2D Array
void valFill (char deck[][COLS], int n){
    //Value Column = 1
    for (int i = 1; i < n + 1; i++){
        int imod13=i%13+2;
        //If less than 10 or 14 keep value. Else, value is 10
        deck[i][1] = (imod13 <11 || imod13 == 14) ? imod13 : 10;
    }
}
void suitFill(char deck[][COLS], int n){
    //Face Column = Column 0;, Value Column = 1
    char suit[] = {'2', '3', '4', '5', '6', '7', '8',
                    '9', 'T', 'J', 'Q', 'K', 'A'};
    for (int i = 1; i < n + 1; i++){
        deck[i][0] = suit[i%13];
    }
}
bool linSrch(int discard[], int val, int n){
    for (int indx = 0; indx < n; indx++){
        if (discard[indx] == val){
            return true;
        }
    }
    return false;
}

//V2 Functions-Modified:

//Calculates value of hand when called:
int calcVal(vector<int> hand, char deck[][COLS]){
    int currCrd, currFix, aceCnt, aceMax;
    currCrd = currFix = aceCnt = 0;
    //Obtain raw pulls from hand--Calculate fixed value
    for (int indx = 0; indx < hand.size(); indx++){
        currCrd = hand[indx];
        (static_cast<int>(deck[currCrd][1]) == 14) ? aceCnt++ 
               :currFix += static_cast<int>(deck[currCrd][1]);
        }
    
    //Calculate ace value(if any are in hand)
    
    if (aceCnt > 0){
        aceMax = aceCnt + 10;
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
void draw (vector<int> &hand, int discard[], int n, int &cardCnt){
    //Draws the Card-Keeps Raw Values
    int card;
    do{
        card = (rand() %52 + 1);
    }while(linSrch(discard, card, n));
    discard[cardCnt] = card;
    cardCnt++;
    hand.push_back(card); //adds raw index of card
}



