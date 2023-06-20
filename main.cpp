#include "stdafx.h"
#include "Components.h"
#include "EnigmaMachine.h"
using namespace std;

int main() {
    /*
    RotorCombination R1 = RotorCombination(8);
    RotorCombination R2 = RotorCombination(8);
    string original1 = "Hello World.";
    string original2 = "Hello again.";
    string code1 = R1.encrypt(original1);
    string code2 = R1.encrypt(original2);
    string revert1 = R2.decrypt(code1);
    string revert2 = R2.decrypt(code2);
    cout << "The original words are: '" << original1 << "' \n";
    cout << "The encrypted messages are: '" << code1 << "' \n";
    cout << "The decrypted messages are: '" << revert1 << "' \n";
    cout << "The original words are: '" << original2 << "' \n";
    cout << "The encrypted messages are: '" << code2 << "' \n";
    cout << "The decrypted messages are: '" << revert2 << "' \n";
    return 0;
    */
    /*
    Plugboard P1 = Plugboard();
    P1.connect("a", "b");
    P1.connect("h", "l");
    P1.connect(".", "?");
    P1.connect(",", " ");
    P1.connect("i", "v");
    P1.printConnectionStatus();
    */
    /*
    EnigmaMachine E1 = EnigmaMachine();
    EnigmaMachine E2 = EnigmaMachine();
    
    E1.connect("a", "b");
    E1.connect("h", "l");
    E1.connect(".", "?");
    E1.connect(",", " ");
    E1.connect("i", "v");
    E2.connect("a", "b");
    E2.connect("h", "l");
    E2.connect(".", "?");
    E2.connect(",", " ");
    E2.connect("i", "v");
    

    string original1 = "Hello World..............";
    string original2 = "Hello again???????????????";
    string code1 = E1.encrypt(original1);
    string code2 = E1.encrypt(original2);
    string revert1 = E2.decrypt(code1);
    string revert2 = E2.decrypt(code2);
    cout << "The original words are: '" << original1 << "' \n";
    cout << "The encrypted messages are: '" << code1 << "' \n";
    cout << "The decrypted messages are: '" << revert1 << "' \n";
    cout << "The original words are: '" << original2 << "' \n";
    cout << "The encrypted messages are: '" << code2 << "' \n";
    cout << "The decrypted messages are: '" << revert2 << "' \n";
    */
    string s = "029384727837198239103";
    vector<int> pos(21, 1);
    EnigmaMachine E1 = EnigmaMachine(s, pos);
    EnigmaMachine E2 = EnigmaMachine(s, pos);
    string d = E1.encrypt("1234567890");
    string j = E2.decrypt(d);
    cout << j << "\n";
};



