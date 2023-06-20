#pragma once
#include "Components.h"

/************************************************************************************************************************
 * The legal characters available are: a-z, 0-9, ",", ".", "?", and " ", for a total of 40 characters.
 * All uppercase characters will be automatically converted into lowercase characters.
 * 
 * There are 10 pre-configured rotors available, indexed #0 - #9, all using random wiring for security.
 * Which rotors to be used in which order could be specified using the EnigmaMachine(index, pos) method.
 * 
 * Plugboard can be configured using the connect(i, j) method.
************************************************************************************************************************/

class EnigmaMachine {
    public:
        // Construct Default Enigma Machine, with all 10 rotors in a row
        EnigmaMachine();

        // Specify the number of rotors used, all the rotors will be rotor #0
        explicit EnigmaMachine(int num);

        /* 
        Using index parameter to specify the rotor index and order to be used.
        Using pos parameter to specify the rotors' starting position before encryption.
        Example:
        index = "52631579" means to use rotor #5, #2, #6, #3, #1, #5, #7, #9 in a sequence.
        pos = {17, 19, 39, 0, 23, 33, 5, 2} specifies their respective starting positions.
        Hence, the length of index parameter MUST be equal to the size of the pos parameter.
        The entry i of the pos parameter must satisfy 0 <= i <= 39.
        */
        EnigmaMachine(std::string index, std::vector<int> pos);

        // Used to connect to characters in the plugboard.
        void connect(std::string i, std::string j);
        
        // Set the ith rotor's position to be p. 0 <= p <= 39.
        void setRotorPos(int i, int p);

        // encrypt and decrypt an input string.
        std::string encrypt(std::string input);
        std::string decrypt(std::string input);
    
    private:
        RotorCombination rotors;
        Plugboard board;
};