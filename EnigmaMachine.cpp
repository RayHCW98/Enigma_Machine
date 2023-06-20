#include "stdafx.h"
#include "Components.h"
#include "EnigmaMachine.h"
using namespace std;

EnigmaMachine::EnigmaMachine() {
    this->rotors = RotorCombination();
    this->board = Plugboard();
};

EnigmaMachine::EnigmaMachine(int num) {
    this->rotors = RotorCombination(num + 1);
    this->board = Plugboard();
};

EnigmaMachine::EnigmaMachine(string index, vector<int> pos) {
    this->rotors = RotorCombination(index, pos);
    this->board = Plugboard();
};

void EnigmaMachine::connect(string i, string j) {
    this->board.connect(i, j);
};

string EnigmaMachine::encrypt(string input) {
    string result;
    result = this->board.encrypt(input);
    result = this->rotors.encrypt(result);
    result = this->board.encrypt(result);
    return result;
};

string EnigmaMachine::decrypt(string input) {
    string result;
    result = this->board.decrypt(input);
    result = this->rotors.decrypt(result);
    result = this->board.decrypt(result);
    return result;
};

void EnigmaMachine::setRotorPos(int i, int p) {
    this->rotors.setPos(i, p);  
};