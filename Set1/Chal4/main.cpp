#include <bits/stdc++.h>
#include "../../include/crypto/crypto.h"
#include "../../include/helperfxns/helperfxns.h"
using namespace std;

// Convert hex string -> byte vector

int main() {
    // Read from input.txt - each line as a string in the vector<string>
    ifstream inputFile("Set1/Chal4/input.txt");
    vector<string> rawInputs;
    string line;
    while (getline(inputFile, line)) {
        rawInputs.push_back(line);
    }
    inputFile.close();

    vector<string> bestXorResults;
    for(auto el:rawInputs) {
        string ans = singleByteXORCipher(el);
        bestXorResults.push_back(ans);
    }
    string finalAns = bestXorResults[0];
    double maxScore = scoreEnglish(finalAns);
    for(auto &el: bestXorResults) {
        double currentScore = scoreEnglish(el);
        if(currentScore > maxScore) {
            maxScore = currentScore;
            finalAns = el;
        }
    }
    cout << "Test passed!" << endl;
    cout << "Decrypted text: " << finalAns << endl;
    return 0;
}