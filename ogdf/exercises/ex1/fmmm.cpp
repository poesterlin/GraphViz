#include "fmmm.h"

void layoutForceDir(string file)
{
    Graph G;
    GraphAttributes GA(G);
    if (!GraphIO::read(G, string("./exercises/ex1/graph/").append(file)))
    {
        std::cerr << "Could not load gml" << std::endl;
        return;
    }

    for (node v : G.nodes)
        GA.width(v) = GA.height(v) = 10.0;

    FMMMLayout fmmm;

    fmmm.useHighLevelOptions(true);
    fmmm.unitEdgeLength(15.0);
    fmmm.newInitialPlacement(true);
    fmmm.qualityVersusSpeed(FMMMOptions::QualityVsSpeed::GorgeousAndEfficient);

    fmmm.call(GA);

    GraphIO::write(GA, string("./exercises/ex1/output/").append(file.substr(0, file.length() - 4).append("-Force.svg")), GraphIO::drawSVG);
    std::cout << "Force directed Layout of " << file << " done" << std::endl;
}