#include <ogdf/basic/graph_generators.h>
#include <ogdf/basic/simple_graph_alg.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/energybased/FMMMLayout.h>
#include <ogdf/basic/Array.h>
#include <ogdf/basic/Graph_d.h>
#include <ogdf/basic/List.h>
#include <string>

using namespace ogdf;
using namespace std;

void degreeDistribution(ClusterGraph C)
{
    Array<int> arr;
    degreeDistribution(C, arr);
    Array<int>::iterator ptr;
    cout << "Degree distribution: ";
    for (ptr = arr.begin(); ptr != arr.end(); ptr++)
    {
        cout << ptr - arr.begin() + 1 << " -> " << *ptr << ", ";
    }
    cout << endl;
}

void connectedComponents(ClusterGraph C)
{
    NodeArray<int> arr;
    List<node> nodes;
    connectedComponents(C, arr);
    NodeArray<int>::iterator ptr;
    cout << "Connected components: " << endl;
    for (ptr = arr.begin(); ptr != arr.end(); ptr++)
    {
        cout << *ptr << ", ";
    }
}

void analyseGraph(ClusterGraph C, int i)
{
    cout << "Graph " << i << " has " << C.numberOfClusters() << " clusters." << endl;
    degreeDistribution(C);
    auto narr = new NodeArray<int>(C);
    List<node> nodes;
    cout << "connected components: " << connectedComponents(C, *narr, &nodes) << endl;
}

int main()
{
    Graph G;

    cout << "10 clusters max" << endl;
    for (int i = 0; i < 10; i++)
    {
        emptyGraph(G, 0);
        randomSimpleGraph(G, 30, 70);
        ClusterGraph C(G);
        randomClusterGraph(C, G, 9);
        analyseGraph(C, i);
    }

    cout << endl
         << endl
         << endl;

    cout << "5 clusters max" << endl;
    for (int i = 0; i < 10; i++)
    {
        emptyGraph(G, 0);
        randomSimpleGraph(G, 30, 70);
        ClusterGraph C(G);
        randomClusterGraph(C, G, 4);
        analyseGraph(C, i);
    }

    return 0;
}