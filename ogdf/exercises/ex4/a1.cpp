#include <ogdf/basic/graph_generators.h>
#include <ogdf/basic/simple_graph_alg.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/basic/Graph_d.h>
#include <ogdf/basic/List.h>
#include <ogdf/graphalg/ShortestPathAlgorithms.h>

using namespace ogdf;
using namespace std;

void analyseGraph(ClusterGraph C)
{
    auto G = *C.getGraph();
    const int nr = G.numberOfNodes();
    auto internal = new vector<double>();
    auto degrees = new vector<double>();
    for (NodeElement *n : G.nodes)
    {
        ListPure<edge> *outEdges = new ListPure<edge>;
        ListPure<edge> *inEdges = new ListPure<edge>;
        n->inEdges(*inEdges);
        n->outEdges(*outEdges);

        for (auto e : *inEdges)
        {
            outEdges->pushBack(e);
        }

        degrees->push_back(n->degree());
        for (auto neighborEdge : *outEdges)
        {
            auto id = n->index();
            NodeElement *neighbor = neighborEdge->target();
            if (n == neighbor)
            {
                continue;
            }

            // check if node id is already in map
            if (internal->size() > id)
            {
                internal->at(id) += 1;
            }
            else
            {
                internal->push_back(0);
            }
        }
    }

    double res;
    for (NodeElement *n : G.nodes)
    {
        auto id = n->index();
        if (id >= internal->size())
        {
            continue;
        }
        internal->at(id) /= 2.0;
        int edgecount = G.numberOfEdges();
        res += (internal->at(id) / edgecount) - pow(degrees->at(id) / (2 * edgecount), 2);
    }
    cout << res << " modularity" << endl;

    NodeArray<int> arr = NodeArray<int>(G);
    cout << connectedComponents(G, arr, nullptr) << " components" << endl
         << endl;
}

int main()
{
    Graph G;

    cout << "10 clusters max" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << "Graph " << i << ":" << endl
             << endl;
        emptyGraph(G, 0);
        randomSimpleGraph(G, 30, 70);
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
        cout << "Graph " << i << ": " << endl
             << endl;
        emptyGraph(G, 0);
        randomSimpleGraph(G, 30, 70);
        ClusterGraph C(G);
        randomClusterGraph(C, G, 4);
        analyseGraph(C);
    }

    return 0;
}