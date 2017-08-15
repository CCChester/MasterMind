#include "mastermind.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <utility>

using namespace std;

Mastermind::Mastermind(){
    this->seed = 42;
    this->codeLength = 4;
    this->guessLimit = 12;
    this->code = nullptr;
}

Mastermind::Mastermind(int seed, int codeLength, int guessLimit){
    srand(seed);
    this->codeLength = codeLength;
    this->guessLimit = guessLimit;
    this->code = nullptr;
}

Mastermind::~Mastermind(){
    delete [ ] this->code;
}

void Mastermind::playGame(){
    int control = 0;
    this->code = new char [this->codeLength];
    int num;
    for(int pos = 0; pos < codeLength; pos++){
        num = rand() % 6;
        if(num == 0){this->code[pos] = 'A';}
        else if(num == 1){this->code[pos] = 'B';}
        else if(num == 2){this->code[pos] = 'C';}
        else if(num == 3){this->code[pos] = 'D';}
        else if(num == 4){this->code[pos] = 'E';}
        else if(num == 5){this->code[pos] = 'F';}
    }
    cout << "Welcome to Mastermind! Please enter your first guess." << endl;
    char mychar;
    int deep = 0;
    int mycount = guessLimit;
    while(deep < guessLimit){
        int index = 0;
        char arr[codeLength];
        for(int pos = 0; pos<codeLength; pos++){
            cin >> mychar;
            if(mychar == 'a' || mychar == 'A'){
                arr[index] = 'A';
            }
            else if(mychar == 'b' || mychar == 'B'){
                arr[index] = 'B';
            }
            else if(mychar == 'c' || mychar == 'C'){
                arr[index] = 'C';
            }
            else if(mychar == 'd' || mychar == 'D'){
                arr[index] = 'D';
            }
            else if(mychar == 'e' || mychar == 'E'){
                arr[index] = 'E';
            }
            else if(mychar == 'f' || mychar == 'F'){
                arr[index] = 'F';
            }
            index++;
        }
        int numb = 0;
        int numw = 0;
        char b[codeLength];
        for(int count = 0; count < codeLength; count++){
            b[count] = this->code[count];
        }
        for(int pos = 0; pos < codeLength; pos++){
            if(arr[pos] == b[pos]){
                numb++;
                arr[pos] = '0';
                b[pos] = '0';
            }
            if(numb == codeLength){
                cout << numb << "b" << "," << numw << "w" << endl;
                cout << "You won in " << deep+1 << " guesses!" << endl;
                control = 1;
                break;
            }
        }
        if(control == 1){break;}
        int k = 0;
        while (k < codeLength){
            if(arr[k] == '0'){
                k++;
            }
            else{
                int index = 0;
                while(index < codeLength){
                    if(b[index] == '0'){index++;}
                    else if(arr[k] == b[index]){
                        ++numw;
                        b[index] = '0';
                        arr[k] = '0';
                        break;
                    }
                    else{index++;}
                }
                k++;
            }
        }
        cout << numb << "b" << "," << numw << "w" << endl;
        if (deep != (guessLimit-1)){
            mycount--;
            cout << mycount << " " << "guesses left. Enter guess:" << endl;
        }
        deep++;
    }
    if(control == 0){
        cout << "You lost! The password was:" << endl << this->code << endl;
    }
    cout << "Would you like to play again? (Y/N): ";
    char newchar;
    cin >> newchar;
    if (newchar == 'Y'){
        playGame();
    }
    else if(newchar == 'N'){return;}
}
