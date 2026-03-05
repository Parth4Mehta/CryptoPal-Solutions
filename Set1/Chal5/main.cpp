#include <bits/stdc++.h>
#include "../../include/crypto/utils.h"
using namespace std;

int main() {
    ifstream inputFile("Set1/Chal5/input.txt");
    vector<string> rawInputs;
    string line;
    string givenKey = "ICE";
    string starts = "";
    int prevLen = 0;
    while (getline(inputFile, line)) {
        //add new line char to line only if not at the end of file
        if(!inputFile.eof()) {
            line += '\n';
        }
        rawInputs.push_back(line);
        starts += givenKey[prevLen % givenKey.size()];
        prevLen = line.size();
    }
    inputFile.close();
    int n = rawInputs.size();

    
    for(int i = 0; i < n; ++i) {
        string plainText = rawInputs[i];
        string hexOutput = plainText_to_hex(plainText);
        string repeatingKey;
        switch(starts[i]){
            case 'I': repeatingKey = "ICE"; break;
            case 'C': repeatingKey = "CEI"; break;
            case 'E': repeatingKey = "EIC"; break;
            default: repeatingKey = "ICE"; break;
        }
        string keyHex = plainText_to_hex(repeatingKey);
        string cipherHex = Fixed_XOR(hexOutput, keyHex);
        cout << cipherHex;
    }
    return 0;
}