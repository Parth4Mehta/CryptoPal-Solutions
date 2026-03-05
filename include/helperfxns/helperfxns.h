#pragma once
#include <cctype>
#include <string>
#include <unordered_map>
using namespace std;


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
