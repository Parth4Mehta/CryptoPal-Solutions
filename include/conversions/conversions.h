#pragma once
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
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

inline string Convert_base64_to_hex(const string &base64) {
    const string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string bin = "";
    for (char c : base64) {
        if (c == '=') break;
        size_t val = base64_chars.find(c);
        for (int i = 5; i >= 0; --i) {
            bin += ((val >> i) & 1) ? '1' : '0';
        }
    }
    // trim trailing bits that don't form a full nibble
    bin = bin.substr(0, (bin.size() / 4) * 4);
    string hex = "";
    const char hexChars[] = "0123456789abcdef";
    for (size_t i = 0; i < bin.size(); i += 4) {
        int val = 0;
        for (int j = 0; j < 4; ++j) {
            val = (val << 1) + (bin[i + j] - '0');
        }
        hex += hexChars[val];
    }
    return hex;
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

inline string plainText_to_hex(const string &plainText) {
    string hex = "";
    for (unsigned char c : plainText) {
        char buf[3];
        snprintf(buf, sizeof(buf), "%02x", c);
        hex += buf;
    }
    return hex;
}
