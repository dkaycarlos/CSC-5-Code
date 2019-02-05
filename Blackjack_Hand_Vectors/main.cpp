/* 
 * File:   main.cpp
 * Author: Danielle Carlos
 * Created on February 5, 2019
 * Purpose:  Utilizing vectors to manage hands in blackjack
 *           and sorting with bubble/selection, searching for
 *           identification of aces
 */

//System Libraries Here
#include <iostream>
#include <cstdlib> //Random Number Generator
#include <ctime>  //Time Library
#include <vector> //Vector Library
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
void linSrch(vector<int>, int, int &, string &);
void bblSort(vector<int>&); //Tested/working
void selSort(vector<int>&);
void binSrch(vector<int>, int, int &);
//Program Execution Begins Here
int main(int argc, char** argv) {
    //Set the random seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare all Variables Here
    int cDraw; //Card draw
    int aceCnt; //Number of aces found in vector
    int val;    //Value to search for (in our case: aces)
    int indx;
    vector<int> hand; // Hand of player/dealer
    
    //Input or initialize values Here
    indx = 0;
    aceCnt = 0;
    val = 14; //Ace value in our program
    
    //Could be used for general hand draws.
    for (int i = 0; i < 100; i++){
    cDraw = (rand() % (14 - 2 + 1)) + 2; //Range 2-14
    hand.push_back(cDraw); //Adds value to vector
    cout << i  << ". Draw = " << cDraw << endl;
    }
    //Process/Calculations Here
    for (int i = 0; i < hand.size(); i++){
        cout << "Value  at index ("<< i <<") = " << hand.at(i) << endl;
    }
    //Output Located Here
    selSort(hand);
    binSrch(hand, val, aceCnt);
    cout << "Amount of Aces = " << aceCnt << endl;
    for (int i = 0; i < hand.size(); i++){
        cout << hand[i] << endl;
    }
    //Exit
    return 0;
}

//Auxiliary Functions Begin Here

//Dealer's Search
void linSrch(vector<int> hand, int val, int &aceCnt, string &indStr){
    for (int indx = 0; indx < hand.size(); indx++){
        if ((hand.at(indx)) == val){
            aceCnt++;
        }
    }
}

//For sorting dealer's hand
void bblSort(vector<int> &hand){
    for (int indx = 0; indx < hand.size(); indx++){
        for (int adj = indx + 1; adj < hand.size(); adj++){
            if (hand[indx] > hand[adj]){
                int temp = hand[indx];
                hand[indx] = hand[adj];
                hand[adj] = temp;
            }
        }
    }
}

//For sorting player's hand
void selSort(vector<int> &hand){
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
}

void binSrch(vector<int> hand, int val, int &aceCnt){
    int first = 0, last = hand.size()-1, middle;
    do{
        middle = (first + last)/2;
        //At the first instance of the ace:
        if(hand[middle] == val) aceCnt++;
        if(hand[middle] < val) first = middle+1;
        else last = middle -1;
    } while (first <=last);
}