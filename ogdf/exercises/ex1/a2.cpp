#include <ogdf/basic/graph_generators.h>
#include <ogdf/basic/simple_graph_alg.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/energybased/FMMMLayout.h>
#include <ogdf/basic/Array.h>
#include <ogdf/basic/Graph_d.h>
#include <ogdf/basic/List.h>
#include <string>

#include <iostream> // std::cout, std::endl
#include <thread>   // std::this_thread::sleep_for
#include <chrono>

using namespace ogdf;
using namespace std;

void getDegreeDistribution(ClusterGraph C)
{
    Array<int> arr;
    degreeDistribution(C, arr);
    Array<int>::iterator ptr;
    std::cout << "Degree distribution: ";
    for (ptr = arr.begin(); ptr != arr.end(); ptr++)
    {
        std::cout << ptr - arr.begin() + 1 << " -> " << *ptr << ", ";
    }
    std::cout << endl;
}

void getConnectedComponents(ClusterGraph C)
{
    NodeArray<int> arr;
    List<node> nodes;
    connectedComponents(C, arr);
    NodeArray<int>::iterator ptr;
    std::cout << "Connected components: " << std::endl;
    for (ptr = arr.begin(); ptr != arr.end(); ptr++)
    {
        std::cout << *ptr << std::endl;
    }
}

void saveGraph(Graph G, int graph_number)
{
    GraphAttributes GA(G,
                       GraphAttributes::nodeGraphics |
                           GraphAttributes::edgeGraphics |
                           GraphAttributes::nodeLabel |
                           GraphAttributes::edgeStyle |
                           GraphAttributes::nodeStyle |
                           GraphAttributes::nodeTemplate);

    for (node v : G.nodes)
        GA.width(v) = GA.height(v) = 10.0;

    FMMMLayout fmmm;

    fmmm.useHighLevelOptions(true);
    fmmm.unitEdgeLength(15.0);
    fmmm.newInitialPlacement(true);
    fmmm.qualityVersusSpeed(FMMMOptions::QualityVsSpeed::GorgeousAndEfficient);

    fmmm.call(GA);
    GraphIO::write(GA, "./exercises/ex1/output/output-cluster-10max-" + std::to_string(graph_number) + ".svg", GraphIO::drawSVG);
}

int main()
{
    std::vector<ClusterGraph> arr;
    Graph G;

    std::cout << "Max. 10 clusters setting " << std::endl;
    for (int i = 0; i < 10; i++)
    {
        randomSimpleGraph(G, 30, 70);
        ClusterGraph C(G);
        arr.push_back(C);
        randomClusterGraph(C, G, 9);
        std::cout << "Graph " << i << " has " << C.numberOfClusters() << " clusters." << std::endl;
        saveGraph(C, i);
        getDegreeDistribution(C);
        auto narr = new NodeArray<int>(G);
        List<node> nodes;
        std::cout << "connected components: " << connectedComponents(G, *narr, &nodes) << std::endl;
    }

    cout << " shiiiit" << endl;

    vector<ClusterGraph>::iterator g;
    for (g = arr.begin(); g != arr.end(); g++)
    {
        ClusterGraph graph = *g;

        for (auto clusterPtr = graph.clusters.begin(); clusterPtr != graph.clusters.end(); clusterPtr++)
        {
            ClusterElement *clusterEl = *clusterPtr;
            auto nodes = clusterEl->nodes;
            for (auto el = nodes.begin(); el != nodes.end(); el++)
            {
                cout << *el << endl;
            }

            cout << "next cluster" << endl;
        }
    }

    return 0;
}