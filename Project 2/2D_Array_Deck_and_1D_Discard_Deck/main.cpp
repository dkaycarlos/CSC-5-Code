/* 
 * File:   main.cpp
 * Author: Danielle Carlos
 * Created on February 9 2019, 12:55 PM
 * Purpose:  2D Array Deck with Discard 
 *           Deck Array/Shuffle Index Array
 */

//System Libraries Here
#include <iostream> //Input/Output Library
#include <cstdlib>  //Random Number Generator
#include <ctime>    //Time Functions
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions
const int COLS = 2; //One for Face Value, other for card value
//Function Prototypes Here
void suitFill(char [][COLS], int);
void valFill (char [][COLS], int);
void print (char [][COLS], int);
bool binSrch(int[], int, int);
bool linSrch(int[], int, int);
void selSort (int[], int);
//Program Execution Begins Here
int main(int argc, char** argv) {
    //Set random number seed
    srand(static_cast<unsigned>(time(0)));
            
    //Size of Discard Arry = 52;
    //Size of 2D Array = 52
    //Shuffle Trigger: if deckCnt >= 39 (at the end of the round)
    //Declare all Variables Here
    const int NCARDS = 53;
    char deck[NCARDS][COLS];
    int discard[NCARDS] = {};
    int rngDraw, cardCnt;
    //Input or initialize values Here
    cardCnt = 0;
    suitFill(deck, NCARDS);
    valFill (deck, NCARDS);
    //Process/Calculations Here
    //Updated part of the draw feature
    for (int i = 0; i < NCARDS; i++){
        int rngDraw;
        do{
            rngDraw = rand()%52 + 1; //Range: 1-52
        }while(linSrch(discard, rngDraw, NCARDS));
        discard[cardCnt] = rngDraw;
        cardCnt++;
    }
    for (int ind = 0; ind < NCARDS; ind++){
        cout << "Card at " << ind << " is: "<<deck[discard[ind]][0] 
                << " with a value of " << static_cast<int>(deck[discard[ind]][1]) << endl;
    }
    print(deck, NCARDS);
    //Exit
    return 0;
}

//Auxiliary Functions
bool linSrch(int discard[], int val, int n){
    for (int indx = 0; indx < n; indx++){
        if (discard[indx] == val){
            return true;
        }
    }
    return false;
}

void print(char deck[][COLS], int n){
    for (int i = 1; i < n + 1; i++){
        cout << i << ". " << deck[i][0] <<
             " has a value of " << static_cast<int>(deck[i][1]) << endl;
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

void valFill (char deck[][COLS], int n){
    //Value Column = 1
    for (int i = 1; i < n + 1; i++){
        int imod13=i%13+2;
        //If less than 10 or 14 keep value. Else, value is 10
        deck[i][1] = (imod13 <11 || imod13 == 14) ? imod13 : 10;
    }
}