#include <bits/stdc++.h>
#include "../../include/crypto/utils.h"
using namespace std;

//?-------------------------------------------------------------------------------------------------


int main()
{
    ifstream inputFile("Set1/Chal2/input.txt");
    string inputString;
    getline(inputFile, inputString);
    inputFile.close();

    ifstream outputFile("Set1/Chal2/output.txt");
    string expectedOutput;
    getline(outputFile, expectedOutput);
    outputFile.close();

    ifstream keyFile("Set1/Chal2/key.txt");
    string key;
    getline(keyFile, key);
    keyFile.close();

    string op = Fixed_XOR(inputString, key);
    if (op == expectedOutput)
    {
        cout << "Test passed!" << endl;
    }
    else
    {
        cout << "Test failed!" << endl;
        cout << "Expected: " << expectedOutput << endl;
        cout << "Got: " << op << endl;
    }
    return 0;
}