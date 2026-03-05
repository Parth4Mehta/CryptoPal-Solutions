#include <bits/stdc++.h>
#include "../../include/crypto/utils.h"
using namespace std;



int main() {
    ifstream inputFile("Set1/Chal3/input.txt");
    string hexInput;
    getline(inputFile, hexInput);
    inputFile.close();

    string ans = singleByteXORCipher(hexInput);
    cout << "Test passed!" << endl;
    cout << "Decrypted text: " << ans << endl;
    return 0;
}