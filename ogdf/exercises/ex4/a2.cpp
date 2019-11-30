#include <string>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/basic/simple_graph_alg.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/basic/Graph_d.h>
#include <ogdf/basic/List.h>
#include <ogdf/graphalg/ShortestPathAlgorithms.h>
#include <ogdf/layered/BarycenterHeuristic.h>
#include <ogdf/layered/CoffmanGrahamRanking.h>
#include <ogdf/layered/LongestPathRanking.h>
#include <ogdf/layered/OptimalRanking.h>
#include <ogdf/layered/GridSifting.h>
#include <ogdf/layered/GreedyInsertHeuristic.h>
#include <ogdf/layered/GreedySwitchHeuristic.h>
#include <ogdf/layered/GridSifting.h>
#include <ogdf/layered/MedianHeuristic.h>
#include <ogdf/layered/SiftingHeuristic.h>
#include <ogdf/layered/SplitHeuristic.h>
#include <ogdf/layered/SugiyamaLayout.h>

using namespace ogdf;
using namespace std;

RankingModule *getRanking()
{
    RankingModule *heuristic;

    /*
        ranking options
    */

    heuristic = new LongestPathRanking();
    // heuristic = new CoffmanGrahamRanking();
    // heuristic = new LongestPathRanking();

    return heuristic;
}

LayeredCrossMinModule *getCrossMin()
{
    LayeredCrossMinModule *heuristic;

    /*
        X-ing optimization options
    */

    // heuristic = new BarycenterHeuristic();
    heuristic = new GreedyInsertHeuristic();
    // heuristic = new GreedyInsertHeuristic();
    // heuristic = new GreedySwitchHeuristic();
    // heuristic = new GridSifting();
    // heuristic = new MedianHeuristic();
    // heuristic = new SiftingHeuristic();

    return heuristic;
}

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
        Graph G;
        GraphAttributes GA(G, GraphAttributes::nodeGraphics |
                                  GraphAttributes::edgeGraphics |
                                  GraphAttributes::nodeLabel |
                                  GraphAttributes::edgeStyle |
                                  GraphAttributes::nodeStyle |
                                  GraphAttributes::nodeTemplate);

        // read file
        if (!GraphIO::read(G, string("./exercises/ex4/graphs/").append(files[i])))
        {
            cerr << "Could not load gml" << endl;
            return 1;
        }

        cout << files[i] << endl;

        SugiyamaLayout layout;

        layout.setRanking(getRanking());
        layout.setCrossMin(getCrossMin());

        layout.call(GA);

        GraphIO::write(GA, string("./exercises/ex4/output/").append(files[i].substr(0, files[i].length() - 4).append(".svg")), GraphIO::drawSVG);
        std::cout << "Layout of " << files[i] << " done" << std::endl;
    }

    return 0;
}
