#pragma once
#include <cctype>
#include <string>
#include <vector>
#include "../conversions/conversions.h"
#include "../helperfxns/helperfxns.h"
using namespace std;


inline string Fixed_XOR(string &hex1, string &hex2)
{
    if(hex2.size() < hex1.size()){
        while(hex2.size() < hex1.size()) {
            hex2 += hex2; // repeat the key
        }
        hex2 = hex2.substr(0, hex1.size()); // trim to match length
    }
    string result = "";
    for (size_t i = 0; i < hex1.size(); ++i)
    {
        int val1 = (hex1[i] >= '0' && hex1[i] <= '9') ? (hex1[i] - '0') : (tolower(hex1[i]) - 'a' + 10);
        int val2 = (hex2[i] >= '0' && hex2[i] <= '9') ? (hex2[i] - '0') : (tolower(hex2[i]) - 'a' + 10);
        int xorVal = val1 ^ val2;
        if (xorVal < 10)
            result += ('0' + xorVal);
        else
            result += ('a' + xorVal - 10);
    }
    return result;
}

inline string singleByteXORCipher(const string &hexInput) {
    vector<unsigned char> cipherBytes = hexToBytes(hexInput);

    vector<string> xorResults;
    for (int key = 0; key < 256; ++key) {
        string plaintext = "";
        for (size_t i = 0; i < cipherBytes.size(); ++i) {
            unsigned char decrypted = cipherBytes[i] ^ key;
            plaintext += decrypted;
        }
        xorResults.push_back(plaintext);
    }
    string ans = xorResults[0];
    double maxScore = scoreEnglish(ans);
    for(auto el: xorResults) {
        double currentScore = scoreEnglish(el);
        if(currentScore > maxScore) {
            maxScore = currentScore;
            ans = el;
        }
    }
    return ans;
}
