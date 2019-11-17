#include "hir.h"

void layoutHierarchical(string file)
{
    Graph G;
    GraphAttributes GA(G,
                       GraphAttributes::nodeGraphics |
                           GraphAttributes::edgeGraphics |
                           GraphAttributes::nodeLabel |
                           GraphAttributes::edgeStyle |
                           GraphAttributes::nodeStyle |
                           GraphAttributes::nodeTemplate);

    if (!GraphIO::read(G, string("./exercises/ex1/graph/").append(file)))
    {
        std::cerr << "Could not read gml file" << std::endl;
        return;
    }

    SugiyamaLayout SL;
    SL.setRanking(new OptimalRanking);
    SL.setCrossMin(new MedianHeuristic);

    OptimalHierarchyLayout *ohl = new OptimalHierarchyLayout;
    ohl->layerDistance(30.0);
    ohl->nodeDistance(25.0);
    ohl->weightBalancing(0.8);
    SL.setLayout(ohl);

    SL.call(GA);
    GraphIO::write(GA, string("./exercises/ex1/output/").append(file.substr(0, file.length() - 4).append("-Hierarchical.svg")), GraphIO::drawSVG);
    std::cout << "Hierarchical Layout of " << file << " done" << std::endl;
}