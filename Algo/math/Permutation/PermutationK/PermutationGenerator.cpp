/*
* PermutationGenerator.cpp
*
*  Created on: 2010-11-11
*      Author: LQW
*/

#include "PermutationGenerator.h"

/************************************************************************/
/* 阶乘计算
/************************************************************************/
int fnFactorial(const int pNum) {
    if (pNum == 1) {
        return 1;
    }
    else {
        return pNum * fnFactorial(pNum - 1);
    }
}

/************************************************************************/
/* construction function
/************************************************************************/
PermutationGenerator::PermutationGenerator() {
    // TODO Auto-generated constructor stub
}

/************************************************************************/
/* destruction function
/************************************************************************/
PermutationGenerator::~PermutationGenerator() {
    // TODO Auto-generated destructor stub
}

/************************************************************************/
/* 寻找后第N个排列
/************************************************************************/
void PermutationGenerator::fnNextN(void) {
    m_inElementNumer = (int) m_stPrimitiveStr.size();
    switch (m_enPermulateAlgo) {
        case enumDICTIONARY_SEQ:
            fnDictionaryNextN();
            break;
        case enumINCREASE_SYSTEM:
            fnIncSysNextN();
            break;
        case enumDECREASE_SYSTEM:
            fnDecSysNextN();
            break;
        case enumADJACENT_EXCHANGE:
            fnAdjExchNextN();
            break;
    }

    return;
}

/************************************************************************/
/*打点法计算字典序的中介数
/************************************************************************/

void PermutationGenerator::fnDictionaryGetIntermediaryNumber(int pIntermediaryNumber[]) {
    for (int i = m_inElementNumer - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            if (m_stPrimitiveStr[j] > m_stPrimitiveStr[i]) {
                pIntermediaryNumber[j]++;
            }
        }
    }

    //output
    printf("原始排列的中位数为：\n");
    for (int i = 0; i < m_inElementNumer - 1; i++) {
        printf("%d", pIntermediaryNumber[i]);
    }
    printf("\n");
    return;
}

/************************************************************************/
/* 将十进制数转化为递增进位制数
/************************************************************************/
void PermutationGenerator::fnTRanIncSys(const int pPrimNum, int pInterNum[]) {
    int inEleNum = this->m_inElementNumer;
    int inTemp = 1;
    int inPrimNum = pPrimNum;
    int i;
    for (i = 0; i < this->m_inElementNumer - 1; i++, inEleNum--) {
        if (inPrimNum == 0) {
            pInterNum[i] = 0;
        }
        else {
            inTemp = fnFactorial(inEleNum - 1);
            pInterNum[i] = inPrimNum / inTemp;
            inPrimNum %= inTemp;
        }
    }
    pInterNum[i] = 0;
    return;
}

/************************************************************************/
/* 递增进位制数的加法
/************************************************************************/
void PermutationGenerator::fnDictionaryCalIntermediaryNumber(int m_inNextN, int inIntermediaryNumber[],
                                                             int in_arrResult[]) {
    int *in_arrIncInterNum = new int[this->m_inElementNumer];
    this->fnTRanIncSys(m_inNextN, in_arrIncInterNum);

    printf("跨度的递增进位制数表示：\n");
    int i;
    for (i = 0; i < m_inElementNumer - 1; i++) {
        if (in_arrIncInterNum[i] != 0) {
            break;
        }
    }
    if (i == m_inElementNumer - 1) {
        printf("0");
    }
    else {
        for (; i < m_inElementNumer - 1; i++) {
            printf("%d", in_arrIncInterNum[i]);
        }
    }
    printf("\n");

    int inJinWei = 0;
    int inTemp;
    int inTemp2;
    in_arrResult[m_inElementNumer - 1] = 0;
    for (int i = this->m_inElementNumer - 2; i >= 0; i--) {
        inTemp = in_arrIncInterNum[i] + inIntermediaryNumber[i] + inJinWei;
        inTemp2 = m_inElementNumer - i;
        in_arrResult[i] = inTemp % inTemp2;
        inJinWei = inTemp / inTemp2;
    }

    //output
    printf("结果的递增进位制数表示：\n");
    for (int i = 0; i < m_inElementNumer - 1; i++) {
        printf("%c", in_arrResult[i] + 48);
    }
    printf("\n");

    delete[] in_arrIncInterNum;
}

/************************************************************************/
/* 查找字典序的第n个
/************************************************************************/
void PermutationGenerator::fnDictionaryNextN(void) {
    int *inIntermediaryNumber = new int[m_inElementNumer];
    memset(inIntermediaryNumber, 0, sizeof(int) * m_inElementNumer);

    //算出中介数
    fnDictionaryGetIntermediaryNumber(inIntermediaryNumber);

    int *in_arrResult = new int[this->m_inElementNumer];
    fnDictionaryCalIntermediaryNumber(m_inNextN, inIntermediaryNumber, in_arrResult);
    fnDictionaryGetNextNum(in_arrResult);

    delete[] inIntermediaryNumber;
    delete[] in_arrResult;
    return;
}


/************************************************************************/
/* 字典序法：根据中介数计算出排列
/************************************************************************/
void PermutationGenerator::fnDictionaryGetNextNum(int p_int_arrResult[]) {
    int *int_arrTemp = new int[this->m_inElementNumer];
    int *int_arrNextNum = new int[this->m_inElementNumer];
    bool *boo_arrNextFlag = new bool[m_inElementNumer];
    memset(boo_arrNextFlag, 0, sizeof(bool) * m_inElementNumer);
    memset(int_arrTemp, 0, sizeof(int) * m_inElementNumer);

    for (int i = 1; i <= m_inElementNumer; i++) {
        for (int j = 0; j <= m_inElementNumer - 1; j++) {
            if (boo_arrNextFlag[j] == false && (p_int_arrResult[j] - int_arrTemp[j] == 0)) {
                int_arrNextNum[j] = i;
                boo_arrNextFlag[j] = true;
                for (int k = 0; k < j; k++) {
                    if (boo_arrNextFlag[k] == false) {
                        int_arrTemp[k]++;
                    }
                }
                break;
            }
        }
    }

    printf("结果排列为：\n");
    for (int i = 0; i < m_inElementNumer; i++) {
        cout << int_arrNextNum[i];
    }
    printf("\n");

    delete[] int_arrNextNum;
    delete[] int_arrTemp;
    delete[] boo_arrNextFlag;
}

/************************************************************************/
/* 查找递增进位制的第n个
/************************************************************************/
void PermutationGenerator::fnIncSysNextN() {
    int *inIntermediaryNumber = new int[m_inElementNumer + 1];
    memset(inIntermediaryNumber, 0, sizeof(int) * (m_inElementNumer + 1));

    //算出中介数
    fnIncSysGetIntermediaryNumber(inIntermediaryNumber);
    int *in_arrResult = new int[this->m_inElementNumer];
    fnIncSysCalIntermediaryNumber(m_inNextN, inIntermediaryNumber, in_arrResult);
    fnIncSysGetNextNum(in_arrResult);

    //clean work
    delete[] inIntermediaryNumber;
    delete[] in_arrResult;
    return;
}

/************************************************************************/
/* 计算出递增进位制对应的中介数
/************************************************************************/
void PermutationGenerator::fnIncSysGetIntermediaryNumber(int pPrimIntNumber[]) {
    for (int i = 0; i <= m_inElementNumer - 1; i++) {
        for (int j = i + 1; j <= m_inElementNumer - 1; j++) {
            if (this->m_stPrimitiveStr[j] < this->m_stPrimitiveStr[i]) {
                pPrimIntNumber[this->m_inElementNumer - m_stPrimitiveStr[i] + 48]++;
            }
        }
    }
    pPrimIntNumber[m_inElementNumer - 1] = 0;

    //output
    printf("原始排列的中位数为：\n");
    for (int i = 0; i <= m_inElementNumer - 2; i++) {
        printf("%d", pPrimIntNumber[i]);
    }
    printf("\n");

    //clean work
    return;
}


/************************************************************************/
/* 递增进位制数的加法
/************************************************************************/
void PermutationGenerator::fnIncSysCalIntermediaryNumber(int pNextN, int pIntNumber[], int in_arrResult[]) {

    int *in_arrIncInterNum = new int[this->m_inElementNumer];
    this->fnTRanIncSys(m_inNextN, in_arrIncInterNum);

    printf("跨度的递增进位制数表示：\n");
    int i;
    for (i = 0; i < m_inElementNumer - 1; i++) {
        if (in_arrIncInterNum[i] != 0) {
            break;
        }
    }
    if (i == m_inElementNumer - 1) {
        printf("0");
    }
    else {
        for (; i < m_inElementNumer - 1; i++) {
            printf("%d", in_arrIncInterNum[i]);
        }
    }
    printf("\n");

    int inJinWei = 0;
    int inTemp;
    int inTemp2;
    in_arrResult[m_inElementNumer - 1] = 0;
    for (int i = this->m_inElementNumer - 2; i >= 0; i--) {
        inTemp = in_arrIncInterNum[i] + pIntNumber[i] + inJinWei;
        inTemp2 = m_inElementNumer - i;
        in_arrResult[i] = inTemp % inTemp2;
        inJinWei = inTemp / inTemp2;
    }

    //output
    printf("结果的递增进位制数表示：\n");
    for (int i = 0; i < m_inElementNumer - 1; i++) {
        printf("%c", in_arrResult[i] + 48);

    }
    printf("\n");

    delete[] in_arrIncInterNum;
}

/************************************************************************/
/* 递增进位制法：中介数求排列
/************************************************************************/
void PermutationGenerator::fnIncSysGetNextNum(int p_arrResult[]) {
    bool *boo_arrFlag = new bool[m_inElementNumer];
    memset(boo_arrFlag, 0, sizeof(bool) * m_inElementNumer);//标志是否已占用
    int *int_arrResult = new int[m_inElementNumer];

    for (int i = 0; i <= m_inElementNumer - 2; i++) {
        int counter = 0;
        int j;
        for (j = m_inElementNumer - 1; counter <= p_arrResult[i]; j--) {
            if (boo_arrFlag[j] == false) {
                counter++;
            }
        }
        int_arrResult[j + 1] = m_inElementNumer - i;
        boo_arrFlag[j + 1] = true;
    }
    for (int i = 0; i <= m_inElementNumer - 1; i++) {
        if (boo_arrFlag[i] == false) {
            int_arrResult[i] = 1;
        }

    }

    printf("结果排列为：\n");
    for (int i = 0; i < m_inElementNumer; i++) {
        cout << int_arrResult[i];
    }
    printf("\n");

    //clean work
    delete[] int_arrResult;
    delete[] boo_arrFlag;
}

/************************************************************************/
/* 查找递減进位制的第n个
/************************************************************************/
void PermutationGenerator::fnDecSysNextN() {
    int *inIntermediaryNumber = new int[m_inElementNumer + 1];
    memset(inIntermediaryNumber, 0, sizeof(int) * (m_inElementNumer + 1));

    //算出中介数
    fnDecSysGetIntermediaryNumber(inIntermediaryNumber);
    int *in_arrResult = new int[this->m_inElementNumer];
    fnDesSysCalIntermediaryNumber(m_inNextN, inIntermediaryNumber, in_arrResult);
    fnDecSysGetNextNum(in_arrResult);

    //clean work
    delete[] inIntermediaryNumber;
    delete[] in_arrResult;
    return;
}

/************************************************************************/
/* 算法递减进位制的中介数
/************************************************************************/
void PermutationGenerator::fnDecSysGetIntermediaryNumber(int pIntNumber[]) {
    this->fnIncSysGetIntermediaryNumber(pIntNumber);
    for (int i = 0; i <= ((m_inElementNumer - 1) / 2) - 1; i++) {
        int temp;
        temp = pIntNumber[i];
        pIntNumber[i] = pIntNumber[m_inElementNumer - 2 - i];
        pIntNumber[m_inElementNumer - 2 - i] = temp;
    }

    printf("原始排列的中位数为：\n");
    for (int i = 0; i <= m_inElementNumer - 2; i++) {
        printf("%d", pIntNumber[i]);
    }
    printf("\n");

    //clean work
    return;
}

/************************************************************************/
/* 递减进位制数的加法
/************************************************************************/
void PermutationGenerator::fnDesSysCalIntermediaryNumber(int pNextN, int pInterNum[], int pResult[]) {
    int *in_arrIncInterNum = new int[this->m_inElementNumer];
    this->fnTRanDecSys(m_inNextN, in_arrIncInterNum);

    printf("跨度的递减进位制数表示：\n");
    int i;
    for (i = 0; i < m_inElementNumer - 1; i++) {
        if (in_arrIncInterNum[i] != 0) {
            break;
        }
    }
    if (i == m_inElementNumer - 1) {
        printf("0");
    }
    else {
        for (; i < m_inElementNumer - 1; i++) {
            printf("%d", in_arrIncInterNum[i]);
        }
    }
    printf("\n");

    int inJinWei = 0;
    int inTemp;
    int inTemp2;
    pResult[m_inElementNumer - 1] = 0;
    for (int i = this->m_inElementNumer - 2; i >= 0; i--) {
        inTemp = in_arrIncInterNum[i] + pInterNum[i] + inJinWei;
        inTemp2 = i + 2;
        pResult[i] = inTemp % inTemp2;
        inJinWei = inTemp / inTemp2;
    }

    //output
    printf("结果的递增进位制数表示：\n");
    for (int i = 0; i < m_inElementNumer - 1; i++) {
        printf("%c", pResult[i] + 48);

    }
    printf("\n");

    delete[] in_arrIncInterNum;
}

/************************************************************************/
/* 将十进制数转化为递减进位制数
/************************************************************************/
void PermutationGenerator::fnTRanDecSys(const int pPrimNext, int *pDecNext) {
    int temp1 = pPrimNext;
    int temp2 = m_inElementNumer;
    for (int i = m_inElementNumer - 2; i >= 0; i--, temp2--) {

        if (temp1 == 0) {
            pDecNext[i] = 0;
        }
        else {
            pDecNext[i] = temp1 % temp2;
            temp1 /= temp2;
        }
    }
    return;
}

/************************************************************************/
/* 递减进位制法：中介数求排列
/************************************************************************/
void PermutationGenerator::fnDecSysGetNextNum(int pResultInterNum[]) {
    bool *boo_arrFlag = new bool[m_inElementNumer];
    memset(boo_arrFlag, 0, sizeof(bool) * m_inElementNumer);//标志是否已占用
    int *int_arrResult = new int[m_inElementNumer];

    for (int i = m_inElementNumer - 2; i >= 0; i--) {
        int counter = 0;
        int j;
        for (j = m_inElementNumer - 1; counter <= pResultInterNum[i]; j--) {
            if (boo_arrFlag[j] == false) {
                counter++;
            }
        }
        int_arrResult[j + 1] = i + 2;
        boo_arrFlag[j + 1] = true;
    }
    for (int i = 0; i <= m_inElementNumer - 1; i++) {
        if (boo_arrFlag[i] == false) {
            int_arrResult[i] = 1;
        }

    }

    printf("结果排列为：\n");
    for (int i = 0; i < m_inElementNumer; i++) {
        cout << int_arrResult[i];
    }
    printf("\n");

    //clean work
    delete[] int_arrResult;
    delete[] boo_arrFlag;
}

/************************************************************************/
/* 查找临位对换法的第n个
/************************************************************************/
void PermutationGenerator::fnAdjExchNextN() {
    int *inIntermediaryNumber = new int[m_inElementNumer + 1];
    memset(inIntermediaryNumber, 0, sizeof(int) * (m_inElementNumer + 1));

    bool *boo_arrDirection = new bool[m_inElementNumer];//移位对换法还有他的方向

    //算出中介数
    fnAdjExcGetIntermediaryNumber(inIntermediaryNumber);
    int *in_arrResult = new int[this->m_inElementNumer];
    fnAdjExcCalIntermediaryNumber(m_inNextN, inIntermediaryNumber, in_arrResult);
    fnAdjExcGetNextNum(in_arrResult, boo_arrDirection);

    //clean work
    delete[] inIntermediaryNumber;
    delete[] in_arrResult;

    return;
}

/************************************************************************/
/* 求临位对换法中的中介数
/************************************************************************/

void PermutationGenerator::fnAdjExcGetIntermediaryNumber(int pAGInterNum[]) {
    int counter = 0;
    for (int i = m_inElementNumer - 1; m_stPrimitiveStr[i] != 2 + 48; i--) {
        if (this->m_stPrimitiveStr[i] < (2 + 48)) {
            counter++;
        }
    }
    pAGInterNum[0] = counter;
    counter = 0;

    for (int i = 1; i <= m_inElementNumer - 2; i++) {
        if (i % 2 == 1) {
            if (pAGInterNum[i - 1] % 2 == 0) {
                for (int j = m_inElementNumer - 1; m_stPrimitiveStr[j] != i + 2 + 48; j--) {
                    if (this->m_stPrimitiveStr[j] < (i + 2 + 48)) {
                        counter++;
                    }
                }
            }
            else {
                for (int j = 0; m_stPrimitiveStr[j] != i + 2 + 48; j++) {
                    if (this->m_stPrimitiveStr[j] < (i + 2 + 48)) {
                        counter++;
                    }
                }
            }
        }
        else {
            if ((pAGInterNum[i - 1] + pAGInterNum[i - 2]) % 2 == 0) {
                for (int j = m_inElementNumer - 1; m_stPrimitiveStr[j] != i + 2 + 48; j--) {
                    if (this->m_stPrimitiveStr[j] < (i + 2 + 48)) {
                        counter++;
                    }
                }
            }
            else {
                for (int j = 0; m_stPrimitiveStr[j] != i + 2 + 48; j++) {
                    if (this->m_stPrimitiveStr[j] < (i + 2 + 48)) {
                        counter++;
                    }
                }
            }
        }
        pAGInterNum[i] = counter;
        counter = 0;
    }

    //output
    printf("原始排列的中位数为：\n");
    for (int i = 0; i <= m_inElementNumer - 2; i++) {
        printf("%d", pAGInterNum[i]);
    }
    printf("\n");

    //clean work
    return;
}

/************************************************************************/
/* 递减进位制数的加法
/************************************************************************/
void PermutationGenerator::fnAdjExcCalIntermediaryNumber(int pNextN, int pInterNum[], int pResult[]) {
    int *in_arrIncInterNum = new int[this->m_inElementNumer];
    this->fnTRanDecSys(pNextN, in_arrIncInterNum);

    printf("跨度的递减进位制数表示：\n");
    int i;
    for (i = 0; i < m_inElementNumer - 1; i++) {
        if (in_arrIncInterNum[i] != 0) {
            break;
        }
    }
    if (i == m_inElementNumer - 1) {
        printf("0");
    }
    else {
        for (; i < m_inElementNumer - 1; i++) {
            printf("%d", in_arrIncInterNum[i]);
        }
    }
    printf("\n");

    int inJinWei = 0;
    int inTemp;
    int inTemp2;
    pResult[m_inElementNumer - 1] = 0;
    for (int i = this->m_inElementNumer - 2; i >= 0; i--) {
        inTemp = in_arrIncInterNum[i] + pInterNum[i] + inJinWei;
        inTemp2 = i + 2;
        pResult[i] = inTemp % inTemp2;
        inJinWei = inTemp / inTemp2;
    }

    //output
    printf("结果的递增进位制数表示：\n");
    for (int i = 0; i < m_inElementNumer - 1; i++) {
        printf("%c", pResult[i] + 48);
    }
    printf("\n");

    delete[] in_arrIncInterNum;
}

/************************************************************************/
/* 临位对换法：中介数求排列
/************************************************************************/

void PermutationGenerator::fnAdjExcGetNextNum(int pInterNumResult[], bool *pDirection) {
    bool *boo_arrFlag = new bool[m_inElementNumer];
    memset(boo_arrFlag, 0, sizeof(bool) * m_inElementNumer);//标志位置是否已经占用
    int *int_arrResult = new int[m_inElementNumer];//用于存储最终结果

    for (int i = m_inElementNumer - 2; i >= 0; i--) {
        int counter = 0;
        int j;
        if (i % 2 == 1) {
            if (pInterNumResult[i - 1] % 2 == 1) {
                for (j = 0; counter <= pInterNumResult[i]; j++) {
                    if (boo_arrFlag[j] == false) {
                        counter++;
                    }
                }
                int_arrResult[j - 1] = i + 2;
                boo_arrFlag[j - 1] = true;
            }
            else {
                for (j = m_inElementNumer - 1; counter <= pInterNumResult[i]; j--) {
                    if (boo_arrFlag[j] == false) {
                        counter++;
                    }
                }
                int_arrResult[j + 1] = i + 2;
                boo_arrFlag[j + 1] = true;
            }

        }
        else {
            if ((pInterNumResult[i - 1] + pInterNumResult[i - 2]) % 2 == 1) {
                for (j = 0; counter <= pInterNumResult[i]; j++) {
                    if (boo_arrFlag[j] == false) {
                        counter++;
                    }
                }
                int_arrResult[j - 1] = i + 2;
                boo_arrFlag[j - 1] = true;
            }
            else {
                for (j = m_inElementNumer - 1; counter <= pInterNumResult[i]; j--) {
                    if (boo_arrFlag[j] == false) {
                        counter++;
                    }
                }
                int_arrResult[j + 1] = i + 2;
                boo_arrFlag[j + 1] = true;
            }
        }
    }

    for (int i = 0; i <= m_inElementNumer - 1; i++) {
        if (boo_arrFlag[i] == false) {
            int_arrResult[i] = 1;
        }
    }

    //output
    printf("结果排列为：\n");
    for (int i = 0; i < m_inElementNumer; i++) {
        cout << int_arrResult[i];
    }
    printf("\n");

    //clean work
    delete[] int_arrResult;
    delete[] boo_arrFlag;
}