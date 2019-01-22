/* 
 * File:   main.cpp
 * Author: Danielle Carlos
 * Created on January 18, 2019, 7:00 PM
 * Purpose:  Simple Blackjack Game//Currently testing rng ranges
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

//Execution Begins Here!
int main(int argc, char** argv) {
    //Set the random number seed
    srand(time(0));
    //Declare Variables
    int card1, card2, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14;
    //Initialize or input i.e. set variable values
    c2=c3=c4=c5=c6=c7=c8=c9=c10=c11=c12=c13=c14= 0;//For counting purposes, set to 0
    //Map inputs -> outputs
    for (int x = 0; x < 5200; x++){ //testing for a normal "card" deck range 4/52
        card1 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
        switch(card1){
            case  2:  c2++; break;
            case  3:  c3++; break;
            case  4:  c4++; break;
            case  5:  c5++; break;
            case  6:  c6++; break;
            case  7:  c7++; break;
            case  8:  c8++; break;
            case  9:  c9++; break;
            case 10: c10++; break;
            case 11: c11++; break;
            case 12: c12++; break;
            case 13: c13++; break;
            case 14: c14++; break;
        }
    }
    //Display the outputs
    cout << "Number of 2's: " << c2 << endl;
    cout << "Number of 3's: " << c3 << endl;
    cout << "Number of 4's: " << c4 << endl;
    cout << "Number of 5's: " << c5 << endl;
    cout << "Number of 6's: " << c6 << endl;
    cout << "Number of 7's: " << c7 << endl;
    cout << "Number of 8's: " << c8 << endl;
    cout << "Number of 9's: " << c9 << endl;
    cout << "Number of 10's: " << c10 << endl;
    cout << "Number of 11's: " << c11 << endl;
    cout << "Number of 12's: " << c12 << endl;
    cout << "Number of 13's: " << c13 << endl;
    cout << "Number of 14's: " << c14 << endl;
    //Exit stage right or left!
    return 0;
}