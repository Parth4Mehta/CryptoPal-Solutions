#pragma once
#include <cctype>
#include <string>
#include <unordered_map>
using namespace std;


inline string Convert_hex_to_binary(const string &hex)
{
    string bin = "";
    for (char c : hex)
    {
        int val = (c >= '0' && c <= '9') ? (c - '0') : (tolower(static_cast<unsigned char>(c)) - 'a' + 10);
        for (int i = 3; i >= 0; --i)
        {
            bin += ((val >> i) & 1) ? '1' : '0';
        }
    }
    return bin;
}
inline string Convert_hex_to_base64(const string &hex)
{
    string bin = Convert_hex_to_binary(hex);
    if (bin.size() % 6 != 0)
    {
        bin += string(6 - (bin.size() % 6), '0');
    }
    string base64 = "";
    const string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    for (size_t i = 0; i < bin.size(); i += 6)
    {
        string chunk = bin.substr(i, 6);
        int val = 0;
        for (char bit : chunk)
        {
            val = (val << 1) + (bit - '0');
        }
        base64 += base64_chars[val];
    }
    return base64;
}

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

inline double scoreEnglish(const string &text) {
    // English frequency (approximate %)
    static unordered_map<char, double> freq = {
        {'a', 8.2}, {'b', 1.5}, {'c', 2.8}, {'d', 4.3}, {'e', 13.0},
        {'f', 2.2}, {'g', 2.0}, {'h', 6.1}, {'i', 7.0}, {'j', 0.15},
        {'k', 0.77}, {'l', 4.0}, {'m', 2.4}, {'n', 6.7}, {'o', 7.5},
        {'p', 1.9}, {'q', 0.095}, {'r', 6.0}, {'s', 6.3}, {'t', 9.1},
        {'u', 2.8}, {'v', 0.98}, {'w', 2.4}, {'x', 0.15},
        {'y', 2.0}, {'z', 0.074},
        {' ', 15.0}  // space is VERY important
    };
    double score = 0.0;
    for (unsigned char c : text) {
        // Hard reject garbage
        if (c < 32 || c > 126)
            score -= 15.0;
        char lower = tolower(c);
        if (freq.count(lower)) {
            score += freq[lower];
        }
        else if (isdigit(c)) {
            score += 0.5;   // small positive
        }
        else if (c == '.' || c == ',' || c == '\'' ||
                 c == '!' || c == '?' || c == ';' ||
                 c == ':' || c == '-') {
            score += 0.5;   // common punctuation
        }
        else {
            score -= 5.0;   // weird symbol penalty
        }
    }
    return score;
}

// Convert hex string -> byte vector
inline vector<unsigned char> hexToBytes(const string &hex) {
    vector<unsigned char> bytes;

    for (size_t i = 0; i < hex.length(); i += 2) {
        string byteString = hex.substr(i, 2);
        int value = stoi(byteString, nullptr, 16);
        bytes.push_back((unsigned char)value);
    }

    return bytes;
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

inline string plainText_to_hex(const string &plainText) {
    string hex = "";
    for (unsigned char c : plainText) {
        char buf[3];
        snprintf(buf, sizeof(buf), "%02x", c);
        hex += buf;
    }
    return hex;
}
