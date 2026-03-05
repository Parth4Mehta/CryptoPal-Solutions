#include <bits/stdc++.h>
#include "../../include/crypto/utils.h"
using namespace std;

//?-------------------------------------------------------------------------------------------------

int main()
{
    
    ifstream inputFile("Set1/Chal1/input.txt");
    string inputString;
    getline(inputFile, inputString);
    inputFile.close();

    ifstream outputFile("Set1/Chal1/output.txt");
    string expectedOutput;
    getline(outputFile, expectedOutput);
    outputFile.close();

    string op = Convert_hex_to_base64(inputString);
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