#include <ogdf/basic/graph_generators.h>
#include <ogdf/basic/simple_graph_alg.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/basic/Graph_d.h>
#include <ogdf/basic/List.h>
#include <ogdf/graphalg/ShortestPathAlgorithms.h>

using namespace ogdf;
using namespace std;

void connectedComponents(ClusterGraph C)
{
    cout << "connected components: ";
    for (auto it = C.clusters.begin(); it != C.clusters.end(); it++)
    {
        cluster c = *it;
        Graph G = *C.getGraph();
        // copy graph to preserve the original
        GraphCopy GC(G);

        List<node> ClusterNodes;
        c->getClusterNodes(ClusterNodes);

        for (node v : G.nodes)
        {
            bool inCluster = false;
            for (node n : ClusterNodes)
            {
                if (n->index() == v->index())
                {
                    inCluster = true;
                    break;
                }
            }

            // delete any node that is not in the same cluster
            if (!inCluster)
            {
                GC.delNode(GC.copy(v));
            }
        }

        NodeArray<int> narr(GC);
        cout << connectedComponents(GC, narr, nullptr) << ", ";
    }
}

void analyseGraph(ClusterGraph C)
{
    Graph G = *C.getGraph();

    // setup matrix
    NodeArray<NodeArray<int>> adj(G);
    for (auto it = G.nodes.begin(); it != G.nodes.end(); ++it)
    {
        adj[*it].init(G);
        adj[*it].fill(0);
    }

    // fill matrix with number of connetions
    int edges = 0;
    for (EdgeElement *e : G.edges)
    {
        edges++;
        adj[e->source()][e->target()]++;
        adj[e->target()][e->source()]++;
    }

    // list degrees
    NodeArray<int> degrees(G);
    for (NodeElement *n : G.nodes)
    {
        degrees[n] = n->degree();
    }

    double mod = 0;
    for (NodeElement *n : G.nodes)
    {
        for (NodeElement *v : G.nodes)
        {
            int inSameCluster = 0;
            cluster c = C.firstCluster();
            while ((c = c->succ()))
            {
                bool nInCluster = false;
                bool vInCluster = false;

                List<NodeElement *> ClusterNodes;
                c->getClusterNodes(ClusterNodes);

                for (NodeElement *m : ClusterNodes)
                {
                    nInCluster = nInCluster || m->index() == n->index();
                    vInCluster = vInCluster || m->index() == v->index();
                }
                if (vInCluster & nInCluster)
                {
                    inSameCluster = 1;
                    break;
                }
            }
            if (n->index() == v->index())
                continue;

            mod = mod + 1 / ((float)(2 * edges)) * (adj[n][v] - (degrees[n] * degrees[v] / ((float)(2 * edges)))) * inSameCluster;
        }
    }
    cout << "Modularity: " << mod << endl;

    connectedComponents(C);
    cout << endl
         << endl;
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
        cout << "Graph " << i << ": " << endl;
        emptyGraph(G, 0);
        randomSimpleGraph(G, 30, 70);
        ClusterGraph C(G);
        randomClusterGraph(C, G, 4);
        analyseGraph(C);
    }

    return 0;
}