#include<stdio.h>
#include<conio.h>

#define MAXSIZE 20 /* 一个用作示例的小顺序表的最大长度 */

/*对两个数值型关键字的比较约定为如下的宏定义 */
#define EQ(a, b) ((a)==(b))
#define LT(a, b) ((a)<(b))
#define GT(a, b) ((a)>(b))
#define LQ(a, b) ((a)<=(b))

typedef int InfoType;
/* 定义其它数据项的类型 */
typedef int KeyType;
/*定义关键字类型为整型*/
typedef struct {
    KeyType key;
    /* 关键字项 */
    InfoType otherinfo;
    /* 其它数据项，具体类型在主程中定义 */
    char name[5];
    char pre[5];
} RedType;
/* 记录类型 */
typedef struct {
    RedType r[MAXSIZE + 1];
    /* r[0]闲置或用作哨兵单元 */
    int length; /* 顺序表长度 */
} SqList;
/* 顺序表类型 */
typedef SqList HeapType; /* 堆采用顺序表存储表示 */
