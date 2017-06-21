#include "HeaderPublic.h"
#include "PermutationGenerator.h"

#define _CRT_SECURE_NO_WARNINGS

int main(void) {

#ifdef _DEBUG
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    cout << "Please choose the algorithm:" << endl << "0-Dictionary Sequence"
    << endl << "1-Increase System" << endl << "2-Decrease System"
    << endl << "3-Adjacent Exchange" << endl;
    int inChoice;
    PermutationGenerator LmPermutationGenerator;
    string stPrimitiveSeq;
    string stResult;

    cin >> inChoice;
    switch (inChoice) {
        case 0:
            LmPermutationGenerator.m_enPermulateAlgo = enumDICTIONARY_SEQ;
            break;
        case 1:
            LmPermutationGenerator.m_enPermulateAlgo = enumINCREASE_SYSTEM;
            break;
        case 2:
            LmPermutationGenerator.m_enPermulateAlgo = enumDECREASE_SYSTEM;
            break;
        case 3:
            LmPermutationGenerator.m_enPermulateAlgo = enumADJACENT_EXCHANGE;
            break;
    }

    cout << "Please input the sequence:" << endl;
    cin >> LmPermutationGenerator.m_stPrimitiveStr;
    cout << "Please input the number n which you want to consult:" << endl;
    cin >> LmPermutationGenerator.m_inNextN;
    LmPermutationGenerator.fnNextN();

    return 0;
}

