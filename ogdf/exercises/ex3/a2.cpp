#include <ogdf/basic/graph_generators.h>
#include <ogdf/basic/simple_graph_alg.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/basic/Graph_d.h>
#include <ogdf/basic/List.h>
#include <ogdf/graphalg/ShortestPathAlgorithms.h>

using namespace ogdf;
using namespace std;

void nodeDistribution(ClusterElement c, Array<int> &dist)
{
    auto func = [](node v) {
        return v->degree();
    };
    int maxval = 0;
    int minval = std::numeric_limits<int>::max();

    for (node v : c.nodes)
    {
        Math::updateMax(maxval, func(v));
        Math::updateMin(minval, func(v));
    }

    dist.init(minval, maxval, 0);
    for (node v : c.nodes)
    {
        ++dist[func(v)];
    }
}

int connectedComponents(const ClusterElement &C, NodeArray<int> &component)
{
    int nComponent = 0;
    component.fill(-1);

    ArrayBuffer<node> S;

    for (node v : C.nodes)
    {
        if (component[v] != -1)
            continue;

        S.push(v);
        component[v] = nComponent;

        while (!S.empty())
        {
            node w = S.popRet();
            for (adjEntry adj : w->adjEntries)
            {
                node x = adj->twinNode();
                if (component[x] == -1)
                {
                    component[x] = nComponent;
                    S.push(x);
                }
            }
        }

        ++nComponent;
    }

    return nComponent;
}

void degreeDistribution(ClusterGraph C)
{
    cluster c;
    forall_clusters(c, C)
    {
        Array<int> arr;
        nodeDistribution(*c, arr);
        cout << "Degree distribution for cluster: (degree -> amount) " << endl;
        Array<int>::iterator ptr;
        for (ptr = arr.begin(); ptr != arr.end(); ptr++)
        {
            cout << ptr - arr.begin() << ": " << *ptr << "   |" << string(*ptr, '=') << endl;
            // cout << *ptr << endl;
        }
        cout << endl;
    }
}

void connectedComponents(ClusterGraph C)
{
    cout << "Connected components per cluster: ";
    cluster c;
    forall_clusters(c, C)
    {
        NodeArray<int> arr = NodeArray<int>(*C.getGraph());
        auto comp = connectedComponents(*c, arr);
        cout << comp << ", ";
    }
    cout << endl;
}

void diameter(Graph G)
{
    NodeArray<NodeArray<int>> shortestPathMatrix(G);

    for (node v : G.nodes)
    {
        shortestPathMatrix[v].init(G, numeric_limits<int>::infinity());
        shortestPathMatrix[v][v] = 0;
    }

    bfs_SPAP(G, shortestPathMatrix, 1);

    int max = numeric_limits<int>::infinity();
    int sum = 0;
    for (auto i = shortestPathMatrix.begin(); i != shortestPathMatrix.end(); i++)
    {
        NodeArray<int> line = *i;
        for (auto j = line.begin(); j != line.end(); j++)
        {
            int cost = *j;
            sum += cost;
            if (cost > max)
            {
                max = cost;
            }
        }
    }
    double paths = G.nodes.size() * (G.nodes.size() - 1);
    double avg = sum / paths;
    cout << "average path length: " << avg << endl;
    cout << "graph diameter: " << max << endl;
}

void analyseGraph(ClusterGraph C)
{
    cout << C.numberOfClusters() << " clusters" << endl;
    connectedComponents(C);
    degreeDistribution(C);

    cout << endl;
}

int main()
{
    Graph G;

    cout << "10 clusters max" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << "Graph " << i << ":" << endl;
        emptyGraph(G, 0);
        randomSimpleGraph(G, 30, 70);
        diameter(G);
        ClusterGraph C(G);
        randomClusterGraph(C, G, 9);
        analyseGraph(C);
    }

    cout << endl
         << endl
         << endl;

    cout << "5 clusters max" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << "Graph " << i << ":" << endl;
        emptyGraph(G, 0);
        randomSimpleGraph(G, 30, 70);
        diameter(G);
        ClusterGraph C(G);
        randomClusterGraph(C, G, 4);
        analyseGraph(C);
    }

    return 0;
}