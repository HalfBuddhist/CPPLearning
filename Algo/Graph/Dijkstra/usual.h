#include<string.h>
#include<ctype.h>
#include <malloc/malloc.h> /* malloc()等, #include<malloc.h>  for win*/
#include<limits.h> /* INT_MAX等 */
#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<stdlib.h> /* atoi() */
//#include<io.h> /* eof() */
#include<math.h> /* floor(),ceil(),abs() */
//#include<process.h> /* exit() */

/* 函数结果状态代码 */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 /*不可实行的*/

#define MAX_NAME 5 /* 顶点字符串的最大长度+1 */
#define MAX_INFO 20 /* 相关信息字符串的最大长度+1 */
#define INFINITY INT_MAX  /*用整型最大值代替∞*/
#define MAX_VERTEX_NUM 20 /* 最大顶点个数 */
#define _DEBUG

/* #define OVERFLOW -2 因为在math.h中已定义OVERFLOW的值为3,故去掉此行 */
typedef int Status;
/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Boolean;
/* Boolean是布尔类型,其值是TRUE或FALSE */
typedef int VRType;
typedef char InfoType[MAX_INFO];
typedef char VertexType[MAX_NAME];
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
/*路径矩阵*/
typedef int ShortPathTable[MAX_VERTEX_NUM];

