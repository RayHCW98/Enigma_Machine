/*
The component classes for the Enigma Machine
*/
#include "stdafx.h"
#include "Components.h"
using namespace std;

Rotor::Rotor(unordered_map<int, int> f, int notch) {
    assert(notch >= 0);
    assert(notch <= 39);
    this->forward = unordered_map<int, int>(f);
    this->configureBackward();
    this->notch_position = notch;
};

int Rotor::getNotchPosition() const {
    return this->notch_position;
}

void Rotor::setNotchPosition(int n) {
    this->notch_position = n;
}

void Rotor::configureBackward() {
    auto it = this->forward.begin();
    while (it != this->forward.end()) {
        this->backward[it->second] = it->first;
        it++;
    }
};

int Rotor::encrypt(int input) const {
    assert(input >= 0);
    assert(input <= 39);
    if (this->forward.find(input) == this->forward.end()) {
        cout << "The illegal character is: " << input << "\n";
        for(auto it = this->forward.begin(); it != this->forward.end(); it++) {
            cout << it->first << " ";
        }
    }
    assert(this->forward.find(input) != this->forward.end());
    return (this->forward).at(input);
};

int Rotor::decrypt(int input) const {
    assert(input >= 0);
    assert(input <= 39);
    assert(this->backward.find(input) != this->backward.end());
    return (this->backward).at(input);
};

bool Rotor::checkLegalLastRotor() const {
    auto it = this->forward.begin();
    while (it != this->forward.end()) {
        if (it->first != this->forward.at(this->forward.at(it->first))) {
            return false;
        }
        it++;
    }
    return true;
};

const unordered_map<string, int> RotorCombination::stringToInt = RotorCombination::createStringToInt();
const unordered_map<int, string> RotorCombination::intToString = RotorCombination::createIntToString();

RotorCombination::RotorCombination() {
    this->rotorNum = 10;
    vector<Rotor> r;
    r.push_back(Rotor::getRotorByIndex("0"));
    r.push_back(Rotor::getRotorByIndex("1"));
    r.push_back(Rotor::getRotorByIndex("2"));
    r.push_back(Rotor::getRotorByIndex("3"));
    r.push_back(Rotor::getRotorByIndex("4"));
    r.push_back(Rotor::getRotorByIndex("5"));
    r.push_back(Rotor::getRotorByIndex("6"));
    r.push_back(Rotor::getRotorByIndex("7"));
    r.push_back(Rotor::getRotorByIndex("8"));
    r.push_back(Rotor::getRotorByIndex("9"));
    this->rotors = r;
    vector<int> p;
    p.push_back(5);
    p.push_back(2);
    p.push_back(6);
    p.push_back(3);
    p.push_back(1);
    p.push_back(5);
    p.push_back(7);
    p.push_back(9);
    p.push_back(14);
    p.push_back(28);
    this->positions = p;
    Rotor temp = Rotor::getDefaultLastRotor();
    this->insertRotor(temp, 10, 0);
};

RotorCombination::RotorCombination(int num) {
    assert(num >= 2);
    this->rotorNum = num - 1;
    vector<Rotor> r(num - 1, Rotor());
    this->rotors = r;
    vector<int> n(num - 1, 0);
    this->positions = n;
    Rotor temp = Rotor::getDefaultLastRotor();
    this->insertRotor(temp, num - 1, 0);
};

RotorCombination::RotorCombination(string index, vector<int> pos) {
    assert(index.size() > 0);
    assert(index.size() == pos.size());
    for(auto iter = pos.begin(); iter != pos.end(); iter++) {
        assert((*iter) >= 0);
        assert((*iter) <= 39);
    }
    vector<Rotor> r;
    for (int i = 0; i < index.size(); i++) {
        string temp(1, index[i]);
        r.push_back(Rotor::getRotorByIndex(temp));
    }
    r.push_back(Rotor::getDefaultLastRotor());
    pos.push_back(0);
    this->rotors = r;
    this->positions = pos;
    this->rotorNum = index.size() + 1;
};

int RotorCombination::getRotorNum() const {
    return this->rotorNum;
};

vector<int> RotorCombination::getPos() const {
    return vector<int> (this->positions);
};

void RotorCombination::setPos(int i, int p) {
    assert(i >= 0);
    assert(i < this->rotorNum);
    assert(p >= 0);
    assert(p <= 39);
    if ((i == (this->rotorNum - 1)) || (i == (this->rotorNum - 2))) {
        this->positions[this->rotorNum - 1] = p;
        this->positions[this->rotorNum - 2] = p;
    } else {
        this->positions[i] = p;
    };
};

void RotorCombination::insertRotor(Rotor r, int pos, int notchPos) {
    assert(pos >= 0);
    assert(pos <= this->rotorNum);
    this->rotors.insert(this->rotors.begin() + pos, r);
    this->positions.insert(this->positions.begin() + pos, notchPos);
    this->rotorNum = this->rotorNum + 1;
};

void RotorCombination::removeRotor(int pos) {
    assert(pos >= 0);
    assert(pos < this->rotorNum);
    this->rotors.erase(this->rotors.begin() + pos);
    this->positions.erase(this->positions.begin() + pos);
    this->rotorNum = this->rotorNum - 1;
};

void RotorCombination::oneClick() {
    bool rotateNext = true;
    bool prevRotate = true;
    for (int i = 0; i < this->rotorNum - 1; i++) {
        if (rotateNext && prevRotate) {
            rotateNext = (this->rotors[i + 1].getNotchPosition() == this->positions[i + 1]);
            this->positions[i] = (this->positions[i] + 1) % 40;
            if ((this->positions[i]) < 0) {
                this->positions[i] = this->positions[i] + 40;
            }
            if (i == this->rotorNum - 2) {
                this->positions[this->rotorNum - 1] = (this->positions[this->rotorNum - 1] + 1) % 40;
                if ((this->positions[this->rotorNum - 1]) < 0) {
                    this->positions[this->rotorNum - 1] = this->positions[this->rotorNum - 1] + 40;
                }
            }
        } else {
            prevRotate = false;
        }    
    }
};

void RotorCombination::oneBack() {
    bool rotateNext = true;
    bool prevRotate = true;
    for (int i = 0; i < this->rotorNum - 1; i++) {
        if (rotateNext && prevRotate) {
            rotateNext = (this->rotors[i + 1].getNotchPosition() == (this->positions[i] - 1));
            this->positions[i] = (this->positions[i] - 1) % 40;
            if ((this->positions[i]) < 0) {
                this->positions[i] = this->positions[i] + 40;
            }
            if (i == this->rotorNum - 2) {
                this->positions[this->rotorNum - 1] = (this->positions[this->rotorNum - 1] - 1) % 40;
                if ((this->positions[this->rotorNum - 1]) < 0) {
                    this->positions[this->rotorNum - 1] = this->positions[this->rotorNum - 1] + 40;
                }
            }
        } else {
            prevRotate = false;
        }    
    }
};

void RotorCombination::printPositions(string m) {
    cout << m;
    cout << "{";
    auto iter = this->positions.begin();
    while (iter != this->positions.end()) {
        cout << *iter << " ";
        iter++;
    }
    cout << "} \n";
}

string RotorCombination::encryptOne(string input) {
    assert(input.size() == 1);
    if (isupper(input[0])) {
        input[0] = tolower(input[0]);
    }
    assert((stringToInt.find(input) != stringToInt.end()) && "The provided string contains illegal characters.");
    int ini = stringToInt.at(input);
    int temp = (ini + this->positions[0]) % 40;
    if (temp < 0) {
        temp = temp + 40;
    }
    // each iteration: rotor + rotor connection 
    for (int i = 0; i < this->rotorNum - 2; i++) {
        temp = this->rotors[i].encrypt(temp);
        temp = (temp + this->positions[i + 1] - this->positions[i]) % 40;
        if (temp < 0) {
            temp = temp + 40;
        }
    }
    temp = this->rotors[this->rotorNum - 2].encrypt(temp);
    temp = this->rotors[this->rotorNum - 1].encrypt(temp);
    // each iteration: rotor + rotor connection
    for (int i = this->rotorNum - 2; i > 0; i--) {
        temp = this->rotors[i].decrypt(temp);
        temp = (temp + this->positions[i - 1] - this->positions[i]) % 40;
        if (temp < 0) {
            temp = temp + 40;
        }
    }
    temp = this->rotors[0].decrypt(temp);
    temp = (temp - this->positions[0]) % 40;
    if (temp < 0) {
        temp = temp + 40;
    }
    string result = intToString.at(temp);
    this->oneClick();
    return result;
};

string RotorCombination::decryptOne(string input) {
    return this->encryptOne(input);
};

string RotorCombination::encrypt(string input) {
    string result = "";
    for (int i = 0; i < input.size(); i++) {
        string temp(1, input[i]);
        result = result + this->encryptOne(temp);
    }
    return result;
};

string RotorCombination::decrypt(string input) {
    return this->encrypt(input);
};

Plugboard::Plugboard() {
    auto it = Plugboard::legalCharacters.begin();
    while (it != Plugboard::legalCharacters.end()) {
        this->board[*it] = *it;
        it++;
    }
};

Plugboard::Plugboard(unordered_map<string, string> setting) {
    int result = Plugboard::checkLegalBoardInput(setting);
    assert(result != 2);
    if (result == 0) {
        this->board = setting;
    } else {
        this->board = setting;
        auto iter = Plugboard::legalCharacters.begin();
        while (iter != Plugboard::legalCharacters.end()) {
            if (setting.find(*iter) == setting.end()) {
                this->board[*iter] = *iter;
            }
            iter++;
        }
    }
    assert(this->checkLegalBoardSettings() && "Board setting is not legal.\n");
}

string Plugboard::encryptOne(string input) const {
    assert(input.size() == 1);
    if (isupper(input[0])) {
        input[0] = tolower(input[0]);
    }
    if (find(Plugboard::legalCharacters.begin(), Plugboard::legalCharacters.end(), input) == Plugboard::legalCharacters.end()) {
        cout << "The illegal input is: " << input << "\n";
    }
    assert(find(Plugboard::legalCharacters.begin(), Plugboard::legalCharacters.end(), input) != Plugboard::legalCharacters.end());
    return this->board.at(input);
}

string Plugboard::decryptOne(string input) const {
    assert(input.size() == 1);
    if (isupper(input[0])) {
        input[0] = tolower(input[0]);
    }
    assert(find(Plugboard::legalCharacters.begin(), Plugboard::legalCharacters.end(), input) != Plugboard::legalCharacters.end());
    return this->board.at(input);
}

string Plugboard::encrypt(string input) const {
    string result = "";
    for (int i = 0; i < input.size(); i++) {
        string temp(1, input[i]);
        result = result + this->encryptOne(temp);
    }
    return result;
}

string Plugboard::decrypt(string input) const {
    string result = "";
    for (int i = 0; i < input.size(); i++) {
        string temp(1, input[i]);
        result = result + this->encryptOne(temp);
    }
    return result;
}

void Plugboard::connect(string i, string j) {
    assert(find(Plugboard::legalCharacters.begin(), Plugboard::legalCharacters.end(), i) != Plugboard::legalCharacters.end());
    assert(find(Plugboard::legalCharacters.begin(), Plugboard::legalCharacters.end(), j) != Plugboard::legalCharacters.end());
    if (this->board[i] == j) {
        return;
    }
    if (this->board[j] == i) {
        return;
    }
    if (i != j) {
        string temp1 = this->board[i];
        string temp2 = this->board[j];
        if ((temp1 != i) && (temp2 != j)) {
            this->board.erase(i);
            this->board.erase(j);
            this->board.erase(temp1);
            this->board.erase(temp2);
            this->board[i] = j;
            this->board[j] = i;
            this->board[temp1] = temp1;
            this->board[temp2] = temp2;
        } else if ((temp1 == i) && (temp2 != j)) {
            this->board.erase(i);
            this->board.erase(j);
            this->board.erase(temp2);
            this->board[i] = j;
            this->board[j] = i;
            this->board[temp2] = temp2;
        } else if ((temp1 != i) && (temp2 == j)) {
            this->board.erase(i);
            this->board.erase(j);
            this->board.erase(temp1);
            this->board[i] = j;
            this->board[j] = i;
            this->board[temp1] = temp1;
        } else {
            this->board.erase(i);
            this->board.erase(j);
            this->board[i] = j;
            this->board[j] = i;
        }
    } else {
        string temp = this->board[i];
        this->board.erase(i);
        this->board.erase(temp);
        this->board[i] = i;
        this->board[temp] = temp;
    }
    assert(this->checkLegalBoardSettings());
};

void Plugboard::printConnectionStatus() const {
    assert(this->checkLegalBoardSettings());
    auto it = this->board.begin();
    vector<string> temp;
    while (it != this->board.end()) {
        if (it->first != it->second) {
            if ((find(temp.begin(), temp.end(), it->second)) == temp.end()) {
                temp.push_back(it->first);
                cout << it->first << "<->" << it->second << "\n";
            }
        }
        it++;
    }
};

void Plugboard::connect(vector<string> i, vector<string> j) {
    assert(i.size() == j.size());
    auto iter1 = i.begin();
    auto iter2 = j.begin();
    while (iter1 != i.end()) {
        this->connect(*iter1, *iter2);
        iter1++;
        iter2++;
    }
    assert(this->checkLegalBoardSettings());
};

int Plugboard::checkLegalBoardInput(unordered_map<string, string> setting) {
    // 0: completely legal; 1: semi-legal, need further action; 2: illegal
    if (setting.size() > 40) {
        return 2;
    }
    if (setting.empty()) {
        return 2;
    }
    auto iter = setting.begin();
    while (iter != setting.end()) {
        if (find(Plugboard::legalCharacters.begin(), Plugboard::legalCharacters.end(), iter->first) == Plugboard::legalCharacters.end()) {
            return 2;
        }
        if (find(Plugboard::legalCharacters.begin(), Plugboard::legalCharacters.end(), iter->second) == Plugboard::legalCharacters.end()) {
            return 2;
        }
        iter++;
    }
    if (setting.size() == 40) {
        return 0;
    }
    return 1;
};

const vector<string> Plugboard::legalCharacters = Plugboard::createLegalCharacters();

bool Plugboard::checkLegalBoardSettings() const {
    auto it = this->board.begin();
    while (it != this->board.end()) {
        if (it->first != this->board.at(this->board.at(it->first))) {
            cout << it->first << "->" << this->board.at(it->first) << "\n";
            cout << this->board.at(it->first) << "->" << this->board.at(this->board.at(it->first)) << "\n";
            return false;
        }
        it++;
    }
    return true;
};

// Default wiring with default notch position
Rotor::Rotor(): notch_position(0) {
    this->forward[0] = 36;
    this->forward[1] = 23;
    this->forward[2] = 18;
    this->forward[3] = 17;
    this->forward[4] = 22;
    this->forward[5] = 13;
    this->forward[6] = 3;
    this->forward[7] = 30;
    this->forward[8] = 2;
    this->forward[9] = 11;
    this->forward[10] = 0;
    this->forward[11] = 32;
    this->forward[12] = 31;
    this->forward[13] = 27;
    this->forward[14] = 1;
    this->forward[15] = 6;
    this->forward[16] = 10;
    this->forward[17] = 29;
    this->forward[18] = 26;
    this->forward[19] = 15;
    this->forward[20] = 28;
    this->forward[21] = 24;
    this->forward[22] = 33;
    this->forward[23] = 34;
    this->forward[24] = 16;
    this->forward[25] = 21;
    this->forward[26] = 8;
    this->forward[27] = 38;
    this->forward[28] = 20;
    this->forward[29] = 35;
    this->forward[30] = 7;
    this->forward[31] = 39;
    this->forward[32] = 25;
    this->forward[33] = 19;
    this->forward[34] = 9;
    this->forward[35] = 14;
    this->forward[36] = 4;
    this->forward[37] = 5;
    this->forward[38] = 37;
    this->forward[39] = 12;
    this->configureBackward();
};

Rotor Rotor::getDefaultLastRotor() {
    unordered_map<int, int> m;
    m[0] = 28;
    m[1] = 34;
    m[2] = 20;
    m[3] = 7;
    m[4] = 38;
    m[5] = 17;
    m[6] = 23;
    m[7] = 3;
    m[8] = 11;
    m[9] = 15;
    m[10] = 27;
    m[11] = 8;
    m[12] = 22;
    m[13] = 24;
    m[14] = 32;
    m[15] = 9;
    m[16] = 21;
    m[17] = 5;
    m[18] = 29;
    m[19] = 39;
    m[20] = 2;
    m[21] = 16;
    m[22] = 12;
    m[23] = 6;
    m[24] = 13;
    m[25] = 30;
    m[26] = 37;
    m[27] = 10;
    m[28] = 0;
    m[29] = 18;
    m[30] = 25;
    m[31] = 33;
    m[32] = 14;
    m[33] = 31;
    m[34] = 1;
    m[35] = 36;
    m[36] = 35;
    m[37] = 26;
    m[38] = 4;
    m[39] = 19;
    Rotor r = Rotor(m, 3);
    assert(r.checkLegalLastRotor());
    return r;
};

unordered_map<string, int> RotorCombination::createStringToInt() {
    unordered_map<string, int> m;
    m["a"] = 0;
    m["b"] = 1;
    m["c"] = 2;
    m["d"] = 3;
    m["e"] = 4;
    m["f"] = 5;
    m["g"] = 6;
    m["h"] = 7;
    m["i"] = 8;
    m["j"] = 9;
    m["k"] = 10;
    m["l"] = 11;
    m["m"] = 12;
    m["n"] = 13;
    m["o"] = 14;
    m["p"] = 15;
    m["q"] = 16;
    m["r"] = 17;
    m["s"] = 18;
    m["t"] = 19;
    m["u"] = 20;
    m["v"] = 21;
    m["w"] = 22;
    m["x"] = 23;
    m["y"] = 24;
    m["z"] = 25;
    m["0"] = 26;
    m["1"] = 27;
    m["2"] = 28;
    m["3"] = 29;
    m["4"] = 30;
    m["5"] = 31;
    m["6"] = 32;
    m["7"] = 33;
    m["8"] = 34;
    m["9"] = 35;
    m[","] = 36;
    m["."] = 37;
    m["?"] = 38;
    m[" "] = 39;
    return m;
};

unordered_map<int, string> RotorCombination::createIntToString() {
    unordered_map<int, string> m;
    m[0] = "a";
    m[1] = "b";
    m[2] = "c";
    m[3] = "d";
    m[4] = "e";
    m[5] = "f";
    m[6] = "g";
    m[7] = "h";
    m[8] = "i";
    m[9] = "j";
    m[10] = "k";
    m[11] = "l";
    m[12] = "m";
    m[13] = "n";
    m[14] = "o";
    m[15] = "p";
    m[16] = "q";
    m[17] = "r";
    m[18] = "s";
    m[19] = "t";
    m[20] = "u";
    m[21] = "v";
    m[22] = "w";
    m[23] = "x";
    m[24] = "y";
    m[25] = "z";
    m[26] = "0";
    m[27] = "1";
    m[28] = "2";
    m[29] = "3";
    m[30] = "4";
    m[31] = "5";
    m[32] = "6";
    m[33] = "7";
    m[34] = "8";
    m[35] = "9";
    m[36] = ",";
    m[37] = ".";
    m[38] = "?";
    m[39] = " ";
    return m;
};

vector<string> Plugboard::createLegalCharacters() {
    vector<string> d;
    d.push_back("a"); 
    d.push_back("b"); 
    d.push_back("c"); 
    d.push_back("d"); 
    d.push_back("e"); 
    d.push_back("f"); 
    d.push_back("g"); 
    d.push_back("h"); 
    d.push_back("i"); 
    d.push_back("j"); 
    d.push_back("k"); 
    d.push_back("l"); 
    d.push_back("m"); 
    d.push_back("n"); 
    d.push_back("o"); 
    d.push_back("p"); 
    d.push_back("q"); 
    d.push_back("r"); 
    d.push_back("s"); 
    d.push_back("t"); 
    d.push_back("u"); 
    d.push_back("v"); 
    d.push_back("w"); 
    d.push_back("x"); 
    d.push_back("y"); 
    d.push_back("z"); 
    d.push_back("0"); 
    d.push_back("1"); 
    d.push_back("2"); 
    d.push_back("3"); 
    d.push_back("4"); 
    d.push_back("5"); 
    d.push_back("6"); 
    d.push_back("7"); 
    d.push_back("8"); 
    d.push_back("9"); 
    d.push_back(",");
    d.push_back("."); 
    d.push_back("?"); 
    d.push_back(" ");
    return d;
};

Rotor Rotor::getRotorByIndex(string index) {
    vector<string> legal;
    legal.push_back("0");
    legal.push_back("1");
    legal.push_back("2");
    legal.push_back("3");
    legal.push_back("4");
    legal.push_back("5");
    legal.push_back("6");
    legal.push_back("7");
    legal.push_back("8");
    legal.push_back("9");
    assert((find(legal.begin(), legal.end(), index) != legal.end()) && "Illegal Rotor Index Supplied!\n");
    unordered_map<int, int> m;
    if (index == "0") {
        m[0] = 36;
        m[1] = 23;
        m[2] = 18;
        m[3] = 17;
        m[4] = 22;
        m[5] = 13;
        m[6] = 3;
        m[7] = 30;
        m[8] = 2;
        m[9] = 11;
        m[10] = 0;
        m[11] = 32;
        m[12] = 31;
        m[13] = 27;
        m[14] = 1;
        m[15] = 6;
        m[16] = 10;
        m[17] = 29;
        m[18] = 26;
        m[19] = 15;
        m[20] = 28;
        m[21] = 24;
        m[22] = 33;
        m[23] = 34;
        m[24] = 16;
        m[25] = 21;
        m[26] = 8;
        m[27] = 38;
        m[28] = 20;
        m[29] = 35;
        m[30] = 7;
        m[31] = 39;
        m[32] = 25;
        m[33] = 19;
        m[34] = 9;
        m[35] = 14;
        m[36] = 4;
        m[37] = 5;
        m[38] = 37;
        m[39] = 12;
        return Rotor(m, 39);
    } else if (index == "1") {
        m[0] = 9;
        m[1] = 26;
        m[2] = 18;
        m[3] = 16;
        m[4] = 32;
        m[5] = 39;
        m[6] = 13;
        m[7] = 24;
        m[8] = 37;
        m[9] = 1;
        m[10] = 33;
        m[11] = 10;
        m[12] = 21;
        m[13] = 20;
        m[14] = 14;
        m[15] = 3;
        m[16] = 11;
        m[17] = 31;
        m[18] = 29;
        m[19] = 4;
        m[20] = 0;
        m[21] = 28;
        m[22] = 22;
        m[23] = 17;
        m[24] = 38;
        m[25] = 27;
        m[26] = 8;
        m[27] = 6;
        m[28] = 2;
        m[29] = 19;
        m[30] = 36;
        m[31] = 5;
        m[32] = 25;
        m[33] = 35;
        m[34] = 15;
        m[35] = 23;
        m[36] = 7;
        m[37] = 12;
        m[38] = 30;
        m[39] = 34;
        return Rotor(m, 0);
    } else if (index == "2") {
        m[0] = 4;
        m[1] = 28;
        m[2] = 36;
        m[3] = 7;
        m[4] = 11;
        m[5] = 33;
        m[6] = 37;
        m[7] = 5;
        m[8] = 32;
        m[9] = 15;
        m[10] = 19;
        m[11] = 35;
        m[12] = 6;
        m[13] = 10;
        m[14] = 22;
        m[15] = 26;
        m[16] = 3;
        m[17] = 18;
        m[18] = 38;
        m[19] = 1;
        m[20] = 30;
        m[21] = 21;
        m[22] = 31;
        m[23] = 34;
        m[24] = 9;
        m[25] = 13;
        m[26] = 14;
        m[27] = 39;
        m[28] = 27;
        m[29] = 0;
        m[30] = 24;
        m[31] = 20;
        m[32] = 12;
        m[33] = 17;
        m[34] = 23;
        m[35] = 29;
        m[36] = 8;
        m[37] = 2;
        m[38] = 25;
        m[39] = 16;
        return Rotor(m, 10);
    } else if (index == "3") {
        m[0] = 38;
        m[1] = 15;
        m[2] = 30;
        m[3] = 20;
        m[4] = 18;
        m[5] = 10;
        m[6] = 36;
        m[7] = 17;
        m[8] = 35;
        m[9] = 11;
        m[10] = 5;
        m[11] = 25;
        m[12] = 34;
        m[13] = 12;
        m[14] = 31;
        m[15] = 7;
        m[16] = 37;
        m[17] = 32;
        m[18] = 22;
        m[19] = 14;
        m[20] = 19;
        m[21] = 26;
        m[22] = 24;
        m[23] = 1;
        m[24] = 33;
        m[25] = 6;
        m[26] = 16;
        m[27] = 29;
        m[28] = 4;
        m[29] = 0;
        m[30] = 8;
        m[31] = 28;
        m[32] = 2;
        m[33] = 13;
        m[34] = 9;
        m[35] = 27;
        m[36] = 23;
        m[37] = 39;
        m[38] = 21;
        m[39] = 3;
        return Rotor(m, 19);
    } else if (index == "4") {
        m[0] = 30;
        m[1] = 22;
        m[2] = 11;
        m[3] = 28;
        m[4] = 6;
        m[5] = 17;
        m[6] = 14;
        m[7] = 15;
        m[8] = 24;
        m[9] = 25;
        m[10] = 35;
        m[11] = 2;
        m[12] = 10;
        m[13] = 12;
        m[14] = 31;
        m[15] = 18;
        m[16] = 5;
        m[17] = 1;
        m[18] = 0;
        m[19] = 8;
        m[20] = 3;
        m[21] = 7;
        m[22] = 39;
        m[23] = 4;
        m[24] = 20;
        m[25] = 21;
        m[26] = 33;
        m[27] = 19;
        m[28] = 36;
        m[29] = 37;
        m[30] = 27;
        m[31] = 29;
        m[32] = 23;
        m[33] = 13;
        m[34] = 26;
        m[35] = 38;
        m[36] = 34;
        m[37] = 32;
        m[38] = 9;
        m[39] = 16;
        return Rotor(m, 26);
    } else if (index == "5") {
        m[0] = 8;
        m[1] = 27;
        m[2] = 13;
        m[3] = 34;
        m[4] = 11;
        m[5] = 6;
        m[6] = 4;
        m[7] = 25;
        m[8] = 35;
        m[9] = 28;
        m[10] = 29;
        m[11] = 14;
        m[12] = 5;
        m[13] = 33;
        m[14] = 7;
        m[15] = 10;
        m[16] = 15;
        m[17] = 17;
        m[18] = 9;
        m[19] = 24;
        m[20] = 38;
        m[21] = 23;
        m[22] = 31;
        m[23] = 0;
        m[24] = 39;
        m[25] = 22;
        m[26] = 32;
        m[27] = 21;
        m[28] = 12;
        m[29] = 36;
        m[30] = 20;
        m[31] = 30;
        m[32] = 1;
        m[33] = 2;
        m[34] = 3;
        m[35] = 16;
        m[36] = 37;
        m[37] = 26;
        m[38] = 19;
        m[39] = 18;
        return Rotor(m, 14);
    } else if (index == "6") {
        m[0] = 35;
        m[1] = 15;
        m[2] = 24;
        m[3] = 13;
        m[4] = 17;
        m[5] = 38;
        m[6] = 31;
        m[7] = 29;
        m[8] = 34;
        m[9] = 18;
        m[10] = 11;
        m[11] = 5;
        m[12] = 27;
        m[13] = 7;
        m[14] = 21;
        m[15] = 20;
        m[16] = 9;
        m[17] = 1;
        m[18] = 8;
        m[19] = 14;
        m[20] = 19;
        m[21] = 22;
        m[22] = 6;
        m[23] = 32;
        m[24] = 4;
        m[25] = 16;
        m[26] = 33;
        m[27] = 36;
        m[28] = 26;
        m[29] = 23;
        m[30] = 2;
        m[31] = 10;
        m[32] = 25;
        m[33] = 30;
        m[34] = 0;
        m[35] = 39;
        m[36] = 3;
        m[37] = 12;
        m[38] = 28;
        m[39] = 37;
        return Rotor(m, 6);
    } else if (index == "7") {
        m[0] = 4;
        m[1] = 14;
        m[2] = 27;
        m[3] = 6;
        m[4] = 16;
        m[5] = 3;
        m[6] = 36;
        m[7] = 25;
        m[8] = 29;
        m[9] = 2;
        m[10] = 33;
        m[11] = 21;
        m[12] = 0;
        m[13] = 39;
        m[14] = 13;
        m[15] = 35;
        m[16] = 37;
        m[17] = 5;
        m[18] = 17;
        m[19] = 19;
        m[20] = 30;
        m[21] = 23;
        m[22] = 18;
        m[23] = 34;
        m[24] = 8;
        m[25] = 38;
        m[26] = 22;
        m[27] = 12;
        m[28] = 20;
        m[29] = 9;
        m[30] = 26;
        m[31] = 24;
        m[32] = 7;
        m[33] = 11;
        m[34] = 31;
        m[35] = 1;
        m[36] = 28;
        m[37] = 32;
        m[38] = 10;
        m[39] = 15;
        return Rotor(m, 39);
    } else if (index == "8") {
        m[0] = 32;
        m[1] = 33;
        m[2] = 36;
        m[3] = 21;
        m[4] = 1;
        m[5] = 11;
        m[6] = 22;
        m[7] = 17;
        m[8] = 31;
        m[9] = 3;
        m[10] = 39;
        m[11] = 2;
        m[12] = 15;
        m[13] = 29;
        m[14] = 25;
        m[15] = 34;
        m[16] = 8;
        m[17] = 18;
        m[18] = 37;
        m[19] = 4;
        m[20] = 7;
        m[21] = 0;
        m[22] = 30;
        m[23] = 5;
        m[24] = 10;
        m[25] = 12;
        m[26] = 26;
        m[27] = 9;
        m[28] = 35;
        m[29] = 24;
        m[30] = 23;
        m[31] = 38;
        m[32] = 19;
        m[33] = 28;
        m[34] = 6;
        m[35] = 16;
        m[36] = 14;
        m[37] = 27;
        m[38] = 20;
        m[39] = 13;
        return Rotor(m, 33);
    } else {
        m[0] = 5;
        m[1] = 19;
        m[2] = 13;
        m[3] = 18;
        m[4] = 14;
        m[5] = 28;
        m[6] = 38;
        m[7] = 4;
        m[8] = 3;
        m[9] = 20;
        m[10] = 29;
        m[11] = 2;
        m[12] = 39;
        m[13] = 25;
        m[14] = 24;
        m[15] = 30;
        m[16] = 12;
        m[17] = 1;
        m[18] = 11;
        m[19] = 36;
        m[20] = 35;
        m[21] = 32;
        m[22] = 0;
        m[23] = 34;
        m[24] = 33;
        m[25] = 7;
        m[26] = 23;
        m[27] = 8;
        m[28] = 22;
        m[29] = 10;
        m[30] = 16;
        m[31] = 37;
        m[32] = 26;
        m[33] = 31;
        m[34] = 15;
        m[35] = 27;
        m[36] = 6;
        m[37] = 21;
        m[38] = 9;
        m[39] = 17;
        return Rotor(m, 5);
    }
};