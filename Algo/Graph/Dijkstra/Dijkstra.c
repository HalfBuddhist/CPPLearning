/**
 * 迪杰斯特拉算法的实现
 * 使用邻接矩阵
 * O(V^2)
 * 缺点如下:
 * 图中结点用字符串表示, 本可以统一转化为数字.
 * 路径信息只显示使用了路径中可能出现的点, 而没有形成一个完整的路径.
 * 详细修正, 见Java版.
 */
#include "usual.h"
#include "structure.h"

void ShortestPath_DIJ(MGraph G, int v0, PathMatrix *P, ShortPathTable *D) {
    /* 用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及带权长度 */
    /* D[v]。若P[v][w]为TRUE,则w是从v0到v当前求得最短路径上的顶点。 */
    /* sptSet[v]为TRUE,当且仅当v∈S,即已经求得从v0到v的最短路径 */
    int v, w, i, j, min;
    Status sptSet[MAX_VERTEX_NUM];
    for (v = 0; v < G.vexnum; ++v) {
        sptSet[v] = FALSE;
        (*D)[v] = G.arcs[v0][v].adj;
        for (w = 0; w < G.vexnum; ++w)
            (*P)[v][w] = FALSE; /* 设空路径 */
        if ((*D)[v] < INFINITY) {
            (*P)[v][v0] = TRUE;
            (*P)[v][v] = TRUE;
        }
    }
    (*D)[v0] = 0;
    sptSet[v0] = TRUE; /* 初始化,v0顶点属于S集 */
    for (i = 1; i < G.vexnum; ++i) /* 其余G.vexnum-1个顶点 */
    { /* 开始主循环,每次求得v0到某个v顶点的最短路径,并加v到S集 */
        min = INFINITY; /* 当前所知离v0顶点的最近距离 */
        for (w = 0; w < G.vexnum; ++w)
            if (!sptSet[w]) /* w顶点在V-S中 */
            if ((*D)[w] < min) {
                v = w;
                min = (*D)[w];
            } /* w顶点离v0顶点更近 */
        sptSet[v] = TRUE; /* 离v0顶点最近的v加入S集 */
        for (w = 0; w < G.vexnum; ++w) /* 更新当前最短路径及距离 */
        {
            if (!sptSet[w] && min < INFINITY && G.arcs[v][w].adj < INFINITY &&
                (min + G.arcs[v][w].adj < (*D)[w])) { /* 修改D[w]和P[w],w∈V-S */
                (*D)[w] = min + G.arcs[v][w].adj;
                for (j = 0; j < G.vexnum; ++j)
                    (*P)[w][j] = (*P)[v][j];
                (*P)[w][w] = TRUE;
            }
        }
    }
}

int LocateVex(MGraph G, VertexType u) { /* 初始条件:图G存在,u和G中顶点有相同特征 */
    /* 操作结果:若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 */
    int i;
    for (i = 0; i < G.vexnum; ++i)
        if (strcmp(u, G.vexs[i]) == 0)
            return i;
    return -1;
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
            (*G).arcs[i][j].adj = INFINITY; /* 网 */
            (*G).arcs[i][j].info = NULL;
        }

    printf("请输入%d条弧的弧尾 弧头 权值(以空格作为间隔): \n", (*G).arcnum);
    for (k = 0; k < (*G).arcnum; ++k) {
        scanf("%s%s%d%*c", va, vb, &w); /* %*c吃掉回车符 */
        i = LocateVex(*G, va);
        j = LocateVex(*G, vb);
        (*G).arcs[i][j].adj = w; /* 有向网 */
//        (*G).arcs[j][i].adj = w;    //无向网的修改
        if (IncInfo) {
            printf("请输入该弧的相关信息(<%d个字符): ", MAX_INFO);
            gets(s);
            w = strlen(s);
            if (w) {
                info = (char *) malloc((w + 1) * sizeof(char));
                strcpy(info, s);
                (*G).arcs[i][j].info = info; /* 有向 */
//                (*G).arcs[j][i].info = info; /* 无向 */
            }
        }
    }
    (*G).kind = DN;
    return OK;
}

int main() {
    int i, j, v0 = 0; /* v0为源点 */
    VertexType start_node;
    MGraph g; /*图*/
    PathMatrix p; /*最短路径矩阵*/
    ShortPathTable d; /*最短路径长度*/

#ifdef _DEBUG
    freopen("/Users/Qingwei/Documents/workspace/Clion/Algo/Graph/Dijkstra/in.txt", "r", stdin);
//    freopen("src\\in.txt", "r", stdin);
//    freopen("src\\out.txt", "w", stdout);
#endif

    printf("进入主函数:\n");
    CreateDN(&g);
    printf("请输入要查询的起点：\n");
//    scanf("%s", start_node);
//    char c;
//    while ((c = getchar()) != '\n' && c != EOF);
    gets(start_node);

    v0 = LocateVex(g, start_node);

    ShortestPath_DIJ(g, v0, &p, &d);

    printf("最短路径数组p[i][j]如下:\n");
    for (i = 0; i < g.vexnum; ++i) {
        for (j = 0; j < g.vexnum; ++j)
            printf("%2d", p[i][j]);
        printf("\n");
    }

    printf("%s到各顶点的最短路径长度为：\n", g.vexs[0]);
    for (i = 0; i < g.vexnum; ++i) {
        if (v0 == i)
            continue;
        else
            printf("%s-%s:\t%d\n", g.vexs[v0], g.vexs[i], d[i]);
    }
    return 0;
}
