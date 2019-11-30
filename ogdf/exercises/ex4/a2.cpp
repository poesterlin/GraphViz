#include <string>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/basic/simple_graph_alg.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/basic/Graph_d.h>
#include <ogdf/basic/List.h>
#include <ogdf/graphalg/ShortestPathAlgorithms.h>

using namespace ogdf;
using namespace std;

int main()
{

    string files[20] = {
        "g.10.1.graphml",
        "g.10.22.graphml",
        "g.100.1.graphml",
        "g.100.3.graphml",
        "g.20.13.graphml",
        "g.20.14.graphml",
        "g.30.15.graphml",
        "g.30.17.graphml",
        "g.40.12.graphml",
        "g.40.8.graphml",
        "g.50.7.graphml",
        "g.50.8.graphml",
        "g.60.0.graphml",
        "g.60.1.graphml",
        "g.70.1.graphml",
        "g.71.2.graphml",
        "g.80.6.graphml",
        "g.81.9.graphml",
        "g.90.1.graphml",
        "g.90.2.graphml",
    };

    for (auto i = 0; i < 20; i++)
    {
        // read file
        Graph G;
        GraphAttributes GA(G);
        if (!GraphIO::read(G, string("./exercises/ex4/graphs/").append(files[i])))
        {
            cerr << "Could not load gml" << endl;
            return 1;
        }

        cout << files[i] << endl;

        // make cluster graph
        ClusterGraph C(G);

        cluster c;
        forall_clusters(c, C)
        {
            cout << c->cCount() << "," << C.numberOfClusters() << endl;
        }
    }

    return 0;
}
