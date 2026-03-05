#include <bits/stdc++.h>
#include "../../include/crypto/crypto.h"
#include "../../include/conversions/conversions.h"
#include "../../include/helperfxns/helperfxns.h"
using namespace std;

//?-------------------------------------------------------------------------------------------------

// Returns the best single-byte XOR key for a block of raw bytes
inline unsigned char findSingleByteKey(const vector<unsigned char> &block) {
    unsigned char bestKey = 0;
    double bestScore = -1e9;
    for (int key = 0; key < 256; ++key) {
        string plaintext = "";
        for (size_t i = 0; i < block.size(); ++i) {
            plaintext += (char)(block[i] ^ key);
        }
        double s = scoreEnglish(plaintext);
        if (s > bestScore) {
            bestScore = s;
            bestKey = (unsigned char)key;
        }
    }
    return bestKey;
}

int main()
{
    // Step 1: Read base64 input, decode to raw bytes
    ifstream file("Set1/Chal6/input.txt");
    string base64Input = "", line;
    while (getline(file, line)) {
        base64Input += line; // no newlines — they're not part of base64
    }
    file.close();

    string hex = Convert_base64_to_hex(base64Input);
    vector<unsigned char> cipherBytes = hexToBytes(hex);

    // Steps 2 & 3: Find best KEYSIZE via normalized Hamming distance
    vector<pair<double, int>> keysizeScores;

    for (int keysize = 2; keysize <= 40; keysize++) {
        if (cipherBytes.size() < (size_t)(keysize * 4)) break;
        vector<vector<unsigned char>> blocks(4);
        for (int b = 0; b < 4; b++) {
            blocks[b] = vector<unsigned char>(
                cipherBytes.begin() + b * keysize,
                cipherBytes.begin() + (b + 1) * keysize
            );
        }
        double totalDistance = 0;
        int pairs = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                string s1(blocks[i].begin(), blocks[i].end());
                string s2(blocks[j].begin(), blocks[j].end());
                totalDistance += hammingDistance(s1, s2);
                pairs++;
            }
        }
        double normalized = (totalDistance / pairs) / keysize;
        keysizeScores.push_back({normalized, keysize});
    }
    sort(keysizeScores.begin(), keysizeScores.end());

    cout << "Top 3 keysize candidates:" << endl;
    for (int i = 0; i < 3 && i < (int)keysizeScores.size(); i++) {
        cout << "  Keysize: " << keysizeScores[i].second
             << ", Normalized Distance: " << keysizeScores[i].first << endl;
    }

    // Try the top 3 keysizes and pick the one that produces the best overall score
    string bestPlaintext = "";
    string bestKey = "";
    double bestTotalScore = -1e9;

    for (int attempt = 0; attempt < 3 && attempt < (int)keysizeScores.size(); attempt++) {
        int keysize = keysizeScores[attempt].second;

        // Step 4: Break ciphertext into blocks of KEYSIZE length
        vector<vector<unsigned char>> blocks;
        for (size_t i = 0; i < cipherBytes.size(); i += keysize) {
            vector<unsigned char> block(
                cipherBytes.begin() + i,
                cipherBytes.begin() + min(cipherBytes.size(), i + (size_t)keysize)
            );
            blocks.push_back(block);
        }

        // Step 5: Transpose — block[i] = i-th byte of every chunk
        vector<vector<unsigned char>> transposed(keysize);
        for (size_t b = 0; b < blocks.size(); b++) {
            for (size_t i = 0; i < blocks[b].size(); i++) {
                transposed[i].push_back(blocks[b][i]);
            }
        }

        // Step 6 & 7: Solve each transposed block, assemble the key
        string key = "";
        for (int i = 0; i < keysize; i++) {
            unsigned char keyByte = findSingleByteKey(transposed[i]);
            key += (char)keyByte;
        }

        // Step 8: Decrypt with the repeating key
        string plaintext = "";
        for (size_t i = 0; i < cipherBytes.size(); i++) {
            plaintext += (char)(cipherBytes[i] ^ key[i % keysize]);
        }

        double totalScore = scoreEnglish(plaintext);
        if (totalScore > bestTotalScore) {
            bestTotalScore = totalScore;
            bestPlaintext = plaintext;
            bestKey = key;
        }
    }

    cout << "\nKey: \"" << bestKey << "\"" << endl;
    cout << "\nDecrypted text:\n" << bestPlaintext << endl;

    return 0;
}