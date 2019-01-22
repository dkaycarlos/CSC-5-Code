/* 
 * File:   main.cpp
 * Author: Danielle Carlos
 * Created on January 18, 2019, 7:00 PM
 * Purpose:  Simple Blackjack Game/Testing value ranges for the sum
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
    int card1, card2, cardSum, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20, c21;
    //Initialize or input i.e. set variable values
    c2=c3=c4=c5=c6=c7=c8=c9=c10=c11=c12=c13=c14=c15=c16=c17=c18=c19=c20=c21= 0;//For counting purposes, set to 0.
    //Map inputs -> outputs
    for (int x = 0; x < 5200; x++){ //testing for a normal sum range.
        card1 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
        card2 = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
        if (card1 == 11 || card1 == 12 || card1 == 13)
            card1 = 10;
        else if (card1 == 14 && card2 <= 10 && card2 > 2) //card2 Range: 10 max/3min
            card1 = 11;
        else if (card1 == 14 && card2 == 14) //basic double ace = 2. Later implementation has A choice for 1 or 11
        {
            card1 = 1;
            card2 = 1;      
        }
        else if(card1 == 14 && card2 < 3) //if card2 is 2/A combo
            card1 = 1;
        else if (card1 < 3 && card2 == 14) //if card1 has 2/A combo
            card2 = 1;
        cardSum = card1 + card2;
        switch(cardSum){ //Max range should always be 21 for a starting hand
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
            case 15: c15++; break;
            case 16: c16++; break;
            case 17: c17++; break;
            case 18: c18++; break;
            case 19: c19++; break;
            case 20: c20++; break;
            case 21: c21++; break;
            default: "Number falls out of range"; break;
        }
    }
    //Display the outputs
    cout << "Statistics for A Starting Hand with Fixed Ace Values:" << endl;
    cout << "2: " << c2 << endl;
    cout << "3: " << c3 << endl;
    cout << "4: " << c4 << endl;
    cout << "5: " << c5 << endl;
    cout << "6: " << c6 << endl;
    cout << "7: " << c7 << endl;
    cout << "8: " << c8 << endl;
    cout << "9: " << c9 << endl;
    cout << "10: " << c10 << endl;
    cout << "11: " << c11 << endl;
    cout << "12: " << c12 << endl;
    cout << "13: " << c13 << endl;
    cout << "14: " << c14 << endl;
    cout << "15: " << c15 << endl;
    cout << "16: " << c16 << endl;
    cout << "17: " << c17 << endl;
    cout << "18: " << c18 << endl;
    cout << "19: " << c19 << endl;
    cout << "20: " << c20 << endl;
    cout << "21: " << c21 << endl;
    //Exit stage right or left!
    return 0;
}