/*堆排序 */
#include "structure.h"
#include "usual.h"
#include "structure_1.h"

#define _DEBUG

void HeapSort(HeapType *);

//小堆
void HeapAdjust_1(HeapType *H, int s, int m) {
    /* 已知H.r[s..m]中记录的关键字除H.r[s].key之外均满足堆的定义，本函数 */
    /* 调整H.r[s]的关键字,使H.r[s..m]成为一个大顶堆(对其中记录的关键字而言) */
    RedType rc;
    int j;
    rc = (*H).r[s];
    for (j = 2 * s; j <= m; j *= 2) { /* 沿key较小的孩子结点向下筛选 */
        if (j < m && GT((*H).r[j].key, (*H).r[j + 1].key)) //如果是小顶堆就将LT改为GT
            ++j; /* j为key较小的记录的下标 */
        if (!GT(rc.key, (*H).r[j].key)) //如果是小顶堆就将LT改为GT
            break; /* rc应插入在位置s上 */
        (*H).r[s] = (*H).r[j];
        s = j;
    }
    (*H).r[s] = rc; /* 插入 */
}

//大堆
void HeapAdjust(HeapType *H, int s, int m) {
    /* 已知H.r[s..m]中记录的关键字除H.r[s].key之外均满足堆的定义，本函数 */
    /* 调整H.r[s]的关键字,使H.r[s..m]成为一个大顶堆(对其中记录的关键字而言) */
    RedType rc;
    int j;
    rc = (*H).r[s];
    for (j = 2 * s; j <= m; j *= 2) { /* 沿key较小的孩子结点向下筛选 */
        if (j < m && LT((*H).r[j].key, (*H).r[j + 1].key)) //如果是小顶堆就将LT改为GT
            ++j; /* j为key较大的记录的下标 */
        if (!LT(rc.key, (*H).r[j].key)) //如果是小顶堆就将LT改为GT
            break; /* rc应插入在位置s上 */
        (*H).r[s] = (*H).r[j];
        s = j;
    }
    (*H).r[s] = rc; /* 插入 */
}

void HeapModify(HeapType *H, int index, int value, MGraph *g) {
    int k, tem, tem_child;
    RedType tem_tran;
    for (k = 1; k <= (*H).length; k++) {
        if (!strcmp((*H).r[k].name, g->vexs[index])) {
            if ((*H).r[k].key > value) {
                (*H).r[k].key = value;
                strcpy((*H).r[k].pre, (*H).r[(*H).length + 1].name);
                tem = k / 2;
                tem_child = k;
                while (tem >= 1) {
                    if ((*H).r[tem_child].key >= (*H).r[tem].key) {
                        break;
                    } else {
                        tem_tran = (*H).r[tem_child];
                        (*H).r[tem_child] = (*H).r[tem];
                        (*H).r[tem] = tem_tran;
                        tem_child = tem;
                        tem = tem / 2;
                    }
                }
            }
            break;
        }
    }
}

/**
 * 不知为什么先调整成大顶堆,再调整成小顶堆,2nlogn
 * 而不直接调整成小顶堆,nlogn
 * 由此可见整个程序的实现极差.
 */
void HeapSort(HeapType *H) { /* 对顺序表H进行堆排序。 */
    RedType t;
    int i;
    for (i = (*H).length / 2; i > 0; --i) //nlogn
        /* 把H.r[1..H.length]建成大顶堆 */
        HeapAdjust(H, i, (*H).length);
    for (i = (*H).length; i > 1; --i) { /* 将堆顶记录和当前未经排序子序列H.r[1..i]中最后一个记录相互交换 */
        t = (*H).r[1];
        (*H).r[1] = (*H).r[i];
        (*H).r[i] = t;
        HeapAdjust(H, 1, i - 1); /* 将H.r[1..i-1]重新调整为大顶堆 */
    }
}

void HeapDeleteTop(HeapType *H) {
    RedType tem;
    tem = (*H).r[1];
    (*H).r[1] = (*H).r[(*H).length];
    (*H).r[(*H).length] = tem;
    (*H).length--;
    HeapAdjust_1(H, 1, H->length);
    //			HeapSort(H);
}

void print(HeapType H) {
    int i;
    for (i = 1; i <= H.length; i++)
        printf("(%d,%d)", H.r[i].key, H.r[i].otherinfo);
    printf("\n");
}

int LocateVex(MGraph G, VertexType u) { /* 初始条件:图G存在,u和G中顶点有相同特征 */
    /* 操作结果:若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 */
    int i;
    for (i = 0; i < G.vexnum; ++i)
        if (strcmp(u, G.vexs[i]) == 0)
            return i;
    return -1;
}

void PrintGraph(MGraph g) {
    //堆排序结果的打印函数:
    int i, j;
    for (i = 0; i < g.vexnum; i++) {
        for (j = 0; j < g.vexnum; j++) {
            printf(" %d ", g.arcs[i][j]);
        }
        printf("\n");
    }
    return;
}

Status CreateDN(MGraph *G) { /* 采用数组(邻接矩阵)表示法,构造有向网G */
    int i, j, k, w, IncInfo;
    char s[MAX_INFO], *info;
    VertexType va, vb;
    printf("请输入有向网G的顶点数,弧数,弧是否含其它信息(是:1,否:0): \n");
    scanf("%d,%d,%d", &(*G).vexnum, &(*G).arcnum, &IncInfo);

    printf("请输入%d个顶点的值(<%d个字符):\n", (*G).vexnum, MAX_NAME);
    for (i = 0; i < (*G).vexnum; ++i)
        /* 构造顶点向量 */
        scanf("%s", (*G).vexs[i]);

    for (i = 0; i < (*G).vexnum; ++i)
        /* 初始化邻接矩阵 */
        for (j = 0; j < (*G).vexnum; ++j) {
            //			(*G).arcs[i][j].adj=INFINITY; /* 网 */
            (*G).arcs[i][j].adj = 1000; /* 网 */
            (*G).arcs[i][j].info = NULL;
        }

    printf("请输入%d条弧的弧尾 弧头 权值(以空格作为间隔): \n", (*G).arcnum);
    for (k = 0; k < (*G).arcnum; ++k) {
        scanf("%s%s%d%*c", va, vb, &w); /* %*c吃掉回车符 */
        i = LocateVex(*G, va);
        j = LocateVex(*G, vb);
        (*G).arcs[i][j].adj = w; /* 有向网*/
        (*G).arcs[j][i].adj = w; //无向网的修改
        if (IncInfo) {
            printf("请输入该弧的相关信息(<%d个字符): ", MAX_INFO);
            gets(s);
            w = (int) strlen(s);
            if (w) {
                info = (char *) malloc((w + 1) * sizeof(char));
                strcpy(info, s);
                (*G).arcs[i][j].info = info; /* 有向 */
            }
        }
    }//for
    (*G).kind = DN;
    return OK;
}

/**
 * 虽然使用了堆,却使用邻接矩阵而不是邻接表来表示图,而且堆实现的并不好,修改操作的复杂度为n
 * 所以整体复杂度为O(n^3logn), n 为结点数.
 * 所以整个程序仅供参考, 实现极差.
 * 详细的prim MST算法请见Java版本.
 */
int main() {

    MGraph g; /*图*/
    int flags[MAXSIZE]; //用以标志该点是否是在树中,可以省去遍历的操作
    int i, j, last, min = 0;

#ifdef _DEBUG
    freopen("src\\in.txt", "r", stdin);
//    freopen("src\\out.txt", "w", stdout);
#endif

    memset(&flags, 0, MAXSIZE * sizeof(int));
    CreateDN(&g);
    PrintGraph(g);
    //	下面进行初始化堆栈的工作,根据图的存储结构,我们这里是把图的第一个结点进行树的初始化结点
    HeapType sl;
    sl.length = g.vexnum - 1;
    for (i = 1; i <= g.vexnum - 1; i++) {
        sl.r[i].key = g.arcs[0][i].adj;
        strcpy(sl.r[i].name, g.vexs[i]);
        strcpy(sl.r[i].pre, g.vexs[0]);
    }
    flags[0] = 1;
    //陆续从优先队列中取出最宜元素并进行相应堆的调整
    HeapSort(&sl);
    //把删除元素的相应的连边做相应的调整
    for (j = 0; j < g.vexnum - 1; j++) {
        HeapDeleteTop(&sl);
        last = LocateVex(g, sl.r[sl.length + 1].name);
        flags[last] = 1;
        min += sl.r[sl.length + 1].key;
        for (i = 0; i <= g.vexnum - 1; i++) {
            if (flags[i] || g.arcs[last][i].adj == 10000) {
                continue;
            }
            HeapModify(&sl, i, g.arcs[last][i].adj, &g);
        }
    }
    //输出
    puts("树的边为:");
    for (i = 1; i <= g.vexnum - 1; i++) {
        printf("%s---%s:%d\n", sl.r[i].pre, sl.r[i].name, sl.r[i].key);
    }
    printf("总的权值为: %d\n", min);
    return 0;
}
