// C / C++实现的 Dijkstra最短路径，图的邻接表表示
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 邻接表的节点
struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode *next;
};

// 邻接表 结构体
struct AdjList {
    struct AdjListNode *head;  // 指向头节点
};

// 图结构体，V为顶点个数。array为所有的邻接表
struct Graph {
    int V;
    struct AdjList *array;
};

//创建邻接表的节点
struct AdjListNode *newAdjListNode(int dest, int weight) {
    struct AdjListNode *newNode = (struct AdjListNode *) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

//创建一个图，包含V的顶点
struct Graph *createGraph(int V) {
    struct Graph *graph = (struct Graph *) malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array = (struct AdjList *) malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// 添加一个边(无向图)
void addEdge(struct Graph *graph, int src, int dest, int weight) {

    struct AdjListNode *newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// 最小堆节点
struct MinHeapNode {
    int v;  //下标
    int dist; //距离
};

// 最小堆
struct MinHeap {
    int size;
    int capacity;
    int *pos;     // pos[i]表示顶点i所在的下标
    struct MinHeapNode **array;
};

// 创建一个最小堆节点
struct MinHeapNode *newMinHeapNode(int v, int dist) {
    struct MinHeapNode *minHeapNode = (struct MinHeapNode *) malloc(
            sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

// A utility function to create a Min Heap
struct MinHeap *createMinHeap(int capacity) {
    struct MinHeap *minHeap = (struct MinHeap *) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *) malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode **) malloc(
            capacity * sizeof(struct MinHeapNode *));
    return minHeap;
}

// 交换两个最小堆的节点
void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b) {
    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

//在位置 idx 调整堆
void minHeapify(struct MinHeap *minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size
        && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size
        && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        // 需要交换的节点
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];

        //交换下标
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        //交换节点
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// 推是否为空
int isEmpty(struct MinHeap *minHeap) {
    return minHeap->size == 0;
}

// 弹出堆顶的节点(即最小的节点)
struct MinHeapNode *extractMin(struct MinHeap *minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    struct MinHeapNode *root = minHeap->array[0];

    struct MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // 更新下标
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    // 记得减少堆的大小
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// 当节点v的距离更新后(变小了)调整堆
void decreaseKey(struct MinHeap *minHeap, int v, int dist) {
    //获取节点 v 在 堆中的下标
    int i = minHeap->pos[v];

    minHeap->array[i]->dist = dist;

    // 因为是变小了，自下向上调整堆即可。 O(Logn)
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

// 判断节点v是否在堆中
bool isInMinHeap(struct MinHeap *minHeap, int v) {
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}

// 打印结果
void printArr(int dist[], int n) {
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

void dijkstra(struct Graph *graph, int src) {
    int V = graph->V;
    int dist[V];

    struct MinHeap *minHeap = createMinHeap(V);

    // 初始化堆包含所有的顶点
    for (int v = 0; v < V; ++v) {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    // 把 源点 src 的距离设置为0，第一个取出的点即为源点
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V;

    // 这个循环中，minHeap包含的是所有未在SPT中的顶点
    while (!isEmpty(minHeap)) {
        // 取得堆顶节点，即最小距离的顶点
        struct MinHeapNode *minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;

        // 只需要遍历和u相邻的顶点进行更新
        struct AdjListNode *pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            // 松弛操作，更新距离
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX
                && pCrawl->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + pCrawl->weight;
                //距离更新了之后，要调整最小堆
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    // 打印
    printArr(dist, V);
}

// 测试
int main() {
    // 创建上一讲：http://www.acmerblog.com/dijkstra-shortest-path-algorithm-5876.html 例子中的图
    int V = 9;
    struct Graph *graph = createGraph(V);
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);

    dijkstra(graph, 0);

    return 0;
}