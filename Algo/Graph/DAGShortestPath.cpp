#include <iostream>
#include <list>
#include <stack>
#include <limits.h>

#define INF INT_MAX
using namespace std;


/**
 * 有向无环图DAG至少有一个源点, 一个终点
 * 反证法:
 * 如果没有源点, 也就是所有的顶点处都有进入的边指向它, 那么我们随机的从一个顶点开始,逆着这条指向它的边到下一个顶点,可以发现
 * 这个过程可以一直走下去, 而对于一个有限图而言, 可能的路径是有限的, 而无限的走下去只能说明图中有环,与DAG的定义矛盾,因此必须
 * 有一个源点, 得证.
 * 同理可证, 必有一个终点.
 */
// 邻接表节点
class AdjListNode {
    int v;
    int weight;
public:
    AdjListNode(int _v, int _w) {
        v = _v;
        weight = _w;
    }

    int getV() { return v; }

    int getWeight() { return weight; }
};

// 图
class Graph {
    int V;    // 顶点个数

    list<AdjListNode> *adj;

    void topologicalSortRecall(int v, bool visited[], stack<int> &stk);

public:
    Graph(int V);

    void addEdge(int u, int v, int weight);

    void shortestPath(int s);
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<AdjListNode>[V];
}

void Graph::addEdge(int u, int v, int weight) {
    AdjListNode node(v, weight);
    adj[u].push_back(node);
}

// 拓扑排序，递归调用。这个顺序就是DFS中出栈序的逆序
void Graph::topologicalSortRecall(int v, bool visited[], stack<int> &stk) {
    // 标记当前节点是访问过的
    visited[v] = true;

    list<AdjListNode>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
        AdjListNode node = *i;
        if (!visited[node.getV()])
            topologicalSortRecall(node.getV(), visited, stk);
    }
    stk.push(v); //should preorder all the directed child node.
}

/**
 * 算法描述:
 * -首先，我们必须对有向无环图进行拓扑排序;
 * -其次，我们将到源点的距离初始化为0并将到其它所有顶点的距离设置为无穷大;
 * -最后，对于列表中的每一个顶点，我们从它的所有邻节点中找到最短路径的那个顶点;
 *
 * 时间复杂度
 * 拓扑排序的时间复杂度是O(V + E)。找到拓扑顺序后，算法依次处理所有顶和其相邻顶点的顶点。总相邻顶点的个数是O(E)。
 * 因此,内循环运行O(V + E)。所以，这个算法的总体时间复杂度是O(V + E)。
 */
// 从给定的源点s 找出到其它顶点的最短距离.
void Graph::shortestPath(int s) {
    stack<int> stk;
    int dist[V];

    //标记所有顶点为未访问过的
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // 拓扑排序，结果存入stk中
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSortRecall(i, visited, stk);

    // 初始化距离
    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[s] = 0;

    // 按照拓扑排序的顺序处理 各个顶点
    while (!stk.empty()) {
        // 获得拓扑排序的下一个顶点
        int u = stk.top();
        stk.pop();

        // 更新所有相邻的顶点
        list<AdjListNode>::iterator i;
        if (dist[u] != INF) {
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
                if (dist[i->getV()] > dist[u] + i->getWeight())
                    dist[i->getV()] = dist[u] + i->getWeight();
        }
    }

    // 打印结果
    for (int i = 0; i < V; i++)
        (dist[i] == INF) ? cout << "INF " : cout << dist[i] << " ";
}

// 测试
int main() {

    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);
    int s = 1;
    cout << "Following are shortest distances from source " << s << " \n";
    g.shortestPath(s);

    return 0;
}