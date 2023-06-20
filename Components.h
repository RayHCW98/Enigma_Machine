#pragma once

class Rotor {
    public:
        // Default Constructor, using default rotor wiring
        Rotor();

        // User defined rotor wiring
        Rotor(std::unordered_map<int, int> f, int notch);

        // get / set method for notch position
        int getNotchPosition() const;
        void setNotchPosition(int n);

        // encrypting and decrypting an input int
        int encrypt(int input) const;
        int decrypt(int input) const;

        // check if the rotor qualifies to be the last rotor
        bool checkLegalLastRotor() const;

        std::unordered_map<int, int> getForward() const {
            return this->forward;
        };
        std::unordered_map<int, int> getBackward() const {
            return this->backward;
        };

        static Rotor getDefaultLastRotor();

        static Rotor getRotorByIndex(std::string index);

    private:
        /* 
        Configuration of the rotor wiring, forward and backward should be
        inverse of each other
        */ 
        std::unordered_map<int, int> forward;
        std::unordered_map<int, int> backward;

        // The position of the notch which facilitate the spin of the rotor, between 0-39
        int notch_position;

        // Given forward wiring, configure backward wiring on inverse relation
        void configureBackward();
};

// There is a "hidden" rotor at the end of all the rotors that must be specified
class RotorCombination {
public:
    // default constructor
    RotorCombination();
    
    // semi-default constructor: users specify how many default rotors to use
    // in default position
    explicit RotorCombination(int num);

    RotorCombination(std::string index, std::vector<int> pos);

    // get the number of rotors
    int getRotorNum() const;

    // get notch position information
    std::vector<int> getPos() const;

    // set position
    void setPos(int i, int p);

    // insert/remove a rotor to a given position, with given notch position
    void insertRotor(Rotor r, int pos, int notchPos);
    void removeRotor(int pos);
    
    // encrypting and decrypting an input strings
    std::string encrypt(std::string input);
    std::string decrypt(std::string input);

    void printPositions(std::string m = "");
    
private:
    int rotorNum;
    bool check = false;
    std::vector<Rotor> rotors;
    std::vector<int> positions;
    static const std::unordered_map<std::string, int> stringToInt;
    static const std::unordered_map<int, std::string> intToString;
    static std::unordered_map<std::string, int> createStringToInt();
    static std::unordered_map<int, std::string> createIntToString();
    void oneClick();
    void oneBack();
    std::string encryptOne(std::string input);
    std::string decryptOne(std::string input);
};

class Plugboard {
    public:
        Plugboard();
        explicit Plugboard(std::unordered_map<std::string, std::string> setting);
        void connect(std::string i, std::string j);
        void connect(std::vector<std::string> i, std::vector<std::string> j);
        bool checkLegalBoardSettings() const;
        std::string encrypt(std::string input) const;
        std::string decrypt(std::string input) const;
        void printConnectionStatus() const;
    private:
        std::unordered_map<std::string, std::string> board;
        static const std::vector<std::string> legalCharacters;
        static std::vector<std::string> createLegalCharacters();
        static int checkLegalBoardInput(std::unordered_map<std::string, std::string> setting);
        std::string encryptOne(std::string input) const;
        std::string decryptOne(std::string input) const;
};